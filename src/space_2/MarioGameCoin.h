#pragma once
#include "MarioGameBlock.h"
#include "MarioGameUserData.h"
#include "Clock.h"

// Define
#define MARIOGAME_COIN_WIDTH		20
#define MARIOGAME_COIN_HEIGHT		32

class MarioGameCoin : public MarioGameUserData, public MarioGameBlock
{
public:
	// Enum
	enum CoinState
	{
		ActiveOne,
		ActiveTwo,
		ActiveThree,
		Destroy
	};

	// Constructor - Destructor
	MarioGameCoin(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameCoin(void);

	// Getters - Setters
	CoinState getCoinState();
	void setCoinState(CoinState p_state);

	// Methods
	void update();
	void updateCoinState();
	void notifyCoinStateChanged();

	void PreSolve(b2Contact* p_contact, const b2Manifold* p_oldManifold, UserDataIndex p_index);


private:
	// Attributs
	b2Body* mBodyCoin;
	CoinState mCoinState;
	mks::Clock mCoinClock;
};

