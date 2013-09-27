#pragma once
#include "ContainerableData.h"
#include "ContainerRow.h"
#include "ItemStack.h"


class Containerable: public ContainerableData
{
public:
	// Constructor - Destructor
	Containerable(ContainerStack::ContainerStackType p_type = ContainerStack::ContainerStackType::TypeNone);
	~Containerable(void);
	void deleteContainerRows();

	// Getters - Setters
	int getContainerRowCount();
	void setContainerRowCount(int p_count);

	double getContentEstimation();
	void setContentEstimation(double p_estimation);
	
	ContainerRow* getContainerRow(int p_index);
	bool isContentChanged(bool p_resetValue = true);
	void setCargoMax(int p_cargoMax);

	long getContentFreeFor(Item* p_item);
	std::vector<Item*> getUniqueItems();
	int getItemCount(Item* p_item);
	std::map<Item*, int> getItemsCount();

	ContainerStack::ContainerStackType getType();
	void setType(ContainerStack::ContainerStackType p_type);

	// Methods
	void empty();
	void notifyContainerRowCountChanged();
	void notifyContentChanged();
	void updateContentEstimation();
	bool addItemStack(ItemStack* p_itemStack);
	bool addItemStack(ItemStack* p_itemStack, int p_position, bool p_notify = true);
	bool addItem(Item* p_item, int p_quantity);
	

private:
	// Attributs
	ContainerRow** mContainerRows;
	int mContainerRowCount;
	bool mContentChanged;
	double mContentEstimation;
	ContainerStack::ContainerStackType mType;
};

