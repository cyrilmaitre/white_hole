#include "CharacterShipWeaponCreate.h"
#include "NetworkDefine.h"


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
		Json::Value jsonRequest = this->mCharacterShip->saveToJson();
		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_CHARACTERSHIP_UPDATE, writer.write(jsonRequest));
		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}