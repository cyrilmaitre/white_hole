#include "HangarShipWeaponView.h"
#include "ItemStack.h"
#include "Weapon.h"
#include "WeaponModel.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define HEIGHT							100
#define BACKGROUNDCOLOR					sf::Color(25, 26, 28)
#define BORDERCOLOR						sf::Color(194, 194, 194)
#define BORDERSIZE						1
#define PADDING							10
#define WEAPON_FONTSIZE					18
#define WEAPON_MARGINRIGHT				50
#define WEAPONVIEW_MARGIN_LEFT			20


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

	this->mContainerWeaponsStacksChanged = false;
	this->mTBWeapon.setText(Resource::resource->getBundle()->getString("hangarShipWeapon"));
	this->mTBWeapon.setFontSize(WEAPON_FONTSIZE);
}

HangarShipWeaponView::~HangarShipWeaponView(void)
{
	for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
	{
		if(this->mContainerWeaponStackViews[i] != NULL)
			delete this->mContainerWeaponStackViews[i];
	}
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

bool HangarShipWeaponView::isContainerWeaponsStacksChanged()
{
	bool returnValue = this->mContainerWeaponsStacksChanged;
	this->mContainerWeaponsStacksChanged = false;
	return returnValue;
}

void HangarShipWeaponView::setContainerWeaponsStacksChanged( bool p_value )
{
	this->mContainerWeaponsStacksChanged = p_value;
}


//*************************************************************
// Methods
//*************************************************************
void HangarShipWeaponView::update()
{
	if(this->isVisible())
	{
		for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
			this->mContainerWeaponStackViews[i]->update();

		if(this->isContainerWeaponsStacksChanged())
			this->notifyContainerWeaponsStacksChanged();
	}
}

void HangarShipWeaponView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
			this->mContainerWeaponStackViews[i]->update(p_event);
	}
	FieldSet::update(p_event);
}

void HangarShipWeaponView::updatePosition()
{
	this->mTBWeapon.setPosition(this->getContentX(), this->getContentY());
	for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
	{
		if(i == 0)
			this->mContainerWeaponStackViews[i]->setPosition(this->mTBWeapon.getRightX() + WEAPON_MARGINRIGHT, this->getContentY());
		else
			this->mContainerWeaponStackViews[i]->setPosition(this->mContainerWeaponStackViews[i-1]->getRightX() + WEAPONVIEW_MARGIN_LEFT, this->getContentY());
	}
}

void HangarShipWeaponView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTBWeapon.draw();
		for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
			this->mContainerWeaponStackViews[i]->draw();
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
	// Clear
	for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
	{
		if(this->mContainerWeaponStackViews[i] != NULL)
			delete this->mContainerWeaponStackViews[i];
	}
	this->mContainerWeaponStackViews.clear();

	// Add
	for(int i = 0; i < this->mCharacterShip->getWeaponSlotMax(); i++)
	{
		if(i < this->mCharacterShip->getWeaponsCount())
		{
			ContainerStack* currentStack = new ContainerStack(new ItemStack(this->mCharacterShip->getWeapon(i)->getWeaponModel(), 1));
			this->mContainerWeaponStackViews.push_back(new ContainerWeaponStackView(this, currentStack));
		}
		else
		{
			this->mContainerWeaponStackViews.push_back(new ContainerWeaponStackView(this, new ContainerStack()));
		}			
	}

	// Update position
	this->updatePosition();
}

void HangarShipWeaponView::notifyContainerWeaponsStacksChanged()
{
	// Remove all
	this->mCharacterShip->removeWeaponAll(false);

	// Add 
	for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
	{
		WeaponModel* currentWeaponModel = NULL;
		if(this->mContainerWeaponStackViews[i]->getContainerStack()->getItemStack() != NULL)
		{
			Item* currentItem = this->mContainerWeaponStackViews[i]->getContainerStack()->getItemStack()->getItem();
			currentWeaponModel = FactoryGet::getWeaponModelFactory()->getWeaponModel(currentItem->getIdItem());
		}

		if(currentWeaponModel != NULL)
			this->mCharacterShip->addWeapon(new Weapon(this->mCharacterShip, currentWeaponModel), false);
	}
	this->mCharacterShip->notifyWeaponsChanged();
}

