#include "CharacterShipWeaponUpdate.h"
#include "NetworkDefine.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterShipWeaponUpdate::CharacterShipWeaponUpdate( CharacterShip* p_ship )
{
	this->mCharacterShip = p_ship;
}

CharacterShipWeaponUpdate::~CharacterShipWeaponUpdate(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterShipWeaponUpdate::job()
{
	if(this->mCharacterShip != NULL)
	{
		Json::Value jsonRequest = this->mCharacterShip->saveToJson();
		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_CHARACTERSHIPWEAPON_UPDATE, writer.write(jsonRequest));
		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}