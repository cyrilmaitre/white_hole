#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define PLANETTYPE_CONFIG_ID			"id"
#define PLANETTYPE_CONFIG_NAME			"name"
#define PLANETTYPE_CONFIG_DESCRIPTION	"description"

class PlanetType
{
public:
	// Constructor - Destructor
	PlanetType(KeyValueFile* p_config);
	~PlanetType(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mId;
	std::string mName;
	std::string mDescription;
};

