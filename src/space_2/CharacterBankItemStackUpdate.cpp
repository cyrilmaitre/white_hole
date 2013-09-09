#include "CharacterBankItemStackUpdate.h"
#include "Game.h"
#include "NetworkDefine.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_IDCHARACTERBANK	"idCharacterBank"
#define JSON_ITEMSTACK			"itemStack"
#define JSON_ITEMSTACKPOSITION	"position"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterBankItemStackUpdate::CharacterBankItemStackUpdate( CharacterBank* p_bank, ItemStack* p_itemStack, int p_position )
{
	this->mCharacterBank = p_bank;
	this->mItemStack = p_itemStack;
	this->mPosition = p_position;
}

CharacterBankItemStackUpdate::~CharacterBankItemStackUpdate(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterBankItemStackUpdate::job()
{
	if(this->mCharacterBank != NULL)
	{
		Json::Value jsonRequest;
		jsonRequest[JSON_IDCHARACTERBANK] = this->mCharacterBank->getId();
		jsonRequest[JSON_ITEMSTACK] = this->mItemStack != NULL ? this->mItemStack->saveToJson() : "null";
		jsonRequest[JSON_ITEMSTACKPOSITION] = this->mPosition;

		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_ITEMSTACK_CHARACTERBANK_UPDATE, writer.write(jsonRequest));
		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}
