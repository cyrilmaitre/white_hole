#include "NpcTypeFactory.h"


//*************************************************************
// Define
//*************************************************************
#define NPCTYPE_COUNT	9


//*************************************************************
// Init static
//*************************************************************
NpcTypeFactory * NpcTypeFactory::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
NpcTypeFactory::NpcTypeFactory(void)
{
}

NpcTypeFactory::~NpcTypeFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
NpcType * NpcTypeFactory::getNpcType( std::string p_configName, bool p_useLoaded )
{
	NpcType* returnValue = NULL;

	if(p_useLoaded)
		returnValue = this->getObject(p_configName);

	if(returnValue != NULL)
	{
		return returnValue;
	}
	else
	{
		returnValue = new NpcType(Resource::resource->getConfig(p_configName));

		if(p_useLoaded)
			this->addObject(p_configName, returnValue);

		return returnValue;
	}
}

NpcType * NpcTypeFactory::getNpcType( long p_jobId, bool p_useLoaded )
{
	return this->getNpcType(NPCTYPE_CONFIG + Tools::buildStringWithLong(p_jobId), p_useLoaded);
}

int NpcTypeFactory::getNpcTypeCount()
{
	return NPCTYPE_COUNT;
}

NpcType* NpcTypeFactory::getRandomNpcType()
{
	return this->getNpcType(Tools::random(1, this->getNpcTypeCount()));
}
