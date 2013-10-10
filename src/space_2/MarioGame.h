#pragma once
#include "Object.h"
#include "Box2D/Box2D.h"

class MarioGameMario;
class MarioGameBlock;

// Define
#define MARIOGAME_SPRITE_MARIOIDLE			"0-0"
#define MARIOGAME_SPRITE_MARIORUNONE		"1-0"
#define MARIOGAME_SPRITE_MARIORUNTWO		"2-0"
#define MARIOGAME_SPRITE_MARIORUNTHREE		"3-0"
#define MARIOGAME_SPRITE_MARIOJUMP			"4-0"
#define MARIOGAME_SPRITE_GROUND				"0-1"
#define MARIOGAME_SPRITE_BONUSACTIVE		"1-1"
#define MARIOGAME_SPRITE_BONUSINACTIVE		"2-1"
#define MARIOGAME_SPRITE_BRICK				"3-1"
#define MARIOGAME_SPRITE_COIN				"4-1"

class MarioGame : public Object
{
public:
	// Constructor - Destructor
	MarioGame(void);
	~MarioGame(void);
	void destroyWorldBlocks();

	// Getters - Setters
	b2World* getWorld();

	// Methods
	void createWorldBlocks();

	void update(sf::Event p_event);
	void update();
	void updatePosition();
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();


private:
	// Attributs
	b2World* mWorld;
	float mWorldTimeStep;
	float mWorldVelocityIter;
	float mWorldPositionIter;
	MarioGameMario* mMario;
	sf::Vector2i mWorldBlocksSize;
	MarioGameBlock*** mWorldBlocks;
};

