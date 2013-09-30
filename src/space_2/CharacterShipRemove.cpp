#include "CharacterShipRemove.h"
#include "NetworkDefine.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterShipRemove::CharacterShipRemove( CharacterShip* p_ship )
{
	this->mCharacterShip = p_ship;
}

CharacterShipRemove::~CharacterShipRemove(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterShipRemove::job()
{
	if(this->mCharacterShip != NULL)
	{
		Json::Value jsonRequest = this->mCharacterShip->saveToJson();
		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_CHARACTERSHIP_REMOVE, writer.write(jsonRequest));
		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}
