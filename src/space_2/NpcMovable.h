#pragma once
#include "Npc.h"
#include "EntityMovable.h"
#include "Clock.h"


class NpcMovable : public Npc
{
public:
	// Constructor - Destructor 
	NpcMovable(EntityMovable* p_entity);
	~NpcMovable(void);

	// Getters - Setters
	EntityMovable* getEntityMovable();

	// Methods
	void update();


private:
	// Attributs
	EntityMovable* mEntityMovable;

	double mNextTickTarget;
	mks::Clock mClockTickTarget;

	double mNextTickRotation;
	mks::Clock mClockTickRotation;

	// Methods
	void generateNextTickTarget();
	void generateNextTickRotation();
};

