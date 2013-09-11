#pragma once
#include "Resource.h"
#include "ImageGIF.h"
#include "WeaponType.h"
#include "Effect.h"
#include "EntityTarget.h"


class Entity;

class Impact : public Effect
{
public:
	// Enum
	enum ImpactType
	{
		Bullet = 0,
		Laser,
		Explosion
	};

	// Constructor - Destructor
	Impact(Entity* p_target, int p_offsetX, int p_offsetY, float p_scale = 1);
	~Impact(void);

	// Getters - Setters
	EntityTarget* getTarget();

	float getScale();
	void setScale(float p_scale);

	int getOffsetX();
	void setOffsetX(int p_x);

	int getOffsetY();
	void setOffsetY(int p_y);

	// Methods
	void update();
	void updatePosition();
	void draw();
	void notifyScaleChanged();


protected:
	// Attributs
	sf::Sprite *mImpactSprite;
	ImageGIF *mImpactGif;
	float mScale;

	EntityTarget mTarget;
	int mOffsetX;
	int mOffsetY;
};

