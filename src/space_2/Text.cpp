#include "Text.h"

//******************************
// Constructor - Destructor
//******************************
Text::Text()
{
	this->mText = "";
	this->notifyTextChanged();
}

Text::~Text(void)
{
}


//******************************
// Getters - Setters
//******************************
std::string Text::getText()
{
	return this->mText;
}

bool Text::setText( std::string p_text )
{
	if(this->mText != p_text)
	{
		this->mText = p_text;
		this->notifyTextChanged();
		return true;
	}
	return false;
}


//******************************
// Methods
//******************************
void Text::notifyTextChanged()
{

}
