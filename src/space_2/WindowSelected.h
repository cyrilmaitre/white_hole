#pragma once
#include "Window.h"
#include "MapObject.h"
#include "LifeBar.h"
#include "ManagerConfig.h"

// Define
#define TB_LABEL_FONTCOLOR			sf::Color(195,195,195)
#define TB_LABEL_FONTSIZE			ManagerConfig::FontSize::Small
#define TB_LABEL_OFFSETX			20
#define TB_LABEL_OFFSETY			10
#define TB_VALUE_OFFSETX			8

class WindowSelected : public Window
{
public:
	// Constructor - Destructor
	WindowSelected(void);
	virtual ~WindowSelected(void);

	// Methods
	virtual void notifyPositionChanged();
	virtual void update() = 0;
	virtual void update(sf::Event p_event);
	virtual void drawContent() = 0;
};

