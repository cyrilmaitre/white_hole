#pragma once
#include "MarioGameBlock.h"


class MarioGameBrick : public MarioGameBlock
{
public:
	// Constructor - Destructor
	MarioGameBrick(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameBrick(void);
};

