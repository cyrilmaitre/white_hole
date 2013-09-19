#include "TextField.h"
#include "ToolsUi.h"
#include "Manager.h"

//******************************
// Define
//******************************
#define DEFAULT_WIDTH						200
#define DEFAULT_HEIGHT						20
#define DEFAULT_COLOR						sf::Color(255,255,0,0)
#define DEFAULT_FONTCOLOR					sf::Color(25,25,25)
#define DEFAULT_BACKGROUNDCOLOR				sf::Color(240,240,240)
#define DEFAULT_BORDERCOLOR					sf::Color(210,210,210)
#define DEFAULT_BORDERCOLOR_OVER			sf::Color(175,175,175)
#define DEFAULT_BORDERCOLOR_FOCUS			sf::Color(110,110,110)
#define DEFAULT_BORDERSIZE					2
#define DEFAULT_TITLE						"TextField:"
#define DEFAULT_TITLE_MARGINRIGHT			10
#define DEFAULT_CURSOR_MARGINTOP			2
#define DEFAULT_CURSOR_MARGINBOTTOM			2
#define DEFAULT_CURSOR_MARGINLEFT			0
#define DEFAULT_VALUE_MARGINTOP				3
#define DEFAULT_VALUE_MARGINBOTTOM			4
#define DEFAULT_VALUE_MARGINLEFT			4
#define DEFAULT_VALUE_MARGINRIGHT			4
#define DEFAULT_VALUE						""
#define CURSOR_TICK							0.6


//******************************
// Constructor - Destructor
//******************************
TextField::TextField( TextFieldType p_type )
{
	this->setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	this->setType(p_type);
	this->setTitle(DEFAULT_TITLE);
	this->setTitleVisibility(false);
	this->setFontColor(DEFAULT_FONTCOLOR);
	this->setBackgroundColor(DEFAULT_BACKGROUNDCOLOR, true);
	this->setBorderColor(DEFAULT_BORDERCOLOR);
	this->setBorderColorFocus(DEFAULT_BORDERCOLOR_FOCUS);
	this->setBorderColorOver(DEFAULT_BORDERCOLOR_OVER);	
	this->setBorderSize(DEFAULT_BORDERSIZE, true);
	
	this->mValueString = DEFAULT_VALUE;
	this->mValueChanged = false;
	this->mSelected = false;
	this->notifyValueChanged();
}

TextField::~TextField(void)
{
}


//******************************
// Getters - Setters
//******************************
std::string TextField::getTitle()
{
	return this->mTitle.getText();
}

void TextField::setTitle( std::string p_title )
{
	if(this->getTitle() != p_title)
	{
		this->mTitle.setText(p_title);
		this->notifyTitleChanged();
	}
}

const sf::Font* TextField::getTitleFont()
{
	return this->mTitle.getFont();
}

void TextField::setTitleFont( sf::Font* p_font )
{
	if(this->mTitle.getFont() != p_font)
	{
		this->mTitle.setFont(p_font);
		this->updateTitlePosition();
	}
}

int TextField::getTitleFontSize()
{
	return this->mTitle.getFontSize();
}

void TextField::setTitleFontSize( int p_size )
{
	if(this->mTitle.getFontSize() != p_size)
	{
		this->mTitle.setFontSize(p_size);
		this->updateTitlePosition();
	}
}

sf::Color TextField::getTitleFontColor()
{
	return this->mTitle.getFontColor();
}

void TextField::setTitleFontColor( sf::Color p_color )
{
	this->mTitle.setFontColor(p_color);
}

bool TextField::getTitleVisibility()
{
	return this->mTitle.isVisible();
}

void TextField::setTitleVisibility( bool p_visibility )
{
	this->mTitle.setVisible(p_visibility);
}

TextField::TextFieldType TextField::getType()
{
	return this->mType;
}

void TextField::setType( TextFieldType p_type )
{
	this->mType = p_type;
}

std::string TextField::getValue()
{
	return this->mValueString;
}

void TextField::setValue( std::string p_buffer )
{
	if(this->mValueString != p_buffer)
	{
		this->mValueString = p_buffer;
		this->notifyValueChanged();
	}
}

bool TextField::isValueChanged()
{
	bool returnValue = this->mValueChanged;
	this->mValueChanged = false;
	return returnValue;
}

void TextField::setValueChanged( bool p_value )
{
	this->mValueChanged = p_value;
}


//******************************
// Methods
//******************************
void TextField::draw()
{
	if(this->isVisible())
	{
		Block::draw();
		this->mTitle.draw();
		this->mValue.draw();
		this->drawCursor();
	}
}

