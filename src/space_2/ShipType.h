#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "ItemTier.h"
#include "SpriteParameterFactory.h"
#include "DestructableData.h"
#include "MovableData.h"
#include "ContainerableData.h"
#include "StuffableData.h"
#include "UpgradableData.h"
#include "WeaponableData.h"


class ShipType
{
public:
	// Constructor - Destructor
	ShipType(KeyValueFile* p_config);
	~ShipType(void);

 	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_descripion);

	// Methode
	void loadFromConfig(KeyValueFile* p_config);


private:
	long mId;
	std::string mName;
	std::string mDescription;
};

