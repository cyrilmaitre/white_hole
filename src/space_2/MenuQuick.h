#pragma once
#include "MenuQuickItem.h"

// Define
#define MENUQUICK_ITEM_COUNT		8

class MenuQuick
{
public:
	// Constructor - Destructor
	MenuQuick(void);
	~MenuQuick(void);

	// Methods
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void draw();


private:
	// Attributs
	MenuQuickItem* mMenuItem[MENUQUICK_ITEM_COUNT];
};

