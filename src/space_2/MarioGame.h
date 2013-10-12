#pragma once
#include "Object.h"
#include "Box2D/Box2D.h"
#include "Clock.h";
#include "TextBox.h"

class MarioGameMario;
class MarioGameBlock;

// Define
#define MARIOGAME_SPRITE_MARIOIDLE			"0-0"
#define MARIOGAME_SPRITE_MARIORUNONE		"1-0"
#define MARIOGAME_SPRITE_MARIORUNTWO		"2-0"
#define MARIOGAME_SPRITE_MARIORUNTHREE		"3-0"
#define MARIOGAME_SPRITE_MARIOJUMP			"4-0"
#define MARIOGAME_SPRITE_GROUND				"0-1"
#define MARIOGAME_SPRITE_BONUSACTIVEONE		"1-1"
#define MARIOGAME_SPRITE_BONUSACTIVETWO		"2-1"
#define MARIOGAME_SPRITE_BONUSACTIVETHREE	"3-1"
#define MARIOGAME_SPRITE_BONUSACTIVEFOUR	"4-1"
#define MARIOGAME_SPRITE_BONUSINACTIVE		"0-2"
#define MARIOGAME_SPRITE_BRICKONE			"1-2"
#define MARIOGAME_SPRITE_BRICKTWO			"2-2"
#define MARIOGAME_SPRITE_BRICKTHREE			"3-2"
#define MARIOGAME_SPRITE_BRICKFOUR			"4-2"
#define MARIOGAME_SPRITE_BRICKFIVE			"0-3"
#define MARIOGAME_SPRITE_COINONE			"1-3"
#define MARIOGAME_SPRITE_COINTWO			"2-3"
#define MARIOGAME_SPRITE_COINTHREE			"3-3"

class MarioGame : public Object, public b2ContactListener
{
public:
	// Constructor - Destructor
	MarioGame(void);
	~MarioGame(void);
	void destroyWorldBlocks();

	// Getters - Setters
	b2World* getWorld();
	MarioGameBlock* getBlock(int p_x, int p_y);

	// Methods
	void createWorld();
	void createBricks();
	void createBricks(int p_line);
	void createCoins();
	void createCoins(int p_line);

	void update(sf::Event p_event);
	void update();
	void updateFrameRate();
	void updatePosition();
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();

	void BeginContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	static float pixelToMeter(float p_pixel);
	static sf::Vector2f pixelToMeter(sf::Vector2f p_pixel);
	static float meterToPixel(float  p_meter);
	static sf::Vector2f meterToPixel(sf::Vector2f  p_meter);


private:
	// Attributs
	float mFrameRate;
	b2World* mWorld;
	float mWorldTimeStep;
	float mWorldVelocityIter;
	float mWorldPositionIter;
	MarioGameMario* mMario;
	sf::Vector2i mWorldBlocksSize;
	MarioGameBlock*** mWorldBlocks;
	b2Body* mBodyGround;
	mks::Clock mGameClock;
};

