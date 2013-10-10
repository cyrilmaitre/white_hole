#pragma once
#include "Resource.h"
#include "TextBox.h"
#include "View.h"
#include "BackgroundSpace.h"

// Define
#define BASESCREEN_OVERLAY_HEIGHT			150

class BaseScreen
{
public:
	// Constructor - Destructor
	BaseScreen(void);
	~BaseScreen(void);

	// Getters - Setters
	bool isRunning();
	void setRunning(bool p_running);

	// Methods
	virtual void draw();
	virtual void update();
	virtual void updatePosition();
	virtual void hideScreen();
	virtual void showScreen();
	virtual void notifyAppSizeChanged();


protected:
	// Attributs
	sf::Event mEvent;
	bool mRunning;
	sf::Sprite mBackgroundSprite;
	sf::RectangleShape mOverlayBottom;
	sf::RectangleShape mBorderBottom;
	TextBox mGameVersion;
	View *mScreenView;
	sf::Mutex mMutex;
};

