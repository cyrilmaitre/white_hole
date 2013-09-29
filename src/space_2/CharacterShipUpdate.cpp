#include "CharacterShipUpdate.h"
#include "NetworkDefine.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterShipUpdate::CharacterShipUpdate( CharacterShip* p_ship )
{
	this->mCharacterShip = p_ship;
}

CharacterShipUpdate::~CharacterShipUpdate(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterShipUpdate::job()
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
