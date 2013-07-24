#pragma once
#include "Button.h"
#include "PopupBubble.h"

// Define
#define MENUQUICK_ITEM_WIDTH					30
#define MENUQUICK_ITEM_HEIGHT					30
#define MENUQUICK_ITEM_COLOR					sf::Color(39, 39, 39)
#define MENUQUICK_ITEM_BORDERSIZE				1
#define MENUQUICK_ITEM_BORDERCOLOR				sf::Color(24, 24, 24)
#define MENUQUICK_ITEM_BORDERCOLOR_FOCUS		sf::Color(10, 10, 10)
#define MENUQUICK_INFO_WIDTH					200

class MenuQuickItem : public Button
{
public:
	// Constructor - Destructor
	MenuQuickItem(void);
	~MenuQuickItem(void);

	// Methods
	void update();
	void update(sf::Event p_event);
	void draw();
	virtual void notifyItemClicked() = 0;


protected:
	// Attributs
	PopupBubble* mInfo;
};

