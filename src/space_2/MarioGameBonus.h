#pragma once
#include "MarioGameBlockActive.h"
#include "Clock.h"


class MarioGameBonus : public MarioGameBlockActive
{
public:
	// Enum
	enum BonusState
	{
		ActiveOne,
		ActiveTwo,
		ActiveThree,
		ActiveFour,
		Inactive
	};

	// Constructor - Destructor
	MarioGameBonus(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameBonus(void);

	// Getters - Setters
	BonusState getBonusState();
	void setBonusState(BonusState p_state);

	// Methods
	void update();
	void updateBonusState();
	void notifyBonusStateChanged();
	void BeginContact(b2Contact* p_contact, MarioGameUserData::UserDataIndex p_index);


private:
	// Attributs
	BonusState mBonusState;
	mks::Clock mBonusClock;
};

