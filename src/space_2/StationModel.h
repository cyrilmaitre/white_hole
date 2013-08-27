#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "DestructableData.h"
#include "MapObjectdata.h"
#include "NpcData.h"
#include "MapObjectModel.h"
#include "EntityData.h"
#include "EquipableData.h"


class StationModel : public DestructableData, public NpcData, public MapObjectModel, public EntityData, public EquipableData
{
public:
	// Constructor - Destructor
	StationModel(KeyValueFile* p_config);
	~StationModel(void);

	// Getters - Setters
	std::string getSpinnerSprite();
	void setSpinnerSprite(std::string p_sprite);

	float getSpinnerVelocity();
	void setSpinnerVelocity(float p_velocity);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	std::string mSpinnerSprite;
	float mSpinnerVelocity;
};

