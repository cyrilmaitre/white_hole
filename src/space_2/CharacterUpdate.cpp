#include "CharacterUpdate.h"
#include "NetworkDefine.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterUpdate::CharacterUpdate( Character* p_character )
{
	this->mCharacter = p_character;
}


CharacterUpdate::~CharacterUpdate(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterUpdate::job()
{
	if(this->mCharacter != NULL)
	{
		Json::Value jsonRequest = this->mCharacter->saveToJson();
		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_CHARACTER_UPDATE, writer.write(jsonRequest));
		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}
