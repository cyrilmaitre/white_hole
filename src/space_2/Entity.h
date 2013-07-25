#pragma once
#include "MapObject.h"
#include "Destructable.h"
#include "Rockable.h"
#include "Equipable.h"
#include "EntityTarget.h"
#include "Rotable.h"
#include "EntityData.h"
#include "FlashingLight.h"

// Define
#define ENTITY_BORDER_FOCUS_SIZE			1
#define ENTITY_BORDER_FOCUS_COLOR			sf::Color(200, 200, 200, 50)
#define ENTITY_BORDER_SELECTED_SIZE			2
#define ENTITY_BORDER_SELECTED_COLOR		sf::Color(225, 225, 225, 125)
#define ENTITY_DISTANCE_OFFSETY				10
#define ENTITY_DISTANCE_FONT_COLOR			sf::Color(225, 225, 225, 125)
#define ENTITY_DISTANCE_FONT_SIZE			12

class Entity: public MapObject, public Destructable, public Rockable, public Equipable, public Rotable, public EntityData
{
public:
	// Constructor - Destructor
	Entity(int p_plane = MAPOBJECT_PLANE_1);
	~Entity(void);

	// Getters - Setters
	EntityTarget* getTarget();
	bool isDestroy();

	// Methods
	void update();
	void updateShieldSprite();
	void updateSprite();
	void update(sf::Event p_event);
	void draw();
	void loadSprite();
	void unloadSprite();
	void destroy();
	void shieldImpact();
	void notifyRotationChanged();
	void notifyFlashingLightJsonChanged();


private:
	// Attributs
	EntityTarget mTarget;
	sf::Sprite *mShieldSprite;
	mks::Clock mShieldClock;
	TextBox mTBDistance;

	std::vector<FlashingLight*> mFlashingLights;
};

