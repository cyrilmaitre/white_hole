#pragma once
#include "MarioGameBlockActive.h"


class MarioGameBrick : public MarioGameBlockActive
{
public:
	// Constructor - Destructor
	MarioGameBrick(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameBrick(void);

	// Methods
	void update();
};

