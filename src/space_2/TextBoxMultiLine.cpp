#include "TextBoxMultiLine.h"

//******************************
// Constructor - Destructor
//******************************
TextBoxMultiLine::TextBoxMultiLine( bool p_autoResizeHeight ) : TextMultiLine(p_autoResizeHeight)
{
	
}

TextBoxMultiLine::~TextBoxMultiLine(void)
{

}


//******************************
// Methods
//******************************
void TextBoxMultiLine::draw()
{
	if(this->isVisible())
		TextMultiLine::draw();
}

void TextBoxMultiLine::update( sf::Event p_event )
{
	if(this->isVisible())
		TextMultiLine::update(p_event);
}



