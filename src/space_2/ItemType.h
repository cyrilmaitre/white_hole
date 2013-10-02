#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "NodeData.h"

class Item;

class ItemType : public NodeData
{
public:
	// Constructor - Destructor
	ItemType(KeyValueFile* p_config);
	~ItemType(void);

	// Getters - Setters
	long getIdItemType();
	void setIdItemType(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	std::string getIconIndex();
	void setIconIndex(std::string p_index);

	ItemType *getParent();
	long getParentId();
	void setParentId(long p_id);

	bool isChildOf(ItemType* p_type);

	std::string getText();
	std::string getIcon();
	std::string getAriane();
	std::vector<ItemType*> getArianeType();
	SpriteParameter* getIconSprite();

	int getItemCount();
	Item* getItem(int p_index);

	// Methode
	void addItem(Item* p_item, bool p_orderAlphabetically = true);
	void removeItem(Item* p_tem);
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mIdItemType;
	std::string mName;
	std::string mDescription;
	std::string mIconIndex;
	long mParentId;

	std::vector<Item*> mItems;
};

