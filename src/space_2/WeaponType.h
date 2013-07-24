#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define WEAPONTYPE_KINETIC		1
#define WEAPONTYPE_LASER		2
#define WEAPONTYPE_LAUNCHER		3

#define WEAPONTYPE_CONFIG_ID			"id"
#define WEAPONTYPE_CONFIG_NAME			"name"
#define WEAPONTYPE_CONFIG_DESCRIPTION	"description"

class WeaponType
{
public:
	// Constructor - Destructor
	WeaponType(KeyValueFile* p_config);
	~WeaponType(void);

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

