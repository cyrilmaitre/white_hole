#pragma once
#include "MapObject.h"
#include "Destructable.h"
#include "Rockable.h"
#include "Equipable.h"
#include "EntityTarget.h"
#include "EntityData.h"
#include "FlashingLightEffect.h"
#include "RadarEffect.h"
#include "TurretEffect.h"
#include "WeaponEffect.h"

class NpcType;

// Define
#define ENTITY_BORDER_FOCUS_SIZE			1
#define ENTITY_BORDER_FOCUS_COLOR			sf::Color(200, 200, 200, 50)
#define ENTITY_BORDER_SELECTED_SIZE			2
#define ENTITY_BORDER_SELECTED_COLOR		sf::Color(225, 225, 225, 125)
#define ENTITY_DISTANCE_OFFSETY				10
#define ENTITY_DISTANCE_FONT_COLOR			sf::Color(225, 225, 225, 125)
#define ENTITY_DISTANCE_FONT_SIZE			12

class Entity: public MapObject, public Destructable, public Rockable, public Equipable, public EntityData
{
public:
	// Constructor - Destructor
	Entity(int p_plane = MAPOBJECT_PLANE_1);
	~Entity(void);

	// Getters - Setters
	EntityTarget* getTarget();
	
	double getTargetOffsetX();
	void setTargetOffsetX(double p_x);

	double getTargetOffsetY();
	void setTargetOffsetY(double p_y);

	bool isDestroy();
	WeaponEffect* getWeaponToFire();

	// Methods
	void addWeaponEffect(WeaponEffect* p_weapon);
	void update();
	void updateShieldSprite();
	void updateSprite();
	void update(sf::Event p_event);
	void draw();
	void loadSprite();
	void unloadSprite();
	void destroy();
	void shieldImpact();
	void selectNextWeapon();
	void notifyNpcTypeChanged(NpcType* p_type);
	void notifyRotationChanged();
	void notifyFlashingLightJsonChanged();
	void notifyRadarJsonChanged();
	void notifyTurretJsonChanged();
	void notifyWeaponJsonChanged();
	void notifyTargetChanged();


private:
	// Attributs
	EntityTarget mTarget;
	double mTargetOffsetX;
	double mTargetOffsetY;
	sf::Sprite *mShieldSprite;
	mks::Clock mShieldClock;
	TextBox mTBDistance;

	std::vector<FlashingLightEffect*> mFlashingLightEffects;
	std::vector<RadarEffect*> mRadarEffects;
	std::vector<TurretEffect*> mTurretEffects;
	std::vector<WeaponEffect*> mWeaponEffects;
	int mWeaponEffectCurrent;
};

