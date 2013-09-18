#include "ToolsMap.h"
#include "Game.h"
#include "Camera.h"
#include "Npc.h"
#include "Star.h"
#include "Terminable.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ToolsMap::ToolsMap(void)
{
}

ToolsMap::~ToolsMap(void)
{
}


//*************************************************************
// Methods
//*************************************************************
// Return angle between object source orientation and object target
float ToolsMap::getAngle( MapObject* p_source, MapObject* p_target )
{
	float objectTargetdAngleAbsolute = ToolsMap::getAngleAbsolute(p_source, p_target);
	float objectTargetAngle = p_source->getRotation() - objectTargetdAngleAbsolute;

	if(objectTargetAngle < -180)
		objectTargetAngle = 180 - (-objectTargetAngle - 180);
	else if(objectTargetAngle < 0)
		objectTargetAngle = -objectTargetAngle;
	else if(objectTargetAngle > 180)
		objectTargetAngle = 180 - (objectTargetAngle - 180);

	return objectTargetAngle;
}

float ToolsMap::getAngleAbsolute( MapObject* p_source, MapObject* p_target )
{
	return Tools::getAngle(p_source->Object::getX(), p_source->Object::getY(), p_target->getX(p_source->getPlane()), p_target->getY(p_source->getPlane()));
}

float ToolsMap::getDistance( MapObject* p_source, MapObject* p_target )
{
	if(p_target == NULL)
		return 0;

	return ToolsMap::getDistance(p_source, p_target->getX(p_target->getPlane()), p_target->getY(p_target->getPlane()));
}

float ToolsMap::getDistance( MapObject* p_source, double p_targetX, double p_targetY )
{
	if(p_source == NULL)
		return 0;

	return sqrt(pow(Tools::getAbsolute(p_source->Object::getX() - p_targetX), 2) + pow(Tools::getAbsolute(p_source->Object::getY() - p_targetY), 2));
}

bool ToolsMap::isCharacterShip( Entity* p_entity )
{
	CharacterShip* v = dynamic_cast<CharacterShip*>(p_entity);
	return v != 0;
}

bool ToolsMap::isDestructable( MapObject* p_target )
{
	Destructable* v = dynamic_cast<Destructable*>(p_target);
	return v != 0;
}

bool ToolsMap::isEntity( MapObject* p_target )
{
	Entity* v = dynamic_cast<Entity*>(p_target);
	return v != 0;
}

bool ToolsMap::isNpc( Entity* p_target )
{
	Npc* v = dynamic_cast<Npc*>(p_target);
	return v != 0;
}

bool ToolsMap::isStar( MapObject* p_object )
{
	Star* v = dynamic_cast<Star*>(p_object);
	return v != 0;
}

bool ToolsMap::isNpcShip( Entity* p_target )
{
	NpcShip* v = dynamic_cast<NpcShip*>(p_target);
	return v != 0;
}

bool ToolsMap::isStation( Entity* p_target )
{
	Station* v = dynamic_cast<Station*>(p_target);
	return v != 0;
}

bool ToolsMap::isTerminable( Entity* p_entity )
{
	Terminable* v = dynamic_cast<Terminable*>(p_entity);
	return v != 0;
}

int ToolsMap::getRadius( MapObject* p_object )
{
	return ToolsMap::getRadius(p_object, p_object->getPlane());
}

int ToolsMap::getRadius( MapObject* p_object, int p_plane )
{
	int widthPlane = p_object->getWidth(p_plane);
	int heightPlane = p_object->getHeight(p_plane);
	return widthPlane > heightPlane ? widthPlane : heightPlane;
}

Sector::SectorColor ToolsMap::getRandomSectorColor()
{
	return static_cast<Sector::SectorColor>(rand() % Sector::SectorColor::Last);
}

sf::Color ToolsMap::convertSectorColor( Sector::SectorColor p_color )
{
	switch(p_color)
	{
	case Sector::SectorColor::Green:
		return sf::Color(70,125,15);
		break;

	case Sector::SectorColor::GreeYellow:
		return sf::Color(80,110,5);
		break;

	case Sector::SectorColor::GreenBlue:
		return sf::Color(50,170,105);
		break;

	case Sector::SectorColor::Red:
		return sf::Color(190,30,15);
		break;

	case Sector::SectorColor::RedYellow:
		return sf::Color(255,255,110);
		break;

	case Sector::SectorColor::RedOrange:
		return sf::Color(205,75,5);
		break;

	case Sector::SectorColor::Blue:
		return sf::Color(120,130,250);
		break;

	case Sector::SectorColor::BlueAqua:
		return sf::Color(85,155,180);
		break;

	case Sector::SectorColor::BlueViolet:
		return sf::Color(230,100,230);
		break;
	}
}




