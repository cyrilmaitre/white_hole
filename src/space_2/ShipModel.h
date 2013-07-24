#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "ShipTypeFactory.h"
#include "MovableData.h"
#include "DestructableData.h"
#include "ContainerableData.h"
#include "StuffableData.h"
#include "UpgradableData.h"
#include "WeaponableData.h"
#include "Item.h"
#include "RotableData.h"
#include "MapObjectModel.h"


class ShipModel :	public Item, public MovableData, public DestructableData, public ContainerableData, public StuffableData, 
					public UpgradableData, public WeaponableData, public RotableData, public MapObjectModel
{
public:
	// Constructor - Destructor
	ShipModel(KeyValueFile* p_config);
	~ShipModel(void);

	// Getters - Setters
	ShipType* getShipType();
	void setShipType(ShipType *p_shipType);

	// Methode
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	ShipType *mShipType;
};

