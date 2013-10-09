#pragma once
#include "FieldSet.h"
#include "Button.h"
#include "Character.h"
#include "WindowChoiceAction.h"
#include "WindowChoiceActionObject.h"

class StationScreen;

class StationScreenLeftMenu : public FieldSet, public WindowChoiceAction
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

	void onButtonTrueClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand);
	void onButtonFalseClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand);


private:
	// Attributs
	Character* mCharacter;
	StationScreen* mStationScreen;

	Button mButtonHangar;
	Button mButtonMarket;
	Button mButtonCraft;
	Button mButtonShipCargo;
	std::vector<Button*> mButtonBanks;
	Button mButtonCharacterSheet;
	Button mButtonShipSheed;
	Button mButtonUndock;

	// Methods 
	void buttonBankClicked(int p_index);
};

