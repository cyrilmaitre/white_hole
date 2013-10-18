#include "HangarShipAddView.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR					sf::Color(25, 26, 28)
#define BORDERCOLOR						sf::Color(194, 194, 194)
#define BORDERSIZE						1
#define PADDING							15
#define BUTTONADD_MARGINTOP				20
#define ITEMTYPE_SHIP_ID				11


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

	this->mContainerStack.addItemTypeAllowed(FactoryGet::getItemTypeFactory()->getItemType(ITEMTYPE_SHIP_ID));
	this->mContainerStackView.setContainerStack(&this->mContainerStack);
	this->mContainerStackView.setDisplayStackSize(false);
	this->mButtonAdd.setTitle(Resource::resource->getBundle()->getString("hangarButtonAdd"));
	this->updateButtonAdd();

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

bool HangarShipAddView::isNewShipAdded()
{
	bool returnValue = this->mNewShipAdded;
	this->mNewShipAdded = false;
	return returnValue;
}

void HangarShipAddView::setNewShipAdded( bool p_value )
{
	this->mNewShipAdded = p_value;
}


//*************************************************************
// Methods
//*************************************************************
void HangarShipAddView::addNewCharacterShip()
{
	if(this->mContainerStackView.getContainerStack()->getItemStack()->getItem() == NULL)
		return;

	this->mCharacter->addShip(this->mContainerStackView.getContainerStack()->getItemStack()->getItem());
	this->mContainerStackView.getContainerStack()->setItemStack(NULL);
	this->notifyNewShipAdded();
}

void HangarShipAddView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mContainerStackView.update(p_event);
		this->mButtonAdd.update(p_event);
		if(this->mButtonAdd.isClicked())
			this->addNewCharacterShip();
	}
	FieldSet::update(p_event);
}

void HangarShipAddView::update()
{
	if(this->isVisible())
	{
		this->mContainerStackView.update();
		this->updateButtonAdd();
	}
}

void HangarShipAddView::updateButtonAdd()
{
	this->mButtonAdd.setEnable(this->mContainerStackView.getContainerStack()->hasItemStack());
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

void HangarShipAddView::notifyNewShipAdded()
{
	this->mNewShipAdded = true;
}


