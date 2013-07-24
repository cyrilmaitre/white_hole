#pragma once
#include "Listable.h"

class Text: public Listable
{
public:
	// Constructor - Destructor
	Text();
	~Text();

	// Getters - Setters
	std::string getText();
	virtual bool setText(std::string p_text);

	// Methods
	virtual void notifyTextChanged();


protected:
	// Attributs
	std::string mText;
};

