#pragma once
#include "Resource.h"
#include "BaseScreen.h"
#include "CreateCharacterScreen.h"
#include "ListSelectableGroup.h"
#include "TextBoxMultiLine.h"
#include "SelectableGroup.h"
#include "CharacterViewSelectSmall.h"
#include "CharacterViewSelect.h"


class SelectCharacterScreen: public BaseScreen
{
public:
	// Constructor - Destructor
	SelectCharacterScreen(void);
	~SelectCharacterScreen(void);

	// Methods
	void launch();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void launchLogout();
	void launchOption();
	void launchCreateNew();
	void launchPlay();


private:
	// Attributs
	FieldSet mFieldsetSelect;
	Button mButtonOption;
	Button mButtonLogout;
	Button mButtonCreateNew;
	Button mButtonPlay;
	CreateCharacterScreen *mCreateScreen;
	ListSelectableGroup mCharactersList;
	CharacterViewSelect *mCharacterSelectedView;
};

