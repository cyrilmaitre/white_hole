#pragma once
#include "MarioGame.h"
#include "Object.h"

// Define
#define MARIOGAME_BLOCK_WIDTH		32.f
#define MARIOGAME_BLOCK_HEIGHT		32.f

class MarioGameBlock : public Object
{
public:
	// Constructor - Destructor
	MarioGameBlock(MarioGame* p_game, sf::Vector2i p_positionGrid);
	virtual ~MarioGameBlock(void);

	// Methods
	virtual void update();
	void updatePosition();
	virtual void draw();
	void notifyPositionChanged();


protected:
	// Attributs
	MarioGame* mGame;
	sf::Vector2i mPositionGrid;
	sf::Sprite* mSprite;
};

