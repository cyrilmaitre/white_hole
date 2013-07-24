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
	bool isContentChanged();
	void setCargoMax(int p_cargoMax);

	ContainerStack::ContainerStackType getType();
	void setType(ContainerStack::ContainerStackType p_type);

	// Methods
	void notifyContainerRowCountChanged();
	void notifyContentChanged();
	void updateContentEstimation();
	bool addItemStack(ItemStack* p_itemStack);
	bool addItemStack(ItemStack* p_itemStack, int p_position);
	

private:
	// Attributs
	ContainerRow** mContainerRows;
	int mContainerRowCount;
	bool mContentChanged;
	double mContentEstimation;
	ContainerStack::ContainerStackType mType;
};

