#pragma once
#include "EntityEffect.h"

class EntityMovable;

class EntityMovableEffect : public EntityEffect
{
public:
	// Constructor - Destructor
	EntityMovableEffect(EntityMovable* p_entity, Json::Value p_json, sf::Vector2f p_offset = sf::Vector2f(0, 0), int p_size = 0);
	~EntityMovableEffect(void);

	// Getters - Setters
	EntityMovable* getEntityMovable();
	void setEntityMovable(EntityMovable* p_entity);


protected:
	// Attributs
	EntityMovable* mEntityMovable;
};

