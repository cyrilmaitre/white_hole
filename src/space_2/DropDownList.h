#pragma once
#include "FieldSet.h"
#include "TextBox.h"


class DropDownList : public FieldSet
{
public:
	// Constrcutor - Destructor
	DropDownList(void);
	~DropDownList(void);

	// Methods
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void notifySizeChanged();


private:
	// Attributs
	TextBox mText;
	sf::Sprite* mIconDrop;
};

