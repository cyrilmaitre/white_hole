#pragma once
#include "TextMultiLine.h"

class TextBoxMultiLine : public TextMultiLine
{
public:
	// Constructor - Destructor
	TextBoxMultiLine(bool p_autoResizeHeight = false);
	~TextBoxMultiLine();

	// Methods
	void draw();
	void update(sf::Event p_event);
};

