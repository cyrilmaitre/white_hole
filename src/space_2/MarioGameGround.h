#pragma once
#include "MarioGameBlock.h"


class MarioGameGround : public MarioGameBlock
{
public:
	// Constructor - Destructor
	MarioGameGround(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameGround(void);
};

