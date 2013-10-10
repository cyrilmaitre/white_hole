#pragma once
#include "MarioGame.h"

// Define
#define MARIOGAME_BLOCK_WIDTH		32.f
#define MARIOGAME_BLOCK_HEIGHT		32.f

class MarioGameBlock
{
public:
	// Constructor - Destructor
	MarioGameBlock(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameBlock(void);

	// Methods
	virtual void update();
	virtual void draw();


protected:
	// Attributs
	MarioGame* mGame;
	sf::Vector2i mPositionGrid;
	b2World* mWorld;
	b2Body* mBody;
	sf::Sprite* mSprite;
};

