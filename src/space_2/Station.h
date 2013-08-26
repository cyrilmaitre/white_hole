#pragma once
#include "Entity.h"
#include "StationModel.h"
#include "Npc.h"


class Station : public Entity, public Npc
{
public:
	// Constructor - Destructor
	Station(void);
	~Station(void);

	// Getters - Setters
	StationModel* getModel();
	void setModel(StationModel* p_model);

	// Methods
	void update();
	void notifyModelChanged();
	void loadSprite();


private:
	// Attributs
	StationModel* mModel;
};

