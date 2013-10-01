#include "HangarShipAddView.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR					sf::Color(25, 26, 28)
#define BORDERCOLOR						sf::Color(194, 194, 194)
#define BORDERSIZE						1
#define PADDING							10
#define BUTTONADD_MARGINTOP				20


//*************************************************************
// Constructor - Destructor
//*************************************************************
HangarShipAddView::HangarShipAddView(void)
{
	this->setDisplayTitle(false);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);

	this->mContainerStackView.setContainerStack(&this->mContainerStack);
	this->mButtonAdd.setTitle(Resource::resource->getBundle()->getString("hangarButtonAdd"));

	this->setHeight(PADDING * 2 + this->mContainerStackView.getHeight() + this->mButtonAdd.getHeight() + BUTTONADD_MARGINTOP);
}

HangarShipAddView::~HangarShipAddView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* HangarShipAddView::getCharacter()
{
	return this->mCharacter;
}

void HangarShipAddView::setCharacter( Character* p_character )
{
	this->mCharacter = p_character;
}


//*************************************************************
// Methods
//*************************************************************
void HangarShipAddView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mContainerStackView.update(p_event);
		this->mButtonAdd.update(p_event);
	}
	FieldSet::update(p_event);
}

void HangarShipAddView::update()
{
	if(this->isVisible())
	{
		this->mContainerStackView.update();
	}
}

void HangarShipAddView::updatePosition()
{
	this->mContainerStackView.setPosition(this->getContentX() + (this->getContentWidth() - this->mContainerStackView.getWidth()) / 2, this->getContentY());
	this->mButtonAdd.setPosition(this->getContentX() + (this->getContentWidth() - this->mButtonAdd.getWidth()) / 2, this->mContainerStackView.getBottomY() + BUTTONADD_MARGINTOP);
}

void HangarShipAddView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mContainerStackView.draw();
		this->mButtonAdd.draw();
	}
}

void HangarShipAddView::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->updatePosition();
}

void HangarShipAddView::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}
