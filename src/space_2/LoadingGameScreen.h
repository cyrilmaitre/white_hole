#pragma once
#include "BaseScreen.h"
#include "TextBox.h"


class LoadingGameScreen : public BaseScreen
{
public:
	// Constructor - Destructor 
	LoadingGameScreen(void);
	~LoadingGameScreen(void);

	// Methods
	void launch();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	TextBox mTBLoading;
};

