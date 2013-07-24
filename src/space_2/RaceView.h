#pragma once
#include "Resource.h"
#include "Selectable.h"
#include "Race.h"
#include "TextBox.h"


class RaceView: public Block
{
public:
	// Constructor - Destructor
	RaceView(	Race *p_race = NULL,
				double p_x = 0,
				double p_y = 0);
	~RaceView(void);

	// Getters - Setters
	bool hasRace();
	Race* getRace();
	void setRace(Race *p_race);

	bool isSelectable();
	void setSelectable(bool p_selectable);

	// Methods
	void notifyPositionChanged();
	void notifyRaceChanged();
	void updatePosition();
	void update(sf::Event myEvent);
	void draw();


private:
	// Attributs
	Race *mRace;
	bool mSelectable;
	sf::Sprite *mRaceSprite;
	TextBox *mTBName;
	sf::RectangleShape mOverlayOver;
};

