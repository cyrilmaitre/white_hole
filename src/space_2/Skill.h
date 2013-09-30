#pragma once
#include "Resource.h"
#include "KeyValueFile.h"


class Skill
{
public:
	// Constructor - Destructor
	Skill(KeyValueFile *p_config);
	~Skill(void);

	// Getters - Setters
	long getIdSkill();
	void setIdSkill(long p_id);

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
	long mIdSkill;
	std::string mName;
	std::string mDescription;
	std::string mSpriteId;
};

