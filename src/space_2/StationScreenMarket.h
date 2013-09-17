#pragma once
#include "StationScreenRightPanel.h"
#include "Button.h"

class StationScreenMarketBuy;
class StationScreenMarketSell;


class StationScreenMarket : public StationScreenRightPanel
{
public:
	// Constructor - Destructor
	StationScreenMarket(Character* p_character, Station* p_station, StationScreen* p_screen);
	~StationScreenMarket(void);

	// Getters - Setters
	StationScreenMarketBuy* getScreenBuy();
	StationScreenMarketSell* getScreenSell();

	// Methods
	void loadScreenBuy();
	void loadScreenSell();	
	void unload();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifySizeChanged();
	void notifyPositionChanged();


private:
	// Attributs
	StationScreenMarketBuy* mScreenBuy;
	StationScreenMarketSell* mScreenSell;

	Button mButtonBuy;
	Button mButtonSell;
};

