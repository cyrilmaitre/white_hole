#pragma once
#include "Resource.h"
#include "EntityMovable.h"


class Reactor
{
public:
	// Enum
	enum ReactorType
	{
		Left,
		Right
	};

	// Constructor - Destructor
	Reactor(EntityMovable* p_entity, ReactorType p_type, float p_offsetX, float p_offsetY);
	~Reactor(void);

	// Getters - Setters
	EntityMovable* getEntityMovable();
	void setEntityMovable(EntityMovable* p_entity);

	ReactorType getType();
	void setType(ReactorType p_type);

	float getOffsetX();
	void setOffsetX(float p_x);

	float getOffsetY();
	void setOffsetY(float p_y);

	// Methods
	void update();
	void draw();


private:
	// Attributs
	EntityMovable* mEntityMovable;
	ReactorType mType;
	float mOffsetX;
	float mOffsetY;
	sf::Sprite *mReactor;
};

