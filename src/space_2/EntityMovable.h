#pragma once
#include "Entity.h"
#include "Movable.h"
#include "EntityMovableData.h"
#include "ReactorEffect.h"

// Define
#define TARGET_DISTANCE_MAX_DEFAULT		50

class EntityMovable : public Entity, public Movable, public EntityMovableData
{
public:
	// Constructor - Destructor
	EntityMovable(	double p_x = 0, double p_y = 0,	int p_plane = MAPOBJECT_PLANE_1);
	~EntityMovable(void);

	// Getters - Setters
	int getTargetDistanceMax();
	void setTargetDistanceMax(int p_max);

	double getTargetX();
	double getTargetY();
	void setTargetPosition(double p_x, double p_y);
	bool isTargetPositionDefined();
	void setTargetPositionDefined(bool p_value);

	double getTargetOffsetX();
	void setTargetOffsetX(double p_x);

	double getTargetOffsetY();
	void setTargetOffsetY(double p_y);

	double getSourceX();
	void setSourceX(double p_x);

	double getSourceY();
	void setSourceY(double p_y);

	double getTargetGenRange();
	void setTargetGenRange(double p_range);

	bool isTargetReached();

	// Methods
	void addReactorEffect(ReactorEffect* p_reactor);
	void update();
	void updateMove();
	void updateRocking();
	void updateRotation();
	void updateSprite();
	void updateReactorsSound();
	virtual void updatePosition();
	virtual void updateQuickeningActive();
	void update(sf::Event p_event);
	void draw();
	double generateTargetPositionX();
	double generateTargetPositionY();

	void notifyReactorJsonChanged();
	void notifyReactorSoundChanged();


protected:
	// Attributs
	double mTargetX;
	double mTargetY;
	double mTargetOffsetX;
	double mTargetOffsetY;
	bool mTargetPositionDefined;
	int mTargetDistanceMax;
	double mSourceX;
	double mSourceY;
	double mTargetGenRange;

	std::vector<ReactorEffect*> mReactors;
	sf::Sound* mReactorsSound;
};

