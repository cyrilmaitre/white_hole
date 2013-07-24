#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "DestructableData.h"
#include "MapObjectdata.h"
#include "NpcData.h"

// Define
#define STATIONMODEL_CONFIG_ID			"id"
#define STATIONMODEL_CONFIG_SIZEMIN		"size_min"
#define STATIONMODEL_CONFIG_SIZEMAX		"size_max"
#define STATIONMODEL_CONFIG_SPRITE		"sprite"

class StationModel : public DestructableData, public MapObjectData, public NpcData
{
public:
	// Constructor - Destructor
	StationModel(KeyValueFile* p_config);
	~StationModel(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getSprite();
	void setSprite(std::string p_sprite);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mId;
	int mSizeMin;
	int mSizeMax;
	std::string mSprite;
};

