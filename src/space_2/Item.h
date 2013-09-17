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
	long getId();
	void setId(long p_id);

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

	float getStockMinimumMin();
	void setStockMinimumMin(float p_min);

	float getStockMinimumMax();
	void setStockMinimumMax(float p_max);

	float getStockMaximumMin();
	void setStockMaximumMin(float p_min);

	float getStockMaximumMax();
	void setStockMaximumMax(float p_max);

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
	float generateStockMin();
	float generateStockMax();
	float generateProduction();
	float generateConsumption();
	void loadFromConfig(KeyValueFile *p_config);


private:
	// Attributes
	long mId;
	std::string mName;
	std::string mDescription;
	double mPrice;
	bool mBuyable;
	int mStackMax;
	std::string mSpriteId;
	
	float mStockMinimumMin;
	float mStockMinimumMax;
	float mStockMaximumMin;
	float mStockMaximumMax;
	float mProductionMin;
	float mProductionMax;
	float mConsumptionMin;
	float mConsumptionMax;

	ItemType *mItemType;
	ItemTier *mItemTier;
};

