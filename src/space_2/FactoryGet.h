#pragma once
#include "ShipTypeFactory.h"
#include "ShipModelFactory.h"
#include "ItemTypeFactory.h"
#include "ItemTierFactory.h"
#include "WeaponTypeFactory.h"
#include "AmmoTypeFactory.h"
#include "JobFactory.h"
#include "RaceFactory.h"
#include "AmmoModelFactory.h"
#include "WeaponModelFactory.h"
#include "DangerLevelFactory.h"
#include "NpcTypeFactory.h"
#include "NpcShipModelFactory.h"
#include "ItemFactory.h"
#include "PlanetTypeFactory.h"
#include "PlanetModelFactory.h"
#include "CloudGazModelfactory.h"
#include "CloudWreckModelFactory.h"
#include "LootItemModelFactory.h"
#include "LevelFactory.h"
#include "SkillFactory.h"
#include "StationModelFactory.h"
#include "StarModelFactory.h"

class FactoryGet
{
public:
	// Methods
	static ShipTypeFactory *getShipTypeFactory();
	static ShipModelFactory *getShipModelFactory();
	static ItemTypeFactory *getItemTypeFactory();
	static ItemTierFactory *getItemTierFactory();
	static WeaponTypeFactory *getWeaponTypeFactory();
	static AmmoTypeFactory *getAmmoTypeFactory();
	static JobFactory *getJobFactory();
	static RaceFactory *getRaceFactory();
	static AmmoModelFactory *getAmmoFactory();
	static WeaponModelFactory *getWeaponModelFactory();
	static DangerLevelFactory *getDangerLevelFactory();
	static NpcTypeFactory *getNpcTypeFactory();
	static NpcShipModelFactory *getNpcShipModelFactory();
	static ItemFactory *getItemFactory();
	static PlanetTypeFactory *getPlanetTypeFactory();
	static PlanetModelFactory *getPlanetModelFactory();
	static CloudGazModelfactory *getCloudGazModelFactory();
	static CloudWreckModelFactory *getCloudWreckModelFactory();
	static LootItemModelFactory *getLootItemModelFactory();
	static LevelFactory *getLevelFactory();
	static SkillFactory *getSkillFactory();
	static StationModelFactory *getStationModelFactory();
	static StarModelFactory *getStarModelFactory();

	static void init();
	static void uninit();

private:
	// Constructor - Destructor
	FactoryGet(void);
	~FactoryGet(void);
};

