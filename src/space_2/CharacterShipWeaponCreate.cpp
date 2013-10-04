#include "CharacterShipWeaponCreate.h"
#include "NetworkDefine.h"
#include "Weapon.h"


//*************************************************************
// Define
//*************************************************************
#define RESPONSEJSON_CHARACTERSHIP		"charactership"
#define JSON_WEAPONS					"weapons"


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
			// Get charactership
			Json::Value jsonCharacterShip = jsonResponse.get(RESPONSEJSON_CHARACTERSHIP, NULL);
			if(jsonCharacterShip != NULL)
			{
				// Get weapons
				Json::Value weapons = jsonCharacterShip.get(JSON_WEAPONS, NULL);
				if(weapons != NULL)
				{
					for(int i = 0; i < weapons.size(); i++)
					{
						// Get current weapon and update id
						Weapon* tmpWeapon = new Weapon(weapons.get(i, NULL), NULL);
						if(i < this->mCharacterShip->getWeaponsCount())
							this->mCharacterShip->getWeapon(i)->setIdWeapon(tmpWeapon->getIdWeapon());
						delete tmpWeapon;
					}
				}
			}
		}

		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}