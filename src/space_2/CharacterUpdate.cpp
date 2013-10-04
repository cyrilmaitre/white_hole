#include "CharacterUpdate.h"
#include "NetworkDefine.h"
#include "UserInterface.h"


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
	if(UserInterface::mUserInterface != NULL)
		UserInterface::mUserInterface->setSavingGifVisible(true);

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

	if(UserInterface::mUserInterface != NULL)
		UserInterface::mUserInterface->setSavingGifVisible(false);
}
