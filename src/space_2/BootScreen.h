#pragma once
#include "Resource.h"


class BootScreen
{
public:
	// Constructor - Destructor
	BootScreen(sf::RenderWindow *p_myApp);
	~BootScreen(void);

	// Methode
	void launch();
	void update();
	void draw();

	// Static
	static bool isRunning;


public:
	// Attributs
	sf::RenderWindow *mApp;
	sf::Image mImageBackground;
	sf::Texture mTextureBackground;
	sf::Sprite mSpriteBackground;
};

