#include "ContainerRow.h"
#include "Containerable.h"
#include "ContainerStack.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerRow::ContainerRow(Containerable* p_parent, int p_containerStackCount, int p_position, Containerable::ContainerStackType p_type)
{
	this->mContainerable = p_parent;
	this->mType = p_type;
	this->mPosition = p_position;
	this->setContainerStacksCount(p_containerStackCount);

	for(int i = 0; i < CONTAINER_ROW_SIZE; i++)
	{
		if(p_containerStackCount > 0)
			this->mContainerStacks[i] = new ContainerStack(this, NULL, this->mPosition * CONTAINER_ROW_SIZE + i, this->mType);
		else
			this->mContainerStacks[i] = NULL;

		p_containerStackCount--;
	}
}

ContainerRow::~ContainerRow(void)
{
	for(int i = 0; i < CONTAINER_ROW_SIZE; i++)
	{
		if(this->mContainerStacks[i] != NULL)
			delete this->mContainerStacks[i];
	}
}


//*************************************************************
// Getters - Setter
//*************************************************************
Containerable* ContainerRow::getContainerable()
{
	return this->mContainerable;
}

ContainerStack* ContainerRow::getContainerStack( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= CONTAINER_ROW_SIZE)
		p_index = CONTAINER_ROW_SIZE - 1;

	return this->mContainerStacks[p_index];
}

Containerable::ContainerStackType ContainerRow::getType()
{
	return this->mType;
}

void ContainerRow::setType( Containerable::ContainerStackType p_type )
{
	this->mType = p_type;
}

int ContainerRow::getContainerStacksCount()
{
	return this->mContainerStacksCount;
}

void ContainerRow::setContainerStacksCount( int p_count )
{
	this->mContainerStacksCount = p_count;
}

int ContainerRow::getPosition()
{
	return this->mPosition;
}

void ContainerRow::setPosition( int p_position )
{
	this->mPosition = p_position;
}




