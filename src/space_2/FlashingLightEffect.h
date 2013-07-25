#pragma once
#include "EntityEffect.h"
#include "Clock.h"


class FlashingLightEffect : public EntityEffect
{
public:
	// Enum
	enum LightColor
	{
		Blue = 0,
		Green = 1,
		Grey = 2,
		Purple = 3,
		Red = 4
	};

	// Constructor - Destructor
	FlashingLightEffect(Entity* p_entity, Json::Value p_lightJson);
	~FlashingLightEffect(void);

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

