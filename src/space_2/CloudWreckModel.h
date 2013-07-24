#pragma once
#include "MapObjectModel.h"
#include "MapObject.h"


class CloudWreckModel : public MapObjectModel
{
public:
	// Constructor - Destructor
	CloudWreckModel(KeyValueFile* p_config);
	~CloudWreckModel(void);

	// Getters - Setters
	MapObject::MapObjectOpacity getOpacity();
	void setOpacity(MapObject::MapObjectOpacity p_opacity);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	MapObject::MapObjectOpacity mOpacity;
};

