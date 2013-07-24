#pragma once
#include "Block.h"
#include "TextBox.h"

class Button: public Block
{
public:
	// Constructor - Destructor
	Button();
	~Button();

	// Getters - Setters
	std::string getTitle();
	void setTitle(std::string p_title);

	// Methods
	void draw();
	void update(sf::Event p_event);


protected:
	// Methods
	void notifyTitleChanged();
	void notifyFontChanged();
	void notifyFontColorChanged();
	void notifyFontSizeChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
	void updateTitlePosition();


private:
	// Attributs
	TextBox mTitle;
};
