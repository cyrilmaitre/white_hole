#include "CharacterShipCreate.h"
#include "NetworkDefine.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterShipCreate::CharacterShipCreate( CharacterShip* p_ship )
{
	this->mCharacterShip = p_ship;
}

CharacterShipCreate::~CharacterShipCreate(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterShipCreate::job()
{
	if(this->mCharacterShip != NULL)
	{
		Json::Value jsonRequest = this->mCharacterShip->saveToJson();
		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_CHARACTERSHIP_CREATE, writer.write(jsonRequest));
		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}

