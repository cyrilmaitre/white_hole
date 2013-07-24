#pragma once
#include "Resource.h"
#include "Clock.h"


class Auto
{
public:
	// Constructor - Destructor
	Auto(void);
	virtual ~Auto(void);

	// Getters - Setters
	virtual bool isFinished() = 0;

	// Methods
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void notifyFinished();


protected:
	// Attributs
	mks::Clock mClockAuto;
};

