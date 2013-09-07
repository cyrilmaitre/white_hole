#pragma once
#include "Window.h"
#include "TextBoxMultiLine.h"

// Define
#define WINDOWPOPUP_MARGIN_MESSAGEICON			10

class WindowPopup : public Window
{
public:
	// Constructor - Destructor
	WindowPopup(std::string p_title, std::string p_message, SpriteParameter* p_spriteIconSheet, std::string p_spriteIconIndex, std::string p_windowIconIdex);
	~WindowPopup(void);

	// Getters - Setters
	std::string getMessage();
	void setMessage(std::string p_message);

	std::string getMessageIconIndex();
	void setMessageIconIndex(std::string p_icon);

	// Methods
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyMessageChanged();
	void notifyMessageIconIndexChanged();
	virtual void updateMessageTextBox();
	void updatePosition();
	void update(sf::Event p_event);
	void drawContent();


protected:
	// Attributs
	std::string mMessage;
	std::string mMessageIconIndex;

	TextBoxMultiLine mMessageTextBox;
	SpriteParameter* mMessageIconSprite;
};

