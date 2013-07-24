#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define SKILL_CONFIG_ID					"id"
#define SKILL_CONFIG_NAME				"name"
#define SKILL_CONFIG_DESCRIPTION		"description"
#define SKILL_CONFIG_SPRITEID			"spriteId"

class Skill
{
public:
	// Constructor - Destructor
	Skill(KeyValueFile *p_config);
	~Skill(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	std::string getSpriteId();
	void setSpriteId(std::string p_id);

	// Methods
	void loadFromConfig(KeyValueFile *p_config);


private:
	// Attributs
	long mId;
	std::string mName;
	std::string mDescription;
	std::string mSpriteId;
};

