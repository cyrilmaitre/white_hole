#include "CharacterShipItemStackUpdate.h"
#include "CharacterShip.h"
#include "Game.h"
#include "NetworkDefine.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterShipItemStackUpdate::CharacterShipItemStackUpdate( ItemStack* p_itemStack, int p_position )
{
	this->mItemStack = p_itemStack;
	this->mPosition = p_position;
}

CharacterShipItemStackUpdate::~CharacterShipItemStackUpdate(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterShipItemStackUpdate::job()
{
	if(Game::game != NULL || Game::game->getCharacterShip() != NULL)
	{
		Json::Value jsonRequest;
		jsonRequest[CHARACTERSHIP_JSON_IDCHARACTERSHIP] = Game::game->getCharacterShip()->getId();
		jsonRequest[CHARACTERSHIP_JSON_ITEMSTACK] = this->mItemStack != NULL ? this->mItemStack->saveToJson() : "null";
		jsonRequest[CHARACTERSHIP_JSON_ITEMSTACKPOSITION] = this->mPosition;

		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_ITEMSTACK_CHARACTERSHIP_UPDATE, writer.write(jsonRequest));
		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}
