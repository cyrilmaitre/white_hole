#pragma once
#include "MarioGameBlock.h"


class MarioGameBonus : public MarioGameBlock
{
public:
	// Constructor - Destructor
	MarioGameBonus(MarioGame* p_game, sf::Vector2i p_positionGrid);
	~MarioGameBonus(void);

	// Getters - Setters
	bool isActive();
	void setActive(bool p_active);

	// Methods
	void notifyActiveChanged();


private:
	// Attributs
	bool mActive;
};

