#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "BonusSkills.h"

// Define
#define JOB_CONFIG_ID				"id"
#define JOB_CONFIG_NAME				"name"
#define JOB_CONFIG_DESCRIPTION		"description"
#define JOB_CONFIG_BONUS			"bonus"
#define JOB_CONFIG_SPRITEID			"spriteId"

class Job : public BonusSkills
{
public:
	// Constructor - Destructor
	Job(KeyValueFile *p_config);
	~Job(void);

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

