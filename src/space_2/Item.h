#pragma once
#include "ItemTierFactory.h"
#include "ItemTypeFactory.h"
#include "KeyValueFile.h"


class Item
{
public:
	// Constructor - Destructor
	Item(KeyValueFile *p_config);
	Item(int p_id);
	void init();
	virtual ~Item(void);

	// Getters - Setters
	long getIdItem();
	void setIdItem(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	double getPrice();
	void setPrice(double p_price);

	bool isBuyable();
	void setBuyable(bool p_value);

	int getStackMax();
	void setStackMax(int p_max);

	std::string getSpriteId();
	void setSpriteId(std::string p_sprite);

	long getStockMinimumMin();
	void setStockMinimumMin(long p_min);

	long getStockMinimumMax();
	void setStockMinimumMax(long p_max);

	long getStockMaximumMin();
	void setStockMaximumMin(long p_min);

	long getStockMaximumMax();
	void setStockMaximumMax(long p_max);

	float getProductionMin();
	void setProductionMin(float p_min);

	float getProductionMax();
	void setProductionMax(float p_max);

	float getConsumptionMin();
	void setConsumptionMin(float p_min);

	float getConsumptionMax();
	void setConsumptionMax(float p_max);

	ItemType* getItemType();
	void setItemType(ItemType *p_itemType);

	ItemTier* getItemTier();
	void setItemTier(ItemTier *p_itemTier);

	// Methode
	long generateStockMin();
	long generateStockMax();
	float generateProduction();
	float generateConsumption();
	void loadFromConfig(KeyValueFile *p_config);


private:
	// Attributes
	long mIdItem;
	std::string mName;
	std::string mDescription;
	double mPrice;
	bool mBuyable;
	int mStackMax;
	std::string mSpriteId;
	
	long mStockMinimumMin;
	long mStockMinimumMax;
	long mStockMaximumMin;
	long mStockMaximumMax;
	float mProductionMin;
	float mProductionMax;
	float mConsumptionMin;
	float mConsumptionMax;

	ItemType *mItemType;
	ItemTier *mItemTier;
};

