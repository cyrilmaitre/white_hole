#include "CharacterBank.h"


//*************************************************************
// Define
//*************************************************************
#define CARGO_MAX				64
#define BANK_1_PRICE			0
#define BANK_2_PRICE			10000
#define BANK_3_PRICE			50000
#define BANK_4_PRICE			250000
#define BANK_5_PRICE			1000000
#define JSON_IDCHARATCER		"idCharacter"
#define JSON_IDCHARACTERBANK	"idCharacterBank"
#define JSON_NUMBER				"number"
#define JSON_UNLOCK				"unlock"
#define JSON_ITEMSTACKS			"itemStacks"
#define JSON_ITEMSTACK			"itemStack"
#define JSON_ITEMSTACKPOSITION	"position"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterBank::CharacterBank( Json::Value json, Character *p_character ) : Containerable(ContainerStack::ContainerStackType::TypeCharacterBank)
{
	this->mCharacter = NULL;
	this->mIdCharacterBank = -1;
	this->mNumber = -1;
	this->mUnlock = false;
	this->mPrice = -1;

	this->setCargoMax(CARGO_MAX);
	this->setCharacter(p_character);
	this->loadFromJson(json);
}

CharacterBank::CharacterBank()
{
	this->mCharacter = NULL;
	this->mIdCharacterBank = -1;
	this->mNumber = -1;
	this->mUnlock = false;
	this->mPrice = 0;
}

CharacterBank::~CharacterBank(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* CharacterBank::getCharacter()
{
	return this->mCharacter;
}

void CharacterBank::setCharacter( Character* p_character )
{
	this->mCharacter = p_character;
}

long CharacterBank::getIdCharacterBank()
{
	return this->mIdCharacterBank;
}

void CharacterBank::setIdCharacterBank( long p_id )
{
	this->mIdCharacterBank = p_id;
}

int CharacterBank::getNumber()
{
	return this->mNumber;
}

void CharacterBank::setNumber( int p_number )
{
	if(this->mNumber != p_number)
	{
		this->mNumber = p_number;
		this->setPrice(this->getPrice(this->mNumber));
	}
}

bool CharacterBank::isUnlock()
{
	return this->mUnlock;
}

void CharacterBank::setUnlock( bool p_unlock )
{
	this->mUnlock = p_unlock;
}

long CharacterBank::getPrice()
{
	return this->mPrice;
}

long CharacterBank::getPrice( int p_number )
{
	switch(p_number)
	{
	case 1:
		return BANK_1_PRICE;
		break;

	case 2:
		return BANK_2_PRICE;
		break;

	case 3:
		return BANK_3_PRICE;
		break;

	case 4:
		return BANK_4_PRICE;
		break;

	case 5:
		return BANK_5_PRICE;
		break;

	default:
		return BANK_1_PRICE;
	}
}

void CharacterBank::setPrice( long p_price )
{
	this->mPrice = p_price;
}


//*************************************************************
// Methods
//*************************************************************
bool CharacterBank::canBeUnlock()
{
	return	this->getCharacter() != NULL && 
			this->getNumber() > 1 && this->getCharacter()->getBankByNumber(this->getNumber() - 1)->isUnlock();
}

void CharacterBank::unlock()
{
	if(this->canBeUnlock() && this->getCharacter()->hasEnoughCredit(this->getPrice()))
	{
		this->getCharacter()->decCredit(this->getPrice());
		this->setUnlock(true);
	}
}

void CharacterBank::loadFromJson( Json::Value json )
{
	this->setIdCharacterBank(json.get(JSON_IDCHARACTERBANK, -1).asInt());
	this->setNumber(json.get(JSON_NUMBER, -1).asInt());
	this->setUnlock(json.get(JSON_UNLOCK, false).asBool());

	// ItemStacks
	Json::Value itemStacks = json.get(JSON_ITEMSTACKS, NULL);
	if(itemStacks != NULL)
	{
		for(int i = 0; i < itemStacks.size(); i++)
		{
			Json::Value currentItemStack = itemStacks.get(i, NULL);
			ItemStack* currentStack = new ItemStack(currentItemStack.get(JSON_ITEMSTACK, NULL));
			this->addItemStack(currentStack, currentItemStack.get(JSON_ITEMSTACKPOSITION, 0).asInt(), false);
		}
	}
}

Json::Value CharacterBank::saveToJson()
{
	Json::Value json;
	json[JSON_IDCHARATCER] = this->getCharacter()->getIdCharacter();
	json[JSON_IDCHARACTERBANK] = this->getIdCharacterBank();
	json[JSON_NUMBER] = this->getNumber();
	json[JSON_UNLOCK] = this->isUnlock();
	return json;
}
