#pragma once
#include "Resource.h"
#include "Clock.h"

class EntityMovable;

class Reactor
{
public:
	// Enum
	enum ReactorType
	{
		Left = 0,
		Right
	};

	// Constructor - Destructor
	Reactor(EntityMovable* p_entity, Json::Value p_reactorJson);
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

	int getSize();
	void setSize(int p_size);

	bool isActive();
	void setActve(bool p_active);

	// Methods
	void update();
	void updatePosition();
	void updateActive();
	void updateReactorAlpha();
	void updateReactorDust();
	void draw();


private:
	// Attributs
	EntityMovable* mEntityMovable;
	ReactorType mType;
	float mOffsetX;
	float mOffsetXWithRotate;
	float mOffsetY;
	float mOffsetYWithRotate;
	int mSize;
	bool mActive;
	sf::Sprite *mReactor;
	float mReactorAlpha;
	float mReactorAlphaSpeed;

	mks::Clock mReactorClock;
	mks::Clock mReactorDustClock;
	float mReactorDustTick;

	// Methods
	void computeReactorDustTick();
};

