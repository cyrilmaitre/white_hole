#pragma once
#include "BaseScreen.h"
#include "User.h"
#include "SelectCharacterScreen.h"
#include "Button.h"
#include "FieldSet.h"
#include "TextBox.h"
#include "ImageGIF.h"
#include "TextField.h"
#include "DebugScreen.h"


class TitleScreen: public BaseScreen
{
public:
	// Constructor - Destructor
	TitleScreen(void);
	~TitleScreen(void);

	// Getters - Setters

	// Methode
	void launch();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void authenticateRequest();
	void launchSelectScreen();
	void launchDebugScreen();
	void launchLogin();
	void launchOption();
	void launchQuit();
	void showScreen();


private:
	// Attributs
	sf::Thread *mAuthenticateThread;
	TextBox mGameTitle;
	TextBox mGameTitleWelcome;
	TextField mTextFieldUsername;
	TextField mTextFieldPassword;
	Button mButtonLogin;
	Button mButtonOption;
	Button mButtonQuit;
	Button mButtonDebug;
	ImageGIF* mGIFLoading;
	TextBox mTextBoxLoginFailed;
	SelectCharacterScreen *mSelectScreen;
	DebugScreen* mDebugScreen;
};

