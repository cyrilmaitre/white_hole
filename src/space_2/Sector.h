#pragma once
#include "Resource.h"
#include "Planet.h"
#include "BackgroundGeneration.h"
#include "DangerLevel.h"
#include "CloudGaz.h"
#include "CloudWreck.h"
#include "Entity.h"
#include "Star.h"

// Define
#define SECTOR_PLANE					MAPOBJECT_PLANE_21
#define SECTOR_WIDTH					1024
#define SECTOR_HEIGHT					1024
#define SECTOR_MINI_WIDTH				1024
#define SECTOR_MINI_HEIGHT				1024

class Sector
{
public:
	// Enum
	enum SectorColor
	{
		Green = 0,
		GreeYellow,
		GreenBlue,
		Red,
		RedYellow,
		RedOrange,
		Blue,
		BlueViolet,
		BlueAqua,
		Last
	};

	// Constructor - Destructor
	Sector(int p_x, int p_y);
	Sector(sf::Vector2i p_idSector);
	void init();
	void initSectorColor();
	~Sector(void);

	// Getters - Setters
	sf::Vector2i getIdSector();
	int getIdSectorX();
	int getIdSectorY();
	int getX();
	int getY();
	sf::Vector2i getPosition();

	DangerLevel* getDangerLevel();
	void setDangerLevel(DangerLevel* p_level);

	BackgroundSpace* getBackground();

	bool isVisible();
	void setVisible(bool p_isVisible);

	bool isVisited();
	void setVisited(bool p_visited);

	sf::Vector2i getAdjacentSectorId(int p_cardinality);
	sf::Vector2i getNorthSectorId();
	sf::Vector2i getNorthEastSectorId();
	sf::Vector2i getEastSectorId();
	sf::Vector2i getSouthEastSectorId();
	sf::Vector2i getSouthSectorId();
	sf::Vector2i getSouthWestSectorId();
	sf::Vector2i getWestSectorId();
	sf::Vector2i getNorthWestSectorId();

	int getObjectsCount();
	MapObject* getObject(int p_index);

	int getEntitiesCount();
	Entity* getEntity(int p_index);

	int getStarCount();
	Star* getStar(int p_index);

	std::vector<Planet*> getPlanets();
	std::vector<CloudGaz*> getCloudGazs();
	std::vector<CloudWreck*> getCloudWrecks();

	Sector::SectorColor getSectorColor();
	void setSectorColor(Sector::SectorColor p_color);

	int getSectorColorSpread();
	void setSectorColorSpread(int p_spread);
	void decSectorColorSpread();

	int getPlanetsCount();
	void setPlanetsCount(int p_count);

	int getCloudGazsCount();
	void setCloudGazsCount(int p_count);

	int getCloudWrecksCount();
	void setCloudWrecksCount(int p_count);

	// Methode
	void calculateIdSector();
	void calculatePosition();

	bool contain(int p_x, int p_y);
	void addMapObject(MapObject* p_object, bool p_deleteIfMissPositioned = false);
	void addEntity(Entity* p_entity);
	void removeEntity(Entity* p_entity);
	void removeEntity(int p_index);
	bool validateMapObject(MapObject* p_object, bool p_checkAdj = true);
	bool canSpreadSectorColor();

	void update();
	void update(sf::Event p_event);
	void updateSpritePosition();
	void updateMapObjects();
	void updateEntities();
	void updateMapObjects(sf::Event p_event);
	void updateEntities(sf::Event p_event);
	void draw();
	void drawMapObjects();
	void drawEntities();
	void drawMapObjects(int p_plane);
	void drawEntities(int p_plane);

	void notifyVisibilityChanged();

	static sf::Vector2i convertPositionToId(sf::Vector2i p_position);
	static sf::Vector2i convertIdToPosition(sf::Vector2i p_id);


private:
	// Attributs
	sf::Vector2i mIdSector;
	int mX;
	int mY;

	bool mVisited;
	bool mVisible;
	BackgroundSpace *mBackground;
	sf::Sprite mBackgroundSprite;
	
	DangerLevel* mDangerLevel;
	std::vector<MapObject*> mObjects;
	std::vector<Entity*> mEntities;
	std::vector<Star*> mStars;

	Sector::SectorColor mSectorColor;
	int mSectorColorSpread;

	// Stats
	int mPlanetsCount;
	int mCloudGazsCount;
	int mCloudWrecksCount;
};

