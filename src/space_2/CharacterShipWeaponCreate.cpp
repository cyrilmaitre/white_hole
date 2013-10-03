#include "CharacterShipWeaponCreate.h"
#include "NetworkDefine.h"
#include "Weapon.h"


//*************************************************************
// Define
//*************************************************************
#define RESPONSEJSON_CHARACTERSHIP		"charactership"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterShipWeaponCreate::CharacterShipWeaponCreate( CharacterShip* p_ship )
{
	this->mCharacterShip = p_ship;
}

CharacterShipWeaponCreate::~CharacterShipWeaponCreate(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterShipWeaponCreate::job()
{
	if(this->mCharacterShip != NULL)
	{
		// Create weapons
		Json::Value jsonRequest = this->mCharacterShip->saveToJson();
		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_CHARACTERSHIP_UPDATE, writer.write(jsonRequest));

		// Update local id
		Json::Value jsonResponse;   
		Json::Reader reader;
		bool parsingSuccessfull = reader.parse(response.getBody(), jsonResponse);
		if(parsingSuccessfull)
		{
			CharacterShip* newShip = new CharacterShip(jsonResponse.get(RESPONSEJSON_CHARACTERSHIP, NULL), NULL);
			if(newShip->getWeaponsCount() == this->mCharacterShip->getWeaponsCount())
			{
				for(int i = 0; i < newShip->getWeaponsCount(); i++)
					this->mCharacterShip->getWeapon(i)->setIdWeapon(newShip->getWeapon(i)->getIdWeapon());
			}
		}

		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}