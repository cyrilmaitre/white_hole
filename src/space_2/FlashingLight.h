#pragma once
#include "EntityEffect.h"
#include "Clock.h"


class FlashingLight : public EntityEffect
{
public:
	// Enum
	enum LightColor
	{
		Blue = 0,
		Green,
		Grey,
		Purple,
		Red
	};

	// Constructor - Destructor
	FlashingLight(Entity* p_entity, Json::Value p_lightJson);
	~FlashingLight(void);

	// Getters - Setters
	std::string getLightSprite();

	// Methods
	void update();
	void updatePosition();
	void updateFlash();
	void draw();


private:
	// Attributs
	LightColor mLightColor;
	bool mFlashDraw;
	float mFlashTick;
	float mFlashTickMin;
	float mFlashTickMax;

	sf::Sprite mLightSprite;
	sf::Sprite mFlashSprite;

	mks::Clock mFlashClock;

	// Methods
	void computeFlashTick();
};

