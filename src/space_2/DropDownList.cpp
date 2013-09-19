#include "DropDownList.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR			sf::Color(25, 26, 28)
#define BORDERCOLOR				sf::Color(194, 194, 194)
#define BORDERCOLOR_OVER		sf::Color(215, 215, 215)
#define BORDERSIZE				1
#define PADDING					5


//*************************************************************
// Constructor - Destructor
//*************************************************************
DropDownList::DropDownList(void)
{
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR);
	this->setBorderColorOver(BORDERCOLOR_OVER);
	this->setBorderColorFocus(BORDERCOLOR_OVER);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);
	this->setDisplayTitle(false);

	this->mIconDrop = NULL;
	this->mIconDrop = SpriteParameterFactory::getSpriteParameterIcon16X16()->getSpritePtr(IC_16X16_EXPAND);

	this->setHeight(this->mText.getHeight() + PADDING * 2);
}

DropDownList::~DropDownList(void)
{
	if(this->mIconDrop != NULL)
		delete this->mIconDrop;
}


//*************************************************************
// Methods
//*************************************************************
void DropDownList::updatePosition()
{
	this->mIconDrop->setPosition(	this->getContentX() + this->getContentWidth() - this->mIconDrop->getGlobalBounds().width, 
									this->getContentY() + (this->getContentHeight() - this->mIconDrop->getGlobalBounds().height) / 2);
}

void DropDownList::update( sf::Event p_event )
{
	if(this->isVisible())
	{

	}
	FieldSet::update(p_event);
}

void DropDownList::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		if(this->mIconDrop != NULL)
			Resource::resource->getApp()->draw(*this->mIconDrop);
	}
}

void DropDownList::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}

void DropDownList::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->updatePosition();
}
