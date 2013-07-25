#pragma once
#include "Block.h"
#include "Ship.h"


class ShipViewSmall : public Block
{
public:
	// Constructor - Destructor
	ShipViewSmall(void);
	~ShipViewSmall(void);

	// Getters - Setters
	bool hasShip();
	Ship* getShip();
	void setShip(Ship* p_ship);

	// Methods
	void notifyPositionChanged();
	void notifyShipChanged();
	void notifySizeChanged();
	void update();
	void updateSpritePosition();
	void updateSpriteSize();
	void updateRotation();
	void draw();


private:
	// Attributs
	Ship* mShip;
	sf::Sprite* mSprite;
	float mRotation;
	mks::Clock mClock;
};

