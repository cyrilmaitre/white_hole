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
#define AUTORESIZEHEIGHT_MAX	300


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

	this->mDropDown.setAutoResizeHeightMax(AUTORESIZEHEIGHT_MAX);
	this->mDropDown.setAutoResizeHeight(true);
	this->mDropDown.setAutoResizeWidth(false);
	this->mDropDown.setForceScrollBar(true);

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
void DropDownList::addDropDownable( DropDownable* p_dropDownable )
{
	p_dropDownable->setWidth(this->mDropDown.getContentWidth());
	this->mDropDown.addItem(p_dropDownable);
}

void DropDownList::removeDropDownable( DropDownable* p_dropDownable )
{
	this->mDropDown.removeItem(p_dropDownable);
}

DropDownable* DropDownList::getSelectedDropDownable()
{
	return (DropDownable*)this->mDropDown.getSelection();
}

void DropDownList::updatePosition()
{
	this->mText.setPosition(this->getContentX(), this->getContentY());
	this->mIconDrop->setPosition(	this->getContentX() + this->getContentWidth() - this->mIconDrop->getGlobalBounds().width, 
									this->getContentY() + (this->getContentHeight() - this->mIconDrop->getGlobalBounds().height) / 2);
	this->mDropDown.setPosition(this->getX(), this->getBottomY() + this->mDropDown.getBorderSize());
}

void DropDownList::update()
{
	if(this->mDropDown.isSelectionChanged())
		this->notifyDropDownableChanged();
}

void DropDownList::update( sf::Event p_event )
{
	FieldSet::update(p_event);

	bool dropDownCanBeVisible = !this->mDropDown.isVisible();
	this->mDropDown.update(p_event);

	if(this->isClicked() && dropDownCanBeVisible)
		this->mDropDown.setVisible(!this->mDropDown.isVisible());
}

void DropDownList::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mText.draw();
		if(this->mIconDrop != NULL)
			Resource::resource->getApp()->draw(*this->mIconDrop);
		this->mDropDown.draw();
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
	this->mDropDown.setWidth(this->getWidth());
	this->mText.setWidth(this->getContentWidth() - this->mIconDrop->getGlobalBounds().width);
}

void DropDownList::notifyDropDownableChanged()
{
	this->mText.setText(this->getSelectedDropDownable()->getText());
}

