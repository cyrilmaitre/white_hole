#pragma once
#include "Character.h"
#include "Skill.h"

// Define
#define SKILL_LEVEL_MIN					0
#define SKILL_LEVEL_MAX					100
#define SKILL_JSON_IDCHARACTERSKILL		"idCharacterSkill"
#define SKILL_JSON_IDCHARACTER			"idCharacter"
#define SKILL_JSON_IDSKILL				"idSkill"
#define SKILL_JSON_LEVEL				"level"

class SkillCharacter
{
public:
	// Constructor - Destructor
	SkillCharacter(Json::Value p_json, Character* p_character);
	SkillCharacter(Skill* p_skill, Character* p_character);
	~SkillCharacter(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	int getTotalLevel();
	int getLevel();
	void setLevel(int p_level);

	int getLevelPending();
	void setLevelPending(int p_levelPending);

	Skill* getSkill();
	void setSkill(Skill* p_skill);

	Character* getCharacter();
	void setCharacter(Character *p_character);

	// Methods
	bool canBeLevelUp();
	bool canBeLevelDown();
	void levelUp();
	void levelDown();
	void validateLevelPending();
	void loadFromJson(Json::Value p_json);
	Json::Value saveToJson();


private:
	// Attributs
	long mId;
	int mLevel;						// This is the base level between 0 and 100 %. The total level equal level + bonus level (job, stuff, race...)
	int mLevelPending;
	Skill* mSkill;
	Character* mCharacter;
};

