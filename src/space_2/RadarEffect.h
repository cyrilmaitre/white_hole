#pragma once
#include "EntityEffect.h"
#include "Rotable.h"
#include "Clock.h"


class RadarEffect : public EntityEffect, public Rotable
{
public:
	// Enum
	enum RadarEffectType
	{
		Normal = 0,
		RotationInfinite
	};

	// Constructor - Destructor
	RadarEffect(Entity* p_entity, Json::Value p_radarJson);
	~RadarEffect(void);

	// Getters - Setters
	RadarEffectType getRadarType();
	void setRadarType(RadarEffectType p_type);

	// Methods
	void update();
	void updateRadar();
	void updatePosition();
	void draw();
	void notifyRadarTypeChanged();
	void computeRadarRotationTick();


private:
	// Attributs
	RadarEffectType mRadarType;
	sf::Sprite mRadarSprite;
	float mRadarRotationTick;
	mks::Clock mRadarClock;
};

