#pragma once
#include "Skill.h"
#include "Factory.h"

// Define
#define SKILL_CONFIG				"skill-"
#define SKILL_CONFIG_FIGHTING		SKILL_CONFIG"1"
#define SKILL_CONFIG_DRONE			SKILL_CONFIG"2"
#define SKILL_CONFIG_STEERING		SKILL_CONFIG"3"
#define SKILL_CONFIG_MINING			SKILL_CONFIG"4"
#define SKILL_CONFIG_CRAFTING		SKILL_CONFIG"5"
#define SKILL_CONFIG_ALCHEMY		SKILL_CONFIG"6"
#define SKILL_CONFIG_BARGAINING		SKILL_CONFIG"7"
#define SKILL_CONFIG_SALVAGING		SKILL_CONFIG"8"
#define SKILL_CONFIG_CONSTRUCTION	SKILL_CONFIG"9"

class SkillFactory : public Factory<Skill>
{
public:
	// Constructor - Destructor
	SkillFactory(void);
	~SkillFactory(void);

	// Methods
	Skill* getSkillFighting();
	Skill* getSkillDrone();
	Skill* getSkillSteering();
	Skill* getSkillMining();
	Skill* getSkillCrafting();
	Skill* getSkillAlchemy();
	Skill* getSkillBargaining();
	Skill* getSkillSalvaging();
	Skill* getSkillConstruction();

	Skill* getSkill(std::string p_configName, bool p_useLoaded = true);
	Skill* getSkill(long p_id, bool p_useLoaded = true);

	// Static
	static SkillFactory *mInstance;
};

