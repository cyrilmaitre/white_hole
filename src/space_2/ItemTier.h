#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define ITEMTIER_CONFIG_ID				"id"
#define ITEMTIER_CONFIG_NAME			"name"
#define ITEMTIER_CONFIG_DESCRIPTION		"description"

class ItemTier
{
public:
	// Constructor - Destructor
	ItemTier(KeyValueFile* p_config);
	~ItemTier(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	// Methode
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributes
	long mId;
	std::string mName;
	std::string mDescription;
};

