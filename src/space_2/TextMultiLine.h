#pragma once
#include "List.h"

class TextMultiLine : public List
{
public:
	// Constructor - Destructor
	TextMultiLine(bool p_autoResizeHeight = false);
	~TextMultiLine();

	// Getters - Setters
	std::string getText();
	void setText(std::string p_text);

	std::string getDelimeter();
	void setDelimeter(std::string p_delimeter);

	int getInterlineSize();
	void setInterlineSize(int p_size);

	// Methods
	void addLine(std::string p_text, bool p_notify = true);
	void addLineBlank(bool p_notify = true);

	void draw();
	void update(sf::Event p_event);
	

protected:
	// Methods
	void updateLine();
	void notifySizeChanged();
	void notifyTextChanged();


private:
	// Attributs
	std::string mText;
	std::string mDelimeter;

	// Methods
	void addLineTextBox(std::string p_text, bool p_notify = true);
};