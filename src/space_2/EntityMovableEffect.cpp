#include "EntityMovableEffect.h"
#include "EntityMovable.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
EntityMovableEffect::EntityMovableEffect( EntityMovable* p_entity, Json::Value p_json, sf::Vector2f p_offset, int p_size ) : EntityEffect(p_entity, p_json, p_offset, p_size)
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
