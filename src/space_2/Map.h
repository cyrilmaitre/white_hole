#pragma once
#include "Resource.h"
#include "Planet.h"
#include "Sector.h"
#include "NpcShipSpawner.h"
#include "MapObjectSelector.h"
#include "MapMiniView.h"

// Define
#define MAP_SECTORS_TAB_SIZE		3
#define MAP_SECTORS_POSITION_NULL	-0


class Map
{
public:
	// Struct
	struct Vector2iComparer
	{
		bool operator () (const sf::Vector2i & t1, const sf::Vector2i & t2) const
		{
			if(t1.x < t2.x)
				return true;
			else if(t1.x > t2.x)
				return false;

			return t1.y < t2.y;
		}
	};

	// Constructeur - Destructeur
	Map(void);
	~Map(void);

	// Getters - Setters
	Sector* getSector(sf::Vector2i idSector, bool p_generateIfNull = true);
	Sector* getSector(int p_idX, int p_idY, bool p_generateIfNull = false);
	Sector* getCurrentSector();
	int getSectorsLoadedNumber();

	sf::Vector2i getTopLeftSectorId();
	void setTopLeftSectorId(sf::Vector2i p_position);

	NpcShipSpawner *getNpcShipSpawner();
	void setNpcShipSpawner(NpcShipSpawner *p_spawner);

	MapObjectSelector* getMapObjectSelector();
	std::vector<Sector*> getAdjacentSectors(Sector* p_sector, std::vector<Sector*>& p_list);

	// Methods
	Sector* generateSector(sf::Vector2i p_idSector);
	void addSector(Sector* p_sector);
	sf::Vector2i calculateTopLeftSectorId();

	void update();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	Sector*** mSectors;									// Table of visible sectors by player
	sf::Vector2i mTopLeftSectorId;						// Position (top / left) of the sectors into world
	std::map<sf::Vector2i, Sector*, Vector2iComparer> mSectorsLoaded;		// Sector loaded into memory (all world is save into file)
	MapObjectSelector mMapObjectSelector;

	// Npc Ship
	NpcShipSpawner *mNpcShipSpawner;

	// Static
	static std::vector<BackgroundSpace*> mBackgroundSpacePool;
};

