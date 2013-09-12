#pragma once
#include "ItemType.h"
#include "Factory.h"
#include "TreeData.h"

class ItemType;

// Define
#define ITEMTYPE_CONFIG		"itemtype-"

class ItemTypeFactory: public Factory<ItemType>
{
public:
	// Constructor - Destructor
	ItemTypeFactory(void);
	~ItemTypeFactory(void);

	// Methods
	ItemType* getItemType(std::string p_configItemType, bool p_useLoaded = true);
	ItemType* getItemType(KeyValueFile* p_config, bool p_useLoaded = true);
	ItemType* getItemType(int p_id, bool p_useLoaded = true);
	std::vector<ItemType*> getItemTypeAll(bool p_useLoaded = true);

	TreeData* getItemTypeTree();
	std::vector<ItemType*> getItemTypeList();

	void buildItemTypeTree();
	void buildItemTypeList();

	// Static
	static ItemTypeFactory* mInstance;


private:
	// Attributs
	TreeData* mItemTypeTree;
	std::vector<ItemType*> mItemTypeList;
};

