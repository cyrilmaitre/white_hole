#pragma once
#include "Resource.h"
#include <map>

// Define
#define EVENTMANAGER_SFML_KEY_CODE_NUMBER	101

class EventManager
{
public:
	// Constructor - Destructor
	EventManager();
	~EventManager(void);

	// Getters - Setters
	sf::Vector2i getMousePositionUiLocal();
	sf::Vector2i getMousePositionUiGlobal();

	sf::Vector2f getMousePositionMapLocal(int p_plane);
	sf::Vector2f getMousePositionMapGlobal(int p_plane);

	bool isMouseOverEvent();
	void setMouseOverEvent(bool p_raised);

	
	// Methods
	void reset();
	void resetMouseOverEvent();
	void raiseMouseOverEvent();
	void handlePlayerAction(sf::Event p_event);
	void handlePlayerActionPre();
	void handlePlayerActionPost();
	
	// Static
	static EventManager *eventManager;


private:
	// Attributs
	bool mMouseOverEvent;
};

