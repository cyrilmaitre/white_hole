#pragma once
#include "FieldSet.h"
#include "TextBox.h"
#include "Button.h"
#include "Character.h"
#include "WindowChoiceAction.h"


class HangarSlotManagementView : public FieldSet, public WindowChoiceAction
{
public:
	// Constructor - Destructor
	HangarSlotManagementView(void);
	~HangarSlotManagementView(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character* p_character);

	// Methods
	void addSlot();
	void addSlotConfirmation();
	void update(sf::Event p_event);
	void updateTBSlots();
	void updatePosition();
	void updateTBSlotsPosition();
	void draw();
	void notifyCharacterChanged();
	void notifyPositionChanged();

	void onButtonTrueClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand);
	void onButtonFalseClicked(WindowChoiceActionObject* p_object, std::string p_actionCommand);


private:
	// Attributs
	Character* mCharacter;
	TextBox mTBSlots;
	Button mButtonAddSlot;
	TextBox mTBSlotPrice;
};

