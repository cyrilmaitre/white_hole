#include "Containerable.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Containerable::Containerable(ContainerStack::ContainerStackType p_type)
{
	this->mContainerRows = NULL;
	this->mContainerRowCount = 0;
	this->mContentChanged = false;
	this->setContentEstimation(0);
	this->mType = p_type;
}

Containerable::~Containerable(void)
{
	this->deleteContainerRows();
}

void Containerable::deleteContainerRows()
{
	if(this->mContainerRows != NULL)
	{
		for(int i = 0; i < this->getContainerRowCount(); i++)
		{
			if(this->mContainerRows[i] != NULL)
				delete this->mContainerRows[i];
		}
		delete this->mContainerRows;
	}
	this->mContainerRows = NULL;
}


//*************************************************************
// Getters - Setters
//*************************************************************
int Containerable::getContainerRowCount()
{
	return this->mContainerRowCount;
}

void Containerable::setContainerRowCount( int p_count )
{
	this->mContainerRowCount = p_count;
}

double Containerable::getContentEstimation()
{
	return this->mContentEstimation;
}

void Containerable::setContentEstimation( double p_estimation )
{
	this->mContentEstimation = p_estimation;
}

ContainerRow* Containerable::getContainerRow( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->getContainerRowCount())
		p_index = this->getContainerRowCount() - 1;

	return this->mContainerRows[p_index];
}

void Containerable::setCargoMax( int p_cargoMax )
{
	ContainerableData::setCargoMax(p_cargoMax);
	this->setContainerRowCount(ceil( ((float) p_cargoMax) / ((float) CONTAINER_ROW_SIZE) ));
	this->notifyContainerRowCountChanged();
}

bool Containerable::isContentChanged()
{
	bool returnValue = this->mContentChanged;
	this->mContentChanged = false;
	return returnValue;
}

ContainerStack::ContainerStackType Containerable::getType()
{
	return this->mType;
}

void Containerable::setType( ContainerStack::ContainerStackType p_type )
{
	this->mType = p_type;
}

long Containerable::getContentFreeFor( Item* p_item )
{
	long contentfree = 0;
	for(int i = 0; i < this->getContainerRowCount(); i++)
	{
		for(int j = 0; j < CONTAINER_ROW_SIZE; j++)
		{
			ContainerRow* currentRow = this->getContainerRow(i);
			if(currentRow != NULL)
			{
				ContainerStack* currentStack = currentRow->getContainerStack(j);
				if(currentStack != NULL)
				{
					if(currentStack->hasItemStack())
					{
						if(currentStack->getItemStack()->getItem()->getId() == p_item->getId())
							contentfree += currentStack->getItemStack()->getStackSizeFree();
					}
					else
					{
						contentfree += p_item->getStackMax();
					}
				}
			}
		}
	}
	return contentfree;
}


//*************************************************************
// Methods
//*************************************************************
void Containerable::notifyContainerRowCountChanged()
{
	this->deleteContainerRows();

	if(this->getContainerRowCount() > 0)
	{
		this->mContainerRows = new ContainerRow*[this->getContainerRowCount()];
		for(int i = 0; i < this->getContainerRowCount() - 1; i++)
			this->mContainerRows[i] = new ContainerRow(this, CONTAINER_ROW_SIZE, i, this->mType);

		int rowItems = this->getCargoMax() % CONTAINER_ROW_SIZE;
		if(rowItems == 0) rowItems = CONTAINER_ROW_SIZE; 
		this->mContainerRows[this->getContainerRowCount() - 1] = new ContainerRow(this, rowItems, this->getContainerRowCount() - 1, this->mType);
	}
}

void Containerable::notifyContentChanged()
{
	this->mContentChanged = true;
	this->updateContentEstimation();
}

