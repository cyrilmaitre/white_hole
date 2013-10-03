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

	// Getters - Setters
	User* getUser();
	void setUser(User* p_user);

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
	void notifyUserChanged();


private:
	// Attributs
	User* mUser;

	FieldSet mFieldsetSelect;
	Button mButtonOption;
	Button mButtonLogout;
	Button mButtonCreateNew;
	Button mButtonPlay;
	ListSelectableGroup mCharactersList;
	CharacterViewSelect mCharacterSelectedView;

	CreateCharacterScreen mCreateScreen;
};

