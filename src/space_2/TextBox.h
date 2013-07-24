#pragma once
#include "Text.h"

class TextBox: public Text
{
public:
	// Construtor - Destructor
	TextBox();
	~TextBox();

	// Getters - Setters
	bool isAutoResize();
	void setAutoResize(bool p_auto);

	// Methods
	void draw();
	void update(sf::Event p_event);


protected:
	// Methods
	void notifyFontChanged();
	void notifyFontColorChanged();
	void notifyFontSizeChanged();
	void notifyFontStyleChanged();
	void notifyTextChanged();
	void notifyPositionChanged();


private:
	// Attributs
	sf::Text mText;
	bool mAutoResize;

	// Methods
	void updateText();
	void updateTextPosition();
};

