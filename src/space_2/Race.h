#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "BonusSkills.h"
#include "SplitString.h"

// Define
#define RACE_CONFIG_ID				"id"
#define RACE_CONFIG_NAME			"name"
#define RACE_CONFIG_DESCRIPTION		"description"
#define RACE_CONFIG_BONUS			"bonus"
#define RACE_CONFIG_SPRITEID		"spriteId"
#define RACE_CONFIG_AVATARINDEX		"avatarIndex"

class Race : public BonusSkills
{
public:
	// Constructor - Destructor
	Race(KeyValueFile *p_config);
	~Race(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	std::string getSpriteId();
	void setSpriteId(std::string p_id);

	int getAvatarCount();
	std::string getAvatarIndex(int p_index);

	// Methods
	void loadFromConfig(KeyValueFile *p_config);


private:
	// Attributs
	long mId;
	std::string mName;
	std::string mDescription;
	std::string mSpriteId;
	SplitString* mAvatarIndex;

	// Methods
	void deleteAvatarIndex();

	// Getters - Setters
	void setAvatarIndex(std::string p_indexes);
};

