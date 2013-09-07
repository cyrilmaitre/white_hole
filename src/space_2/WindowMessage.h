#pragma once
#include "WindowPopup.h"
#include "Button.h"


class WindowMessage : public WindowPopup
{
public:
	// Constructor - Destructor
	WindowMessage(std::string p_title, std::string p_message, SpriteParameter* p_spriteSheet, std::string p_spriteIndex, std::string p_windowIconIdex);
	~WindowMessage(void);

	// Methods
	void notifyPositionChanged();
	void notifySizeChanged();
	void updateMessageTextBox();
	void updatePosition();
	void update(sf::Event p_event);
	void drawContent();


private:
	// Attributs
	Button mButtonOk;
};

