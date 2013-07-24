#include "Levelable.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Levelable::Levelable(void)
{
	this->mLevel = 0;
	this->mLevelChanged = false;

	this->mExperience = 0;
	this->mExperienceChanged = false;

	this->mLevelConfig = NULL;
}

Levelable::~Levelable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int Levelable::getLevel()
{
	return this->mLevel;
}

void Levelable::setLevel( int p_level )
{
	bool notify = this->mLevel != p_level;
	this->mLevel = p_level;

	if(notify)
		this->notifyLevelChanged();
}

bool Levelable::isLevelChanged()
{
	bool returnValue = this->mLevelChanged;
	this->mLevelChanged = false;
	return returnValue;
}

bool Levelable::isLevelMax()
{
	if(this->hasLevelConfig())
		return this->getLevel() == this->getLevelConfig()->getLevelMax();
	else
		return true;
}

long Levelable::getExperience()
{
	return this->mExperience;
}

long Levelable::getExperienceCurrentLevel()
{
	if(this->hasLevelConfig())
		return this->getLevelConfig()->getExperience(this->getLevel());
	else
		return -1;
}

long Levelable::getExperienceBeforeLevel()
{
	if(this->hasLevelConfig())
		return this->getExperienceCurrentLevel() - this->getExperience();
	else
		return -1;
}

void Levelable::setExperience( long p_experience )
{
	bool notify = this->mExperience != p_experience;
	this->mExperience = p_experience;
	
	if(notify)
		this->notifyExperienceChanged();
}

bool Levelable::isExperienceChanged()
{
	bool returnValue = this->mExperienceChanged;
	this->mExperienceChanged = false;
	return returnValue;
}

bool Levelable::hasLevelConfig()
{
	return this->mLevelConfig != NULL;
}

Level* Levelable::getLevelConfig()
{
	return this->mLevelConfig;
}

void Levelable::setLevelConfig( Level *p_level )
{
	this->mLevelConfig = p_level;
	this->notifyExperienceChanged();
}


//*************************************************************
// Methods
//*************************************************************
void Levelable::notifyExperienceChanged()
{
	this->mExperienceChanged = true;
}

void Levelable::notifyLevelChanged()
{
	this->mLevelChanged = true;
}

void Levelable::incLevel()
{
	if(!this->isLevelMax())
	{
		this->setLevel(this->getLevel() + 1);
	}
}

void Levelable::incExperience( long p_inc )
{
	if(!this->isLevelMax())
	{
		if(p_inc < this->getExperienceBeforeLevel())
		{
			this->setExperience(this->getExperience() + p_inc);
		}
		else
		{
			p_inc -= this->getExperienceBeforeLevel();
			this->setExperience(p_inc);
			this->incLevel();
		}
	}
}


