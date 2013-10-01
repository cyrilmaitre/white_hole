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

	// Methods
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void draw();
	void notifySizeChanged();
	void notifyPositionChanged();


private:
	// Attributs
	Character* mCharacter;
	ContainerStack mContainerStack;
	ContainerStackView mContainerStackView;
	Button mButtonAdd;
};

