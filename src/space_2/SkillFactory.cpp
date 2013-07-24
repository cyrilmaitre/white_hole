#include "SkillFactory.h"


//*************************************************************
// Init static
//*************************************************************
SkillFactory * SkillFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
SkillFactory::SkillFactory(void)
{
}

SkillFactory::~SkillFactory(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Skill* SkillFactory::getSkillFighting()
{
	return this->getSkill(SKILL_CONFIG_FIGHTING);
}

Skill* SkillFactory::getSkillDrone()
{
	return this->getSkill(SKILL_CONFIG_DRONE);
}

Skill* SkillFactory::getSkillSteering()
{
	return this->getSkill(SKILL_CONFIG_STEERING);
}

Skill* SkillFactory::getSkillMining()
{
	return this->getSkill(SKILL_CONFIG_MINING);
}

Skill* SkillFactory::getSkillCrafting()
{
	return this->getSkill(SKILL_CONFIG_CRAFTING);
}

Skill* SkillFactory::getSkillAlchemy()
{
	return this->getSkill(SKILL_CONFIG_ALCHEMY);
}

Skill* SkillFactory::getSkillBargaining()
{
	return this->getSkill(SKILL_CONFIG_BARGAINING);
}

Skill* SkillFactory::getSkillSalvaging()
{
	return this->getSkill(SKILL_CONFIG_SALVAGING);
}

Skill* SkillFactory::getSkillConstruction()
{
	return this->getSkill(SKILL_CONFIG_CONSTRUCTION);
}

Skill* SkillFactory::getSkill( std::string p_configName, bool p_useLoaded )
{
	Skill* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new Skill(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

Skill* SkillFactory::getSkill( long p_id, bool p_useLoaded )
{
	return this->getSkill(SKILL_CONFIG + Tools::buildStringWithLong(p_id), p_useLoaded);
}


