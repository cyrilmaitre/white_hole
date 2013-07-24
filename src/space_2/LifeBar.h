#pragma once
#include "Block.h"
#include "Destructable.h"
#include "TextBox.h"
#include "Clock.h"

class LifeBar : public Block
{
public:
	// Enum
	enum LifeBarType
	{
		TypeShield = 0,
		TypeArmor,
		TypeStructure
	};

	// Constructor - Destructor
	LifeBar(Destructable* p_destructable, LifeBarType p_type);
	~LifeBar(void);

	// Getters - Setters
	Destructable* getDestructable();
	void setDestructable(Destructable* p_destructable);

	LifeBarType getType();
	void setType(LifeBarType p_type);

	// Methods
	void notifyDestructableChanged();
	void notifyPositionChanged();
	void update();
	void update(sf::Event p_event);
	void updateBar(bool p_forceUpdate = false);
	void updateTextPosition();
	void draw();


private:
	// Atrributs
	Destructable* mDestructable;
	LifeBarType mType;

	TextBox mTextLife;
	sf::RectangleShape mLifeBar;
};

