#pragma once
#include "Window.h"
#include "Button.h"
#include "MapMiniView.h"
#include "TextBox.h"


class WindowMap : public Window
{
public:
	// Constructor - Destructor
	WindowMap(void);
	~WindowMap(void);

	// Getters - Setters
	MapMiniView* getMapView();

	int getZoomLevel();
	void setZoomLevel(int p_level);

	// Methods
	void incZoomLevel();
	void decZoomLevel();

	void notifyPositionChanged();
	void update();
	void update(sf::Event p_event);
	void drawContent();


private:
	// Attributs
	MapMiniView* mMapView;
	int mZoomLevel;
	std::vector<float> mZoomLevels;

	Button mButtonZoom;
	Button mButtonDezoom;
	TextBox mTBZoom;
};

