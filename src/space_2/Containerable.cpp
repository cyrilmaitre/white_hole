#include "Containerable.h"
#include "ContainerRow.h"
#include "ContainerStack.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Containerable::Containerable(Containerable::ContainerStackType p_type)
{
	this->mContainerRows = NULL;
	this->mContainerRowCount = 0;
	this->mContentChanged = false;
	this->setContentEstimation(0);
	this->mNotifyServerOnChange = true;
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

bool Containerable::isContentChanged(bool p_resetValue)
{
	if(!p_resetValue)
		return this->mContentChanged;

	bool returnValue = this->mContentChanged;
	this->mContentChanged = false;
	return returnValue;
}

Containerable::ContainerStackType Containerable::getType()
{
	return this->mType;
}

void Containerable::setType( Containerable::ContainerStackType p_type )
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
						if(currentStack->getItemStack()->getItem()->getIdItem() == p_item->getIdItem())
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

std::vector<Item*> Containerable::getUniqueItems()
{
	std::vector<Item*> uniqueItems;
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
						Item* currentItem = currentStack->getItemStack()->getItem();
						bool addCurrentItem = true;
						for(int k = 0; k < uniqueItems.size(); k++)
						{
							if(uniqueItems[k]->getIdItem() == currentItem->getIdItem())
							{
								addCurrentItem = false;
								break;
							}
						}
						if(addCurrentItem)
							uniqueItems.push_back(currentItem);
					}
				}
			}
		}
	}
	return uniqueItems;
}

int Containerable::getItemCount( Item* p_item )
{
	int itemCount = 0;
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
						if(currentStack->getItemStack()->getItem()->getIdItem() == p_item->getIdItem())
							itemCount += currentStack->getItemStack()->getStackSize();
					}
				}
			}
		}
	}
	return itemCount;
}

std::map<Item*, int> Containerable::getItemsCount()
{
	std::vector<Item*> uniqueItems = this->getUniqueItems();
	std::map<Item*, int> itemsCount;

	for(int i = 0; i < uniqueItems.size(); i++)
		itemsCount.insert(std::pair<Item*, int>(uniqueItems[i], this->getItemCount(uniqueItems[i])));

	return itemsCount;
}

bool Containerable::isNotifyServerOnChange()
{
	return this->mNotifyServerOnChange;
}

void Containerable::setNotifyServerOnChange( bool p_value )
{
	this->mNotifyServerOnChange = p_value;
}


//*************************************************************
// Methods
//*************************************************************
void Containerable::empty()
{
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
						currentStack->setItemStack(NULL);
				}
			}
		}
	}
}

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
						if(p_itemStack->getStackSize() > 0 && currentStack->getItemStack()->getItem()->getIdItem() == p_itemStack->getItem()->getIdItem() && currentStack->getItemStack()->getStackSizeFree() > 0)
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

bool Containerable::addItemStack( ItemStack* p_itemStack, int p_position, bool p_notify )
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
			currentStack->setItemStack(p_itemStack, false, p_notify);
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