void TextField::drawCursor()
{
	if(this->mSelected) 
	{
		if(this->mClockCursor.getElapsedTimeAsSeconds() < CURSOR_TICK)
			Resource::resource->getApp()->draw(this->mCursor);

		if(this->mClockCursor.getElapsedTimeAsSeconds() > CURSOR_TICK * 2) 
			this->mClockCursor.restart();
	}
}

void TextField::update(sf::Event p_event)
{
	if(this->isVisible())
	{
		Block::update(p_event);
		this->updateSelected(p_event);
		this->updateValue(p_event);
	}
}

void TextField::updateSelected( sf::Event p_event )
{
	if(p_event.type == sf::Event::MouseButtonPressed && p_event.mouseButton.button == sf::Mouse::Left)
	{
		if(this->hasMouseOver() && this->isEnable())
			this->mSelected = true;
		else
			this->mSelected = false;
	}
}

void TextField::updateValue()
{
	std::string tmpBuffer;
	int textWidth;

	// Define tmpBuffer
	if(this->getType() == TextFieldType::TypeText)
	{
		tmpBuffer = this->mValueString;
	}
	else if(this->getType() == TextFieldType::TypePassword)
	{
		for(int i = 0; i < (int)this->mValueString.length(); i++)
		{
			tmpBuffer += "*";
		}
	}
	else
	{
		tmpBuffer = "";
	}

	// Check lenght
	this->mValue.setText(tmpBuffer);
	textWidth = this->mValue.getWidth();
	while(textWidth > 0 && textWidth > (this->getWidth() - DEFAULT_VALUE_MARGINRIGHT))
	{
		tmpBuffer = tmpBuffer.substr(1, tmpBuffer.length());
		this->mValue.setText(tmpBuffer);
		textWidth = this->mValue.getWidth();
	}
}

void TextField::updateValue( sf::Event p_event )
{
	if(this->mSelected)
	{
		if(p_event.type == sf::Event::KeyPressed)
			this->setValue(this->getValue() + ToolsUi::charEntred(p_event));

		if((p_event.type == sf::Event::KeyPressed) && (p_event.key.code == sf::Keyboard::BackSpace))
			this->setValue(this->mValueString.substr(0, this->mValueString.length() - 1));
	}
}

void TextField::clearValue()
{
	this->setValue("");
}

void TextField::notifyTitleChanged()
{
	this->updateTitlePosition();
}

void TextField::notifyFontChanged()
{
	Block::notifyFontChanged();
	this->mValue.setFont(this->mFont);
	this->updateValue();
	this->updateValuePosition();
}

void TextField::notifyFontColorChanged()
{
	Block::notifyFontColorChanged();
	this->mValue.setFontColor(this->mFontColor);
	this->mCursor.setFillColor(this->mFontColor);
}

void TextField::notifyFontSizeChanged()
{
	Block::notifyFontSizeChanged();
	this->mValue.setFontSize(this->mFontSize);
	this->updateHeight();
	this->updateValue();
	this->updateValuePosition();
}

void TextField::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updateTitlePosition();
	this->updateValuePosition();
	this->updateCursorPosition();
}

void TextField::notifySizeChanged()
{
	Block::notifySizeChanged();
	this->updateFontSize();
	this->updateTitlePosition();
	this->updateCursorSize();
	this->updateValue();
	this->updateValuePosition();
}

void TextField::notifyValueChanged()
{
	this->mValueChanged = true;

	this->updateValue();
	this->updateCursorPosition();
}

void TextField::updateTitlePosition()
{
	this->mTitle.setPosition((float)(this->getX() - DEFAULT_TITLE_MARGINRIGHT - this->mTitle.getWidth()), (float)(this->getY() + (this->getHeight() - this->mTitle.getHeight()) / 2));
}

void TextField::updateValuePosition()
{
	this->mValue.setPosition((float)(this->getX() + DEFAULT_VALUE_MARGINLEFT), (float)(this->getY() + (this->getHeight() - this->getFontSize()) / 2));
}

void TextField::updateCursorPosition()
{
	this->mCursor.setPosition((float)(this->mValue.getRightX() + DEFAULT_CURSOR_MARGINLEFT), (float)(this->getY() + DEFAULT_CURSOR_MARGINTOP));
}

void TextField::updateCursorSize()
{
	this->mCursor.setSize(sf::Vector2f(1.f, (float)this->getHeight() - DEFAULT_CURSOR_MARGINTOP - DEFAULT_CURSOR_MARGINBOTTOM));
}

void TextField::updateFontSize()
{
	this->setFontSize(this->getHeight() - DEFAULT_VALUE_MARGINTOP - DEFAULT_VALUE_MARGINBOTTOM);
}

void TextField::updateHeight()
{
	this->setHeight(this->getFontSize() + DEFAULT_VALUE_MARGINTOP + DEFAULT_VALUE_MARGINBOTTOM);
}


