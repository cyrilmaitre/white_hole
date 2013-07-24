#pragma once
#include "WindowSelected.h"
#include "Entity.h"

// Define
#define LIFEBAR_COUNT			3

class WindowSelectedEntity : public WindowSelected
{
public:
	// Constructor - Destructor
	WindowSelectedEntity(Entity* p_entity);
	~WindowSelectedEntity(void);

	// Getters - Setters
	Entity* getEntity();
	void setEntity(Entity* p_entity);

	// Methods
	void notifyPositionChanged();
	void notifyEntityChanged();
	void update();
	void update(sf::Event p_event);
	void updatePosition();
	void drawContent();


private:
	// Attributs
	Entity* mEntity;

	TextBox mTBName;
	TextBox mTBNameValue;
	TextBox mTBLevel;
	TextBox mTBLevelValue;
	TextBox mTBShield;
	TextBox mTBArmor;
	TextBox mTBStructure;
	LifeBar *mLifeBars[LIFEBAR_COUNT];
};