bool Containerable::addItemStack( ItemStack* p_itemStack )
{
	if(this->getContainerRowCount() == 0)
		return false;

	int freeRowPosition = -1;
	int freeStackPosition = -1;

	for(int i = 0; i < this->getContainerRowCount(); i++)
	{
		for(int j = 0; j < CONTAINER_ROW_SIZE; j++)
		{
			ContainerRow* currentRow = this->getContainerRow(i);
			if(currentRow != NULL)
			{
				ContainerStack* currentStack = currentRow->getContainerStack(j);
				if(currentStack != NULL)
				{
					if(!currentStack->hasItemStack())
					{
						if(freeRowPosition == -1 && freeStackPosition == -1)
						{
							freeRowPosition = i;
							freeStackPosition = j;
						}
					}
					else
					{
						if(p_itemStack->getStackSize() > 0 && currentStack->getItemStack()->getItem()->getId() == p_itemStack->getItem()->getId())
						{
							p_itemStack->setStackSize(currentStack->incStackSize(p_itemStack->getStackSize()));
							this->notifyContentChanged();
						}
					}
				}
			}
		}
	}

	if(p_itemStack->getStackSize() > 0 && freeRowPosition != -1 && freeStackPosition != -1)
	{
		ContainerRow* currentRow = this->getContainerRow(freeRowPosition);
		if(currentRow != NULL)
		{
			ContainerStack* currentStack = currentRow->getContainerStack(freeStackPosition);
			if(currentStack != NULL && !currentStack->hasItemStack())
			{
				currentStack->setItemStack(p_itemStack);
				this->notifyContentChanged();
				return true;
			}
		}
	}
	else
	{
		delete p_itemStack;
	}

	return false;
}

bool Containerable::addItemStack( ItemStack* p_itemStack, int p_position )
{
	if(this->getContainerRowCount() == 0)
		return false;

	int rowPosition = p_position / CONTAINER_ROW_SIZE;
	int stackPosition = p_position % CONTAINER_ROW_SIZE;

	if(rowPosition < 0)
		rowPosition = 0;
	else if(rowPosition >= this->getContainerRowCount())
		rowPosition = this->getContainerRowCount() - 1;

	ContainerRow* currentRow = this->getContainerRow(rowPosition);
	if(currentRow != NULL)
	{
		ContainerStack* currentStack = currentRow->getContainerStack(stackPosition);
		if(currentStack != NULL && !currentStack->hasItemStack())
		{
			currentStack->setItemStack(p_itemStack);
			this->notifyContentChanged();
			return true;
		}
	}
	return this->addItemStack(p_itemStack);
}

bool Containerable::addItem( Item* p_item, int p_quantity )
{
	if(p_item != NULL)
	{
		bool returnValue = true;
		int numberOfFullStack = p_quantity / p_item->getStackMax();
		int lastStackSize = p_quantity % p_item->getStackMax();

		if(numberOfFullStack > 0)
		{
			for(int i = 0; i < numberOfFullStack; i++)
			{
				ItemStack* newItemStack = new ItemStack(p_item, p_item->getStackMax());
				returnValue = this->addItemStack(newItemStack);
			}
		}

		if(lastStackSize > 0)
		{
			ItemStack* newItemStack = new ItemStack(p_item, lastStackSize);
			returnValue = this->addItemStack(newItemStack);
		}

		return returnValue;
	}
	return false;
}

void Containerable::updateContentEstimation()
{
	double newEstimation = 0;
	for(int i = 0; i < this->getContainerRowCount(); i++)
	{
		for(int j = 0; j < CONTAINER_ROW_SIZE; j++)
		{
			ContainerRow* currentRow = this->getContainerRow(i);
			if(currentRow != NULL)
			{
				ContainerStack* currentStack = currentRow->getContainerStack(j);
				if(currentStack != NULL && currentStack->hasItemStack())
					newEstimation += currentStack->getItemStack()->getStackPrice();
			}
		}
	}
	this->setContentEstimation(newEstimation);
}




