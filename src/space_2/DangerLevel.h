#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "NpcType.h"
#include "NpcShipModel.h"

// Define
#define DANGERLEVEL_TEXTURE_MAPMINI_WIDTH			64
#define DANGERLEVEL_TEXTURE_MAPMINI_HEIGHT			64

class DangerLevel
{
public:
	// Constructor - Destructor
	DangerLevel(KeyValueFile *p_config);
	~DangerLevel(void);

	// Getters - Setters
	long getIdDangerLevel();
	void setIdDangerLevel(long p_id);

	int getDangerLevel();
	void setDangerLevel(int p_level);

	sf::Color getDangerLevelColor();
	void setDangerLevelColor(sf::Color p_color);

	sf::RectangleShape* getShapeMapMini();

	int getShipTypeSpawn(int p_index);
	int getShipTypeSpawnCount();
	int getShipTypeSpawnNumber(long p_shipTypeId);
	void setShipTypeSpawnNumber(long p_shipTypeId, int p_count);
	void setShipTypeSpawnNumber(std::string p_value);

	int getShipModelSpawn(int p_index);
	int getShipModelSpawnCount();
	float getShipModelSpawnChance(long p_shipModelId);
	void getShipModelSpawnChanceByShipType(std::map<NpcShipModel*, float>& p_map, long p_shipTypeId);
	void setShipModelSpawnChance(long p_shipModelId, float p_chance);
	void setShipModelSpawnChance(std::string p_value);

	int getPlanetCountMin();
	void setPlanetCountMin(int p_min);
	int getPlanetCountMax();
	void setPlanetCountMax(int p_max);

	int getCloudGazCountMin();
	void setCloudGazCountMin(int p_min);
	int getCloudGazCountMax();
	void setCloudGazCountMax(int p_max);

	int getCloudWreckCountMin();
	void setCloudWreckCountMin(int p_min);
	int getCloudWreckCountMax();
	void setCloudWreckCountMax(int p_max);

	int getStationCountMin();
	void setStationCountMin(int p_min);
	int getStationCountMax();
	void setStationCountMax(int p_max);

	// Methods
	int generatePlanetCount();
	int generateCloudGazCount();
	int generateCloudWreckCount();
	int generateStationCount();
	void loadFromConfig(KeyValueFile *p_config);


private:
	// Attibuts
	long mIdDangerLevel;
	int mDangerLevel;
	sf::Color mColor;
	sf::RectangleShape mShapeMapMini;

	// Ship
	std::vector<long> mShipTypeSpawn;				// Id of shiptype available
	std::map<long, int> mShipTypeSpawnNumber;		// Id shiptype ; Count (number of this type to spawn)
	std::vector<int> mShipModelSpawn;				// Id of shipmodel available
	std::map<long, float> mShipModelSpawnChance;	// Id shipmodel ; Chance to spawn this model

	// Planets
	int mPlanetCountMin;
	int mPlanetCountMax;

	// Cloud gazs
	int mCloudGazCountMin;
	int mCloudGazCountMax;

	// Cloud
	int mCloudWreckCountMin;
	int mCloudWreckCountMax;

	// Station
	int mStationCountMin;
	int mStationCountMax;
};

