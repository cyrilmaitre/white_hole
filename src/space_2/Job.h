#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "BonusSkills.h"


class Job : public BonusSkills
{
public:
	// Constructor - Destructor
	Job(KeyValueFile *p_config);
	~Job(void);

	// Getters - Setters
	long getIdJob();
	void setIdJob(long p_id);

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
	long mIdJob;
	std::string mName;
	std::string mDescription;
	std::string mSpriteId;
};

