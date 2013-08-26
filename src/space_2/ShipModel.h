#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "ShipTypeFactory.h"
#include "MovableData.h"
#include "DestructableData.h"
#include "ContainerableData.h"
#include "EquipableData.h"
#include "Item.h"
#include "RotableData.h"
#include "MapObjectModel.h"
#include "EntityMovableData.h"
#include "EntityData.h"


class ShipModel :	public Item, public MovableData, public DestructableData, public ContainerableData, public EquipableData, 
					public RotableData, public MapObjectModel, public EntityMovableData, public EntityData
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

