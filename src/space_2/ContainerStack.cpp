#include "ContainerStack.h"
#include "CharacterShipItemStackUpdate.h"
#include "Game.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerStack::ContainerStack( ItemStack* p_stack, int p_position, ContainerStackType p_type ) : mItemStack(NULL)
{
	this->mItemStack = NULL;
	this->mType = p_type;
	this->mPosition = p_position;
	this->mItemStackChanged = false;
	this->setItemStack(p_stack);
}

ContainerStack::~ContainerStack(void)
{
	if(this->mItemStack != NULL)
		delete this->mItemStack;
}


//*************************************************************
// Getters - Setters
//*************************************************************
ItemStack* ContainerStack::getItemStack()
{
	return this->mItemStack;
}

void ContainerStack::setItemStack( ItemStack *p_stack, bool p_removePrec )
{
	if(p_removePrec && this->mItemStack != NULL && this->mItemStack != p_stack)
		delete this->mItemStack;

	this->mItemStack = p_stack;
	this->notifyItemStackChanged();
}

bool ContainerStack::hasItemStack()
{
	return this->mItemStack != NULL;
}

ContainerStack::ContainerStackType ContainerStack::getType()
{
	return this->mType;
}

void ContainerStack::setType( ContainerStackType p_type )
{
	this->mType = p_type;
}

int ContainerStack::getPosition()
{
	return this->mPosition;
}

void ContainerStack::setPosition( int p_position )
{
	this->mPosition = p_position;
}

bool ContainerStack::isItemTypeAllowed( ItemType* p_type )
{
	if(this->mItemTypesAllowed.size() == 0)
		return true;

	for(int i = 0; i < this->mItemTypesAllowed.size(); i++)
	{
		if(this->mItemTypesAllowed[i] != NULL && p_type != NULL && this->mItemTypesAllowed[i]->getId() == p_type->getId())
			return true;
	}

	return false;
}

bool ContainerStack::isItemStackChanged()
{
	bool returnValue = this->mItemStackChanged;
	this->mItemStackChanged = false;
	return returnValue;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerStack::notifyItemStackChanged()
{
	this->mItemStackChanged = true;

	// Update server
	switch(this->mType)
	{
	case ContainerStack::ContainerStackType::TypeCharacterShip:
		if(Game::game != NULL && Game::game->getCharacterShip() != NULL)
			new CharacterShipItemStackUpdate(this->getItemStack(), this->getPosition());
		break;
	}
}

void ContainerStack::addItemTypeAllowed( ItemType* p_type )
{
	this->mItemTypesAllowed.push_back(p_type);
}

int ContainerStack::incStackSize( int p_size )
{
	if(this->mItemStack != NULL)
	{
		int returnValue = this->mItemStack->incStackSize(p_size);
		this->notifyItemStackChanged();
		return returnValue;
	}
}

int ContainerStack::decStackSize( int p_size )
{
	if(this->mItemStack != NULL)
	{
		int returnValue = this->mItemStack->decStackSize(p_size);
		this->notifyItemStackChanged();
		return returnValue;
	}
}

void ContainerStack::setStackSize( int p_size )
{
	if(this->mItemStack != NULL)
	{
		this->mItemStack->setStackSize(p_size);
		this->notifyItemStackChanged();
	}
}

