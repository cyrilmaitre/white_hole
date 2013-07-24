#pragma once
#include "Block.h"
#include "TextBox.h"

class FieldSet : public Block
{
public:
	// Constructor - Destructor
	FieldSet();
	~FieldSet();

	// Getters - Setters
	bool hasTitle();
	std::string getTitle();
	void setTitle(std::string p_title);

	int getPadding();
	void setPadding(int p_padding);

	int getContentWidth();
	int getContentHeight();
	double getContentX();
	double getContentY();

	// Methods
	void draw();
	void update(sf::Event myEvent);


protected:
	// Methods
	void notifyTitleChanged();
	void notifyFontChanged();
	void notifyFontStyleChanged();
	void notifyFontColorChanged();
	void notifyFontSizeChanged();
	void notifyPositionChanged();
	void notifySizeChanged();


private:
	// Attributs
	TextBox mTitle;
	int mPadding;

	// Methods
	void updateTitlePosition();
};

