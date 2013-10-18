#pragma once
#include "FieldSet.h"
#include "ItemStack.h"
#include "ContainerStack.h"
#include "ContainerStackView.h"
#include "Button.h"
#include "Character.h"


class HangarShipAddView : public FieldSet
{
public:
	// Constructor - Destructor
	HangarShipAddView(void);
	~HangarShipAddView(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character* p_character);

	bool isNewShipAdded();
	void setNewShipAdded(bool p_value);

	// Methods
	void addNewCharacterShip();
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void updateButtonAdd();
	void draw();
	void notifySizeChanged();
	void notifyPositionChanged();
	void notifyNewShipAdded();


private:
	// Attributs
	Character* mCharacter;
	ContainerStack mContainerStack;
	ContainerStackView mContainerStackView;
	Button mButtonAdd;
	bool mNewShipAdded;
};

