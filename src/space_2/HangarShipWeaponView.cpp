#include "HangarShipWeaponView.h"


//*************************************************************
// Define
//*************************************************************
#define HEIGHT							100
#define BACKGROUNDCOLOR					sf::Color(25, 26, 28)
#define BORDERCOLOR						sf::Color(194, 194, 194)
#define BORDERSIZE						1
#define PADDING							10
#define WEAPON_FONTSIZE					18


//*************************************************************
// Constructor - Destructor
//*************************************************************
HangarShipWeaponView::HangarShipWeaponView(void)
{
	this->setHeight(HEIGHT);
	this->setDisplayTitle(false);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);

	this->mTBWeapon.setText(Resource::resource->getBundle()->getString("hangarShipWeapon"));
	this->mTBWeapon.setFontSize(WEAPON_FONTSIZE);
}

HangarShipWeaponView::~HangarShipWeaponView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
CharacterShip* HangarShipWeaponView::getCharacterShip()
{
	return this->mCharacterShip;
}

void HangarShipWeaponView::setCharacterShip( CharacterShip* p_ship )
{
	if(this->mCharacterShip != p_ship)
	{
		this->mCharacterShip = p_ship;
		this->notifyCharacterShipChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void HangarShipWeaponView::update()
{
	if(this->isVisible())
	{
	}
}

void HangarShipWeaponView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
	}
	FieldSet::update(p_event);
}

void HangarShipWeaponView::updatePosition()
{
	this->mTBWeapon.setPosition(this->getContentX(), this->getContentY());
}

void HangarShipWeaponView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTBWeapon.draw();
	}
}

void HangarShipWeaponView::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->updatePosition();
}

void HangarShipWeaponView::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}

void HangarShipWeaponView::notifyCharacterShipChanged()
{

}
