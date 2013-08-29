#pragma once
#include "MapObject.h"
#include "Entity.h"
#include "CharacterShip.h"
#include "Sector.h"
#include "NpcShip.h"
#include "Station.h"

class ToolsMap
{
public:
	// Methods
	static float getAngle(MapObject* p_source, MapObject* p_target);
	static float getAngleAbsolute(MapObject* p_source, MapObject* p_target);
	static float getDistance(MapObject* p_source, MapObject* p_target);
	static float getDistance(MapObject* p_source, double p_targetX, double p_targetY);

	static bool isCharacterShip(Entity* p_entity);
	static bool isDestructable(MapObject* p_target);
	static bool isEntity(MapObject* p_target);
	static bool isNpc(Entity* p_target);
	static bool isStar(MapObject* p_object);
	static bool isNpcShip(Entity* p_target);
	static bool isStation(Entity* p_target);

	static int getRadius(MapObject* p_object);
	static int getRadius(MapObject* p_object, int p_plane);

	static Sector::SectorColor getRandomSectorColor();
	static sf::Color convertSectorColor(Sector::SectorColor p_color);


private:
	// Constructor - Destructor
	ToolsMap(void);
	~ToolsMap(void);
};

