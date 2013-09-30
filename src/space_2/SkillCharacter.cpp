#include "SkillCharacter.h"
#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
SkillCharacter::SkillCharacter( Json::Value p_json, Character* p_character)
{
	this->mLevel = 0;
	this->mLevelPending = 0;
	this->mCharacter = p_character;
	this->loadFromJson(p_json);
}

SkillCharacter::SkillCharacter( Skill* p_skill, Character* p_character )
{
	this->mIdSkillCharacter = -1;
	this->mLevel = 0;
	this->mLevelPending = 0;
	this->mCharacter = p_character;
	this->mSkill = p_skill;
}

SkillCharacter::~SkillCharacter(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long SkillCharacter::getIdSkillCharacter()
{
	return this->mIdSkillCharacter;
}

void SkillCharacter::setIdSkillCharacter( long p_id )
{
	this->mIdSkillCharacter = p_id;
}

int SkillCharacter::getTotalLevel()
{
	int totalLevel = this->getLevel() + this->getLevelPending();
	if(this->getCharacter()->hasRace())
		totalLevel += this->getCharacter()->getRace()->getBonusSkill(this->getSkill()->getId());

	if(this->getCharacter()->hasJob())
		totalLevel += this->getCharacter()->getJob()->getBonusSkill(this->getSkill()->getId());

	return totalLevel;
}

int SkillCharacter::getLevel()
{
	return this->mLevel;
}

void SkillCharacter::setLevel( int p_level )
{
	if(p_level < SKILL_LEVEL_MIN)
		p_level = SKILL_LEVEL_MIN;
	else if(p_level > SKILL_LEVEL_MAX)
		p_level = SKILL_LEVEL_MAX;

	this->mLevel = p_level;
}

int SkillCharacter::getLevelPending()
{
	return this->mLevelPending;
}

void SkillCharacter::setLevelPending(int p_levelPending)
{
	this->mLevelPending = p_levelPending;
}

Skill* SkillCharacter::getSkill()
{
	return this->mSkill; 
}

void SkillCharacter::setSkill( Skill* p_skill )
{
	this->mSkill = p_skill;
}

Character* SkillCharacter::getCharacter()
{
	return this->mCharacter;
}

void SkillCharacter::setCharacter( Character *p_character )
{
	this->mCharacter = p_character;
}


//*************************************************************
// Methods
//*************************************************************
bool SkillCharacter::canBeLevelUp()
{
	return	this->getCharacter() != NULL && 
			this->getCharacter()->hasSkillPoints() && 
			(this->getLevel() + this->getLevelPending() + 1) <= SKILL_LEVEL_MAX;
}

bool SkillCharacter::canBeLevelDown()
{
	return	this->getCharacter() != NULL && 
			(this->getLevelPending() - 1) >= 0;
}

void SkillCharacter::levelUp()
{
	if(this->canBeLevelUp())
	{
		this->setLevelPending(this->getLevelPending() + 1);
		this->getCharacter()->decSkillPoints();
	}
}

void SkillCharacter::levelDown()
{
	if(this->canBeLevelDown())
	{
		this->setLevelPending(this->getLevelPending() - 1);
		this->getCharacter()->incSkillPoints();
	}
}

void SkillCharacter::validateLevelPending()
{
	this->setLevel(this->getLevel() + this->getLevelPending());
}

void SkillCharacter::loadFromJson( Json::Value p_json )
{
	this->setIdSkillCharacter(p_json.get(SKILL_JSON_IDCHARACTERSKILL, -1).asInt64());
	this->setLevel(p_json.get(SKILL_JSON_LEVEL, 0).asInt());
	this->setSkill(FactoryGet::getSkillFactory()->getSkill(p_json.get(SKILL_JSON_IDSKILL, -1).asInt()));
}

Json::Value SkillCharacter::saveToJson()
{
	Json::Value json;
	json[SKILL_JSON_IDCHARACTERSKILL] = this->getIdSkillCharacter();
	json[SKILL_JSON_IDCHARACTER] = this->getCharacter()->getIdCharacter();
	json[SKILL_JSON_IDSKILL] = this->getSkill()->getId();
	json[SKILL_JSON_LEVEL] = this->getLevel();
	return json;
}