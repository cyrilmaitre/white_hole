#include "LifeBar.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUND_COLOR				sf::Color(148,15,18)
#define BORDER_COLOR					sf::Color(175,165,155)
#define BORDER_SIZE						1
#define LIFE_BACKGROUND_COLOR			sf::Color(110,100,90)
#define FONT_COLOR						sf::Color(195,195,195)
#define FONT_SIZE						ManagerConfig::FontSize::Tiny


//*************************************************************
// Constructor - Destructor
//*************************************************************
LifeBar::LifeBar( Destructable* p_destructable, LifeBar::LifeBarType p_type )
{
	this->mDestructable = NULL;

	this->setBackgroundColor(BACKGROUND_COLOR, true);
	this->setBorderColor(BORDER_COLOR, true);
	this->setBorderSize(BORDER_SIZE, true);

	this->mLifeBar.setFillColor(LIFE_BACKGROUND_COLOR);
	this->mTextLife.setFontColor(FONT_COLOR);
	this->mTextLife.setFontSize(FONT_SIZE);

	this->setDestructable(p_destructable);
	this->setType(p_type);
}

LifeBar::~LifeBar(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Destructable* LifeBar::getDestructable()
{
	return this->mDestructable;
}

void LifeBar::setDestructable( Destructable *p_destructable )
{
	if(this->mDestructable != p_destructable)
	{
		this->mDestructable = p_destructable;
		this->notifyDestructableChanged();
	}
}

LifeBar::LifeBarType LifeBar::getType()
{
	return this->mType;
}

void LifeBar::setType(LifeBar::LifeBarType p_type)
{
	this->mType = p_type;
}


//*************************************************************
// Methods
//*************************************************************
void LifeBar::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updateTextPosition();
	this->mLifeBar.setPosition(this->getX(), this->getY());
}

void LifeBar::notifyDestructableChanged()
{
	if(this->mDestructable != NULL)
		this->updateBar(true);
}

void LifeBar::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		Block::update(p_event);
		if(this->isClicked())
			this->mTextLife.setVisible(!this->mTextLife.isVisible());
	}
}

void LifeBar::update()
{
	if(this->isVisible())
	{
		this->updateBar();
	}
}

void LifeBar::updateBar(bool p_forceUpdate)
{
	if(this->mDestructable == NULL)
		return;

	if(this->mType == LifeBarType::TypeShield && (this->mDestructable->isShieldChanged() || this->mDestructable->isShieldMaxChanged() || p_forceUpdate))
	{
		this->mLifeBar.setSize(sf::Vector2f(this->getWidth() * (this->mDestructable->getShield() / this->mDestructable->getShieldMax()), this->getHeight()));
		this->mTextLife.setText(Tools::formatNumber((long)this->mDestructable->getShield()) + " / " + Tools::formatNumber((long)this->mDestructable->getShieldMax()));
		this->updateTextPosition();
	}
	else if(this->mType == LifeBarType::TypeArmor && (this->mDestructable->isArmorChanged() || this->mDestructable->isArmorMaxChanged() || p_forceUpdate))
	{
		this->mLifeBar.setSize(sf::Vector2f(this->getWidth() * (this->mDestructable->getArmor() / this->mDestructable->getArmorMax()), this->getHeight()));
		this->mTextLife.setText(Tools::formatNumber((long)this->mDestructable->getArmor()) + " / " + Tools::formatNumber((long)this->mDestructable->getArmorMax()));
		this->updateTextPosition();
	}
	else if(this->mType == LifeBarType::TypeStructure && (this->mDestructable->isStructureChanged() || this->mDestructable->isStructureMaxChanged() || p_forceUpdate))
	{
		this->mLifeBar.setSize(sf::Vector2f(this->getWidth() * (this->mDestructable->getStructure() / this->mDestructable->getStructureMax()), this->getHeight()));
		this->mTextLife.setText(Tools::formatNumber((long)this->mDestructable->getStructure()) + " / " + Tools::formatNumber((long)this->mDestructable->getStructureMax()));
		this->updateTextPosition();
	}
}

void LifeBar::updateTextPosition()
{
	this->mTextLife.setPosition(this->getX() + (this->getWidth() - this->mTextLife.getWidth()) / 2, 
								this->getY() + (this->getHeight() - this->mTextLife.getHeight()) / 2);
}

void LifeBar::draw()
{
	if(this->isVisible())
	{
		Block::draw();
		Resource::resource->getApp()->draw(this->mLifeBar);
		this->mTextLife.draw();
	}
}

