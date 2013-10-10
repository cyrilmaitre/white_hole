#pragma once
#include "MarioGame.h"

// Define 
#define MARIOGAME_MARIO_WIDTH		32
#define MARIOGAME_MARIO_HEIGHT		32

class MarioGameMario
{
public:
	// Constructor - Destructor
	MarioGameMario(MarioGame* p_game);
	~MarioGameMario(void);

	// Methods
	void update();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	MarioGame* mGame;
	b2World* mWorld;
	b2Body* mBody;
	sf::Sprite* mSprite;
};

