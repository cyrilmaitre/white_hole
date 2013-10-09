#pragma once
#include "BaseScreen.h"
#include "TextBox.h"
#include "ImageGIF.h"


class UnloadingGameScreen : public BaseScreen
{
public:
	// Constructor - Destructor
	UnloadingGameScreen(void);
	~UnloadingGameScreen(void);

	// Methods
	void launch();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	TextBox mTBUnloading;
	ImageGIF* mGifUnloading;
};

