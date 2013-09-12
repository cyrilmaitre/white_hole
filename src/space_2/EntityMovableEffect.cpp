#include "EntityMovableEffect.h"
#include "EntityMovable.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
EntityMovableEffect::EntityMovableEffect( EntityMovable* p_entity, Json::Value p_json ) : EntityEffect(p_entity, p_json)
{
	this->setEntityMovable(p_entity);
}

EntityMovableEffect::EntityMovableEffect( EntityMovable* p_entity, float p_offsetX, float p_offsetY, int p_size ) : EntityEffect(p_entity, p_offsetX, p_offsetY, p_size)
{
	this->setEntityMovable(p_entity);
}	

EntityMovableEffect::~EntityMovableEffect(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
EntityMovable* EntityMovableEffect::getEntityMovable()
{
	return this->mEntityMovable;
}

void EntityMovableEffect::setEntityMovable( EntityMovable* p_entity )
{
	this->mEntityMovable = p_entity;
}
