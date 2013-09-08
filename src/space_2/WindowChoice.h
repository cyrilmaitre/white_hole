#pragma once
#include "WindowPopup.h"
#include "Button.h"


class WindowChoice : public WindowPopup
{
public:
	// Constructor - Destructor
	WindowChoice(std::string p_title, std::string p_message, SpriteParameter* p_spriteSheet, std::string p_spriteIndex, std::string p_windowIconIdex, std::string p_buttonYesTitle, std::string p_buttonNoTitle);
	~WindowChoice(void);

	// Getters - Setters

	// Methods
	void notifyPositionChanged();
	void notifySizeChanged();
	void updateMessageTextBox();
	void updatePosition();
	void update(sf::Event p_event);
	void drawContent();


private:
	// Attributs
	Button mButtonYes;
	Button mButtonNo;
};

