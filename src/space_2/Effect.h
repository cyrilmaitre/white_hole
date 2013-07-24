#pragma once
#include "Resource.h"
#include "Auto.h"


class Effect : public Auto
{
public:
	// Constructor - Destructor
	Effect(void);
	~Effect(void);

	// Getters - Setters
	long getLiveTime();
	void setLiveTime(long p_lifeTime);

	bool isFinished();

	// Methods
	virtual void update();
	virtual void draw();


protected:
	// Attributs
	long mLiveTime;
};

