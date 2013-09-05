#pragma once
#include "FieldSet.h"
#include "Button.h"
#include "Character.h"

class StationScreen;

class StationScreenLeftMenu : public FieldSet
{
public:
	// Constructor - Destructor
	StationScreenLeftMenu(Character* p_character, StationScreen* p_screen);
	~StationScreenLeftMenu(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character* p_character);

	StationScreen* getStationScreen();
	void setStationScreen(StationScreen* p_screen);

	static int getWidth();

	// Methods
	void update();
	void updateButtonBank();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyCharacterChanged();
	void notifyPositionChanged();
	void notifySizeChanged();


private:
	// Attributs
	Character* mCharacter;
	StationScreen* mStationScreen;

	Button mButtonHangar;
	Button mButtonMarket;
	Button mButtonCraft;
	Button mButtonShipCargo;
	std::vector<Button*> mButtonBanks;
	Button mButtonUndock;
};

