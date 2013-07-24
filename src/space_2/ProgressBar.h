#pragma once
#include "Block.h"
#include "TextBox.h"

class ProgressBar : public Block
{
public:
	// Enum
	enum UiProgressBarMode 
	{
		ModeNone = 0,
		ModeValueMax,
		ModePercent,
		ModeTitle
	};

	// Constructor - Destructor
	ProgressBar(void);
	~ProgressBar(void);

	// Getters - Setters
	double getValue();
	double getValuePercent();
	void setValue(double p_value);

	double getValueMin();
	void setValueMin(double p_min);

	double getValueMax();
	void setValueMax(double p_max);

	std::string getTitle();
	void setTitle(std::string p_title);

	UiProgressBarMode getMode();
	void setMode(UiProgressBarMode p_mode);

	sf::Color getBarColor();
	void setBarColor(sf::Color p_color);

	// Methods
			
	void update(sf::Event myEvent);
	void updatePosition();
	void updateBar();
	void updateText();
	void draw();


protected:
	// Methods
	void notifyFontChanged();
	void notifyFontColorChanged();
	void notifyFontSizeChanged();
	void notifySizeChanged();
	void notifyPositionChanged();
	void notifyValueChanged();


private:
	// Attributs
	double mValue;
	double mValueMin;
	double mValueMax;
	std::string mTitle;
	UiProgressBarMode mMode;

	TextBox mText;

	sf::RectangleShape mBar;
	sf::Color mBarColor;
};