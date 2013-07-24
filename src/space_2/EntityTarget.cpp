#include "EntityTarget.h"
#include "EntityManager.h"
#include "Entity.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
EntityTarget::EntityTarget(void)
{
	this->setEntity(NULL);
}

EntityTarget::~EntityTarget(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long EntityTarget::getEntityId()
{
	return this->mEntitytId;
}

Entity* EntityTarget::getEntity()
{
	return this->mEntity;
}

void EntityTarget::setEntity( Entity* p_target )
{
	this->mEntity = p_target;

	if(this->mEntity != NULL)
		this->mEntitytId = this->mEntity->getId();
	else
		this->mEntitytId = -1;
}

bool EntityTarget::isEntityValid()
{
	return this->getEntity() != NULL && EntityManager::hasEntity(this->getEntityId());
}
