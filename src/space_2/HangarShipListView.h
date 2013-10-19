#pragma once
#include "Listable.h"
#include "CharacterShip.h"
#include "Image.h"
#include "TextBox.h"
#include "PopupBubble.h"

// Define
#define HANGARSHIPLISTVIEW_WIDTH	350

class HangarShipListView : public Listable
{
public:
	// Constructor - Destructor
	HangarShipListView(CharacterShip* p_ship);
	~HangarShipListView(void);

	// Getters - Setters
	CharacterShip* getCharacterShip();
	void setCharacterShip(CharacterShip* p_ship);

	// Methods
	void update(sf::Event p_event);
	void updatePosition();
	void draw();
	void notifyShipChanged();
	void notifyPositionChanged();
	void notifySelectedChanged();


private:
	// Attributs
	CharacterShip* mCharacterShip;
	Image mIcon;
	Image mIconPiloted;
	TextBox mTBName;
	TextBox mTBType;
	TextBox mTBLevel;
};

