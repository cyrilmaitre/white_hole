#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "NodeData.h"


class ItemType : public NodeData
{
public:
	// Constructor - Destructor
	ItemType(KeyValueFile* p_config);
	~ItemType(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	std::string getIconIndex();
	void setIconIndex(std::string p_index);

	ItemType *getParent();
	long getParentId();
	void setParentId(long p_id);

	std::string getText();
	std::string getIcon();
	SpriteParameter* getIconSprite();

	// Methode
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mId;
	std::string mName;
	std::string mDescription;
	std::string mIconIndex;
	long mParentId;
};

