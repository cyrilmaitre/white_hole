#pragma once
#include "Resource.h"
#include "KeyValueFile.h"


class MovableData
{
public:
	// Constructor - Destructor
	MovableData(void);
	~MovableData(void);

	// Getters - Setters
	virtual float getVelocityMax();
	void setVelocityMax(float p_velocityMax);

	virtual float getQuickening();
	void setQuickening(float p_quickening);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromMovableData(MovableData* p_object);


protected:
	// Attributs
	float mVelocityMax;
	float mQuickening;
};

