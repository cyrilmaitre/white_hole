#pragma once
#include "EntityEffect.h"

class EntityMovable;

class EntityMovableEffect : public EntityEffect
{
public:
	// Constructor - Destructor
	EntityMovableEffect(EntityMovable* p_entity, Json::Value p_json);
	EntityMovableEffect(EntityMovable* p_entity, float p_offsetX, float p_offsetY, int p_size);
	~EntityMovableEffect(void);

	// Getters - Setters
	EntityMovable* getEntityMovable();
	void setEntityMovable(EntityMovable* p_entity);


protected:
	// Attributs
	EntityMovable* mEntityMovable;
};

