#include "Button.h"
#include "Manager.h"

//******************************
// Define
//******************************
#define DEFAULT_FONTCOLOR					sf::Color(25,25,25)
#define DEFAULT_BACKGROUNDCOLOR				sf::Color(240,240,240)
#define DEFAULT_BORDERCOLOR					sf::Color(210,210,210)
#define DEFAULT_BORDERCOLOR_OVER			sf::Color(175,175,175)
#define DEFAULT_BORDERCOLOR_FOCUS			sf::Color(110,110,110)
#define DEFAULT_WIDTH						150
#define DEFAULT_HEIGHT						25
#define DEFAULT_BORDERSIZE					2
#define DEFAULT_TITLE						""


//******************************
// Constructor - Destructor
//******************************
Button::Button()
{
	this->setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	this->setFontColor(DEFAULT_FONTCOLOR);
	this->setBackgroundColor(DEFAULT_BACKGROUNDCOLOR, true);
	this->setBorderSize(DEFAULT_BORDERSIZE, true);
	this->setBorderColor(DEFAULT_BORDERCOLOR);
	this->setBorderColorFocus(DEFAULT_BORDERCOLOR_FOCUS);
	this->setBorderColorOver(DEFAULT_BORDERCOLOR_OVER);
	this->setTitle(DEFAULT_TITLE);

	this->mClicked = false;
}

Button::~Button(void)
{

}


//******************************
// Getters - Setters
//******************************
std::string Button::getTitle()
{
	return this->mTitle.getText();
}
void Button::setTitle( std::string p_title )
{
	if(this->getTitle() != p_title)
	{
		this->mTitle.setText(p_title);
		this->notifyTitleChanged();
	}
}


//******************************
// Methods
//******************************
void Button::draw()
{
	if(this->isVisible())
	{
		Block::draw();
		this->mTitle.draw();
	}
}

void Button::update( sf::Event p_event )
{
	if(this->isVisible() && this->isEnable())
	{
		Block::update(p_event);
	}
}

void Button::notifyTitleChanged()
{
	this->updateTitlePosition();
}

void Button::notifyFontChanged()
{
	Block::notifyFontChanged();
	this->mTitle.setFont(this->mFont);
	this->updateTitlePosition();
}

void Button::notifyFontColorChanged()
{
	Block::notifyFontColorChanged();
	this->mTitle.setFontColor(this->mFontColor);
}

void Button::notifyFontSizeChanged()
{
	Block::notifyFontSizeChanged();
	this->mTitle.setFontSize(this->mFontSize);
	this->updateTitlePosition();
}

void Button::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updateTitlePosition();
}

void Button::notifySizeChanged()
{
	Block::notifySizeChanged();
	this->updateTitlePosition();
}

void Button::updateTitlePosition()
{
	this->mTitle.setPosition((float)(this->getX() + (this->getWidth() - this->mTitle.getWidth()) / 2), (float)(this->getY() + (this->getHeight() - this->mTitle.getHeight()) / 2));
}
