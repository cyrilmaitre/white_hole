#include "FieldSet.h"
#include "Manager.h"
#include "ManagerConfig.h"

//******************************
// Define
//******************************
#define DEFAULT_WIDTH						600
#define DEFAULT_HEIGHT						400
#define DEFAULT_FONTSIZE					ManagerConfig::FontSize::Huge
#define DEFAULT_FONTSTYLE					sf::Text::Bold
#define DEFAULT_BACKGROUNDCOLOR				sf::Color(128,128,128,75)
#define DEFAULT_BORDERCOLOR					sf::Color(128,128,128,125)
#define DEFAULT_BORDERSIZE					1
#define DEFAULT_PADDING						5
#define DEFAULT_TITLE						"Fieldset"
#define TITLE_MARGINTOP						10


//******************************
// Constructor - Destructor
//******************************
FieldSet::FieldSet()
{
	this->setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	this->setFontStyle(DEFAULT_FONTSTYLE);
	this->setFontSize(DEFAULT_FONTSIZE);
	this->setBackgroundColor(DEFAULT_BACKGROUNDCOLOR, true);
	this->setBorderColor(DEFAULT_BORDERCOLOR, true);
	this->setBorderSize(DEFAULT_BORDERSIZE, true);
	this->setPadding(DEFAULT_PADDING);
	this->setTitle(DEFAULT_TITLE);
	this->setDisplayTitle(true);
}

FieldSet::~FieldSet(void)
{
}


//******************************
// Getters - Setters
//******************************
bool FieldSet::hasTitle()
{
	return this->getTitle() != "";
}

std::string FieldSet::getTitle()
{
	return this->mTitle.getText();
}

void FieldSet::setTitle( std::string p_title )
{
	if(this->getTitle() != p_title)
	{
		this->mTitle.setText(p_title);
		this->notifyTitleChanged();
	}
}

bool FieldSet::isDisplayTitle()
{
	return this->mDisplayTitle;
}

void FieldSet::setDisplayTitle( bool p_display )
{
	this->mDisplayTitle = p_display;
}

int FieldSet::getPadding()
{
	return this->mPadding;
}

void FieldSet::setPadding( int p_padding )
{
	this->mPadding = p_padding;
}

int FieldSet::getContentWidth()
{
	return this->getWidth() - this->getPadding() * 2;
}

int FieldSet::getContentHeight()
{
	if(this->hasTitle())
		return this->getHeight() - this->getPadding() * 2 - this->mTitle.getHeight() - TITLE_MARGINTOP;
	else
		return this->getHeight() - this->getPadding() * 2;
}

double FieldSet::getContentX()
{
	return this->getX() + this->getPadding();
}

double FieldSet::getContentY()
{
	if(this->hasTitle())
		return this->mTitle.getBottomY() + TITLE_MARGINTOP + this->getPadding();
	else
		return this->getY() + this->getPadding();
}


//******************************
// Methods
//******************************
void FieldSet::draw()
{
	if(this->isVisible())
	{
		Block::draw();
		if(this->isDisplayTitle())
			this->mTitle.draw();
	}
}

void FieldSet::update( sf::Event myEvent )
{
	if(this->isVisible())
	{
		Block::update(myEvent);
	}
}

void FieldSet::notifyTitleChanged()
{
	this->updateTitlePosition();
}

void FieldSet::notifyFontChanged()
{
	Block::notifyFontChanged();
	this->mTitle.setFont(this->mFont);
	this->updateTitlePosition();
}

void FieldSet::notifyFontStyleChanged()
{
	Block::notifyFontStyleChanged();
	this->mTitle.setFontStyle(this->mFontStyle);
	this->updateTitlePosition();
}

void FieldSet::notifyFontColorChanged()
{
	Block::notifyFontColorChanged();
	this->mTitle.setFontColor(this->mFontColor);
}

void FieldSet::notifyFontSizeChanged()
{
	Block::notifyFontSizeChanged();
	this->mTitle.setFontSize(this->mFontSize);
	this->updateTitlePosition();
}

void FieldSet::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updateTitlePosition();
}

void FieldSet::notifySizeChanged()
{
	Block::notifySizeChanged();
	this->updateTitlePosition();
}

void FieldSet::updateTitlePosition()
{
	this->mTitle.setPosition((float)(this->getX() + (this->getWidth() - this->mTitle.getWidth()) / 2), (float)(this->getY() + TITLE_MARGINTOP));
}







