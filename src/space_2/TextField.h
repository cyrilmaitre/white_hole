#pragma once
#include "Block.h"
#include "Clock.h"
#include "TextBox.h"

class TextField: public Block
{
public:
	// Enum
	enum TextFieldType
	{
		TypeText,
		TypePassword,
		TypeHidden
	};

	// Construtor - Destructor
	TextField(TextFieldType p_type = TextFieldType::TypeText);
	~TextField();

	// Getters - Setters
	std::string getTitle();
	void setTitle(std::string p_title);

	const sf::Font* getTitleFont();
	void setTitleFont(sf::Font* p_font);

	sf::Color getTitleFontColor();
	void setTitleFontColor(sf::Color p_color);

	int getTitleFontSize();
	void setTitleFontSize(int p_size);

	bool getTitleVisibility();
	void setTitleVisibility(bool p_visibility);

	TextFieldType getType();
	void setType(TextFieldType p_type);

	std::string getValue();
	void setValue(std::string p_buffer);

	bool isValueChanged();
	void setValueChanged(bool p_value);

	// Methods
	void clearValue();
	void notifyTitleChanged();
	void notifyFontChanged();
	void notifyFontColorChanged();
	void notifyFontSizeChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyValueChanged();
	void draw();
	void update(sf::Event p_event);


private:
	// Attributs
	TextBox mTitle;
	TextBox mValue;
	bool mValueChanged;
	std::string mValueString;
	sf::RectangleShape mCursor;
	mks::Clock mClockCursor;

	TextFieldType mType;
	bool mSelected;

	// Methods
	void drawTitle();
	void drawBuffer();
	void drawCursor();

	void updateTitlePosition();
	void updateValuePosition();
	void updateCursorPosition();
	void updateCursorSize();
	void updateFontSize();
	void updateHeight();
	void updateSelected(sf::Event p_event);
	void updateValue();
	void updateValue(sf::Event p_event);
};