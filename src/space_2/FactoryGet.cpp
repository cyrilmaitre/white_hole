#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
FactoryGet::FactoryGet(void)
{
}

FactoryGet::~FactoryGet(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void FactoryGet::init()
{
	ShipTypeFactory::mInstance = new ShipTypeFactory();
	ShipModelFactory::mInstance = new ShipModelFactory();
	ItemTypeFactory::mInstance = new ItemTypeFactory();
	ItemTierFactory::mInstance = new ItemTierFactory();
	WeaponTypeFactory::mInstance = new WeaponTypeFactory();
	AmmoTypeFactory::mInstance = new AmmoTypeFactory();
	JobFactory::mInstance = new JobFactory();
	RaceFactory::mInstance = new RaceFactory();
	AmmoModelFactory::mInstance = new AmmoModelFactory();
	WeaponModelFactory::mInstance = new WeaponModelFactory();
	DangerLevelFactory::mInstance = new DangerLevelFactory();
	NpcTypeFactory::mInstance = new NpcTypeFactory();
	NpcShipModelFactory::mInstance = new NpcShipModelFactory();
	ItemFactory::mInstance = new ItemFactory();
	PlanetTypeFactory::mInstance = new PlanetTypeFactory();
	PlanetModelFactory::mInstance = new PlanetModelFactory();
	CloudGazModelfactory::mInstance = new CloudGazModelfactory();
	CloudWreckModelFactory::mInstance = new CloudWreckModelFactory();
	LootItemModelFactory::mInstance = new LootItemModelFactory();
	LevelFactory::mInstance = new LevelFactory();
	SkillFactory::mInstance = new SkillFactory();
	StationModelFactory::mInstance = new StationModelFactory();
	StarModelFactory::mInstance = new StarModelFactory();
}

void FactoryGet::uninit()
{
	ShipTypeFactory::mInstance->uninit();
	delete ShipTypeFactory::mInstance;

	ShipModelFactory::mInstance->uninit();
	delete ShipModelFactory::mInstance;

	ItemTypeFactory::mInstance->uninit();
	delete ItemTypeFactory::mInstance;

	ItemTierFactory::mInstance->uninit();
	delete ItemTierFactory::mInstance;

	WeaponTypeFactory::mInstance->uninit();
	delete WeaponTypeFactory::mInstance;

	AmmoTypeFactory::mInstance->uninit();
	delete AmmoTypeFactory::mInstance;

	JobFactory::mInstance->uninit();
	delete JobFactory::mInstance;

	RaceFactory::mInstance->uninit();
	delete RaceFactory::mInstance;

	AmmoModelFactory::mInstance->uninit();
	delete AmmoModelFactory::mInstance;

	WeaponModelFactory::mInstance->uninit();
	delete WeaponModelFactory::mInstance;

	DangerLevelFactory::mInstance->uninit();
	delete DangerLevelFactory::mInstance;

	NpcTypeFactory::mInstance->uninit();
	delete NpcTypeFactory::mInstance;

	NpcShipModelFactory::mInstance->uninit();
	delete NpcShipModelFactory::mInstance;

	ItemFactory::mInstance->uninit();
	delete ItemFactory::mInstance;

	PlanetTypeFactory::mInstance->uninit();
	delete PlanetTypeFactory::mInstance;

	PlanetModelFactory::mInstance->uninit();
	delete PlanetModelFactory::mInstance;

	CloudGazModelfactory::mInstance->uninit();
	delete CloudGazModelfactory::mInstance;

	CloudWreckModelFactory::mInstance->uninit();
	delete CloudWreckModelFactory::mInstance;

	LootItemModelFactory::mInstance->uninit();
	delete LootItemModelFactory::mInstance;

	LevelFactory::mInstance->uninit();
	delete LevelFactory::mInstance;

	SkillFactory::mInstance->uninit();
	delete SkillFactory::mInstance;

	StationModelFactory::mInstance->uninit();
	delete StationModelFactory::mInstance;

	StarModelFactory::mInstance->uninit();
	delete StarModelFactory::mInstance;
}

ShipTypeFactory * FactoryGet::getShipTypeFactory()
{
	return ShipTypeFactory::mInstance;
}

ShipModelFactory * FactoryGet::getShipModelFactory()
{
	return ShipModelFactory::mInstance;
}

ItemTypeFactory * FactoryGet::getItemTypeFactory()
{
	return ItemTypeFactory::mInstance;
}

ItemTierFactory * FactoryGet::getItemTierFactory()
{
	return ItemTierFactory::mInstance;
}

WeaponTypeFactory * FactoryGet::getWeaponTypeFactory()
{
	return WeaponTypeFactory::mInstance;
}

AmmoTypeFactory * FactoryGet::getAmmoTypeFactory()
{
	return AmmoTypeFactory::mInstance;
}

JobFactory * FactoryGet::getJobFactory()
{
	return JobFactory::mInstance;
}

RaceFactory * FactoryGet::getRaceFactory()
{
	return RaceFactory::mInstance;
}

AmmoModelFactory * FactoryGet::getAmmoFactory()
{
	return AmmoModelFactory::mInstance;
}

WeaponModelFactory * FactoryGet::getWeaponModelFactory()
{
	return WeaponModelFactory::mInstance;
}

DangerLevelFactory * FactoryGet::getDangerLevelFactory()
{
	return DangerLevelFactory::mInstance;
}

NpcTypeFactory * FactoryGet::getNpcTypeFactory()
{
	return NpcTypeFactory::mInstance;
}

NpcShipModelFactory * FactoryGet::getNpcShipModelFactory()
{
	return NpcShipModelFactory::mInstance;
}

ItemFactory * FactoryGet::getItemFactory()
{
	return ItemFactory::mInstance;
}

PlanetTypeFactory * FactoryGet::getPlanetTypeFactory()
{
	return PlanetTypeFactory::mInstance;
}

PlanetModelFactory * FactoryGet::getPlanetModelFactory()
{
	return PlanetModelFactory::mInstance;
}

CloudGazModelfactory * FactoryGet::getCloudGazModelFactory()
{
	return CloudGazModelfactory::mInstance;
}

CloudWreckModelFactory * FactoryGet::getCloudWreckModelFactory()
{
	return CloudWreckModelFactory::mInstance;
}

LootItemModelFactory * FactoryGet::getLootItemModelFactory()
{
	return LootItemModelFactory::mInstance;
}

LevelFactory * FactoryGet::getLevelFactory()
{
	return LevelFactory::mInstance;
}

SkillFactory * FactoryGet::getSkillFactory()
{
	return SkillFactory::mInstance;
}

StationModelFactory * FactoryGet::getStationModelFactory()
{
	return StationModelFactory::mInstance;
}

StarModelFactory * FactoryGet::getStarModelFactory()
{
	return StarModelFactory::mInstance;
}
