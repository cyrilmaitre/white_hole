#include "HangarShipWeaponView.h"
#include "ItemStack.h"
#include "Weapon.h"
#include "WeaponModel.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define HEIGHT							140
#define BACKGROUNDCOLOR					sf::Color(25, 26, 28)
#define BORDERCOLOR						sf::Color(194, 194, 194)
#define BORDERSIZE						1
#define PADDING							10
#define WEAPON_FONTSIZE					18
#define WEAPON_MARGINRIGHT				50
#define WEAPONVIEW_MARGIN_LEFT			20
#define AMMO_FONTSIZE					18
#define AMMO_MARGINTOP					65
#define ICONTYPEALLOWED_WIDTH			16
#define ICONTYPEALLOWED_HEIGHT			16
#define ICONTYPEALLOWED_BACKCOLOR		sf::Color(255, 255, 255, 0)
#define ICONTYPEALLOWED_BORDERSIZE		0
#define ICONTYPEALLOWED_MARGINLEFT		15


//*************************************************************
// Constructor - Destructor
//*************************************************************
HangarShipWeaponView::HangarShipWeaponView(void) : mPUBTypeAllowed(&this->mIconTypeAllowed)
{
	this->mCharacterShip = NULL;

	this->setHeight(HEIGHT);
	this->setDisplayTitle(false);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);

	this->mContainerWeaponsStacksChanged = false;
	this->mTBWeapon.setText(Resource::resource->getBundle()->getString("hangarShipWeapon"));
	this->mTBWeapon.setFontSize(WEAPON_FONTSIZE);
	this->mTBAmmo.setText(Resource::resource->getBundle()->getString("hangarShipAmmo"));
	this->mTBAmmo.setFontSize(AMMO_FONTSIZE);

	this->mIconTypeAllowed.setSize(ICONTYPEALLOWED_WIDTH, ICONTYPEALLOWED_HEIGHT);
	this->mIconTypeAllowed.setBackgroundColor(ICONTYPEALLOWED_BACKCOLOR, true);
	this->mIconTypeAllowed.setBorderSize(ICONTYPEALLOWED_BORDERSIZE, true);
	this->mIconTypeAllowed.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSpritePtr(IC_16X16_INFO), true);
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

bool HangarShipWeaponView::isContainerAmmosItemsChanged()
{
	bool returnValue = this->mContainerAmmosItemsChanged;
	this->mContainerAmmosItemsChanged = false;
	return returnValue;
}

void HangarShipWeaponView::setContainerAmmosItemsChanged( bool p_value )
{
	this->mContainerAmmosItemsChanged = p_value;
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

		for(int i = 0; i < this->mContainerAmmosItemViews.size(); i++)
			this->mContainerAmmosItemViews[i]->update();

		this->mPUBTypeAllowed.update();

		if(this->isContainerWeaponsStacksChanged())
			this->notifyContainerWeaponsStacksChanged();

		if(this->isContainerAmmosItemsChanged())
			this->notifyContainerAmmosItemChanged();
	}
}

void HangarShipWeaponView::updateCharacterShipWeapons()
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
		{
			Weapon* newWeapon = new Weapon(this->mCharacterShip, currentWeaponModel);
			if(this->mContainerAmmosItemViews[i]->getContainerItem()->hasItem())
				newWeapon->setAmmo(FactoryGet::getAmmoFactory()->getAmmo(this->mContainerAmmosItemViews[i]->getContainerItem()->getItem()->getIdItem()));
			this->mCharacterShip->addWeapon(newWeapon, false);
		}
	}
	this->mCharacterShip->notifyWeaponsChanged();

	// Update ammos item
	this->updateContainerAmmosItems();
}

void HangarShipWeaponView::updateCharacterShipWeaponAmmos()
{
	for(int i = 0; i < this->mCharacterShip->getWeaponsCount(); i++)
	{
		if(this->mContainerWeaponStackViews[i]->getContainerStack()->hasItemStack())
		{
			Weapon* currentWeapon = this->mCharacterShip->getWeapon(i);

			// Correct index ammo view
			int indexAmmoView = 0;
			int indexWeapon = i;
			while(indexWeapon >= 0)
			{
				if(this->mContainerWeaponStackViews[indexAmmoView]->getContainerStack()->hasItemStack())
					indexWeapon--;

				if(indexWeapon >= 0)
					indexAmmoView++;
			}

			// Update ammo
			if(this->mContainerAmmosItemViews[i]->getContainerItem()->hasItem())
				currentWeapon->setAmmo(FactoryGet::getAmmoFactory()->getAmmo(this->mContainerAmmosItemViews[i]->getContainerItem()->getItem()->getIdItem()));
		}
	}	
}

void HangarShipWeaponView::updateContainerAmmosItems()
{
	if(this->mCharacterShip == NULL)
		return;

	// Update content
	for(int i = 0; i < this->mCharacterShip->getWeaponsCount(); i++)
	{
		// Correct index ammo view
		int indexAmmoView = 0;
		int indexWeapon = i;
		while(indexWeapon >= 0)
		{
			if(this->mContainerWeaponStackViews[indexAmmoView]->getContainerStack()->hasItemStack())
				indexWeapon--;

			if(indexWeapon >= 0)
				indexAmmoView++;
		}

		// Restriction
		Weapon* currentWeapon = this->mCharacterShip->getWeapon(i);
		this->mContainerAmmosItemViews[indexAmmoView]->getContainerItem()->clearItemTypeAllowed();
		for(int j = 0; j < currentWeapon->getWeaponModel()->getAmmoTypeAllowedCount(); j++)
			this->mContainerAmmosItemViews[indexAmmoView]->getContainerItem()->addItemTypeAllowed(currentWeapon->getWeaponModel()->getAmmoTypeAllowed(j));

		// Update
		if(currentWeapon->getAmmo() != NULL)
		{
			this->mContainerAmmosItemViews[indexAmmoView]->getContainerItem()->setItem(currentWeapon->getAmmo());
		}
		else if(this->mContainerAmmosItemViews[indexAmmoView]->getContainerItem()->hasItem())
		{
			if(!this->mContainerAmmosItemViews[indexAmmoView]->getContainerItem()->isItemTypeAllowed(this->mContainerAmmosItemViews[indexAmmoView]->getContainerItem()->getItem()->getItemType()))
				this->mContainerAmmosItemViews[indexAmmoView]->getContainerItem()->setItem(NULL);
		}
	}

	// Update NULL
	for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
	{
		if(!this->mContainerWeaponStackViews[i]->getContainerStack()->hasItemStack())
			this->mContainerAmmosItemViews[i]->getContainerItem()->setItem(NULL);
	}
}

void HangarShipWeaponView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		for(int i = 0; i < this->mContainerWeaponStackViews.size(); i++)
			this->mContainerWeaponStackViews[i]->update(p_event);

		for(int i = 0; i < this->mContainerAmmosItemViews.size(); i++)
			this->mContainerAmmosItemViews[i]->update(p_event);

		this->mIconTypeAllowed.update(p_event);
		this->mPUBTypeAllowed.update(p_event);
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
	if(this->mContainerWeaponStackViews.size() > 0)
		this->mIconTypeAllowed.setPosition(this->mContainerWeaponStackViews[this->mContainerWeaponStackViews.size() - 1]->getRightX() + ICONTYPEALLOWED_MARGINLEFT, this->getContentY());

	this->mTBAmmo.setPosition(this->getContentX(), this->mTBWeapon.getBottomY() + AMMO_MARGINTOP);
	for(int i = 0; i < this->mContainerAmmosItemViews.size(); i++)
	{
		this->mContainerAmmosItemViews[i]->setPosition(	this->mContainerWeaponStackViews[i]->getX() + (this->mContainerWeaponStackViews[i]->getWidth() - this->mContainerAmmosItemViews[i]->getWidth()) / 2,
														this->mTBAmmo.getY());
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
		this->mIconTypeAllowed.draw();

		this->mTBAmmo.draw();
		for(int i = 0; i < this->mContainerAmmosItemViews.size(); i++)
			this->mContainerAmmosItemViews[i]->draw();
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

	for(int i = 0; i < this->mContainerAmmosItemViews.size(); i++)
	{
		if(this->mContainerAmmosItemViews[i] != NULL)
			delete this->mContainerAmmosItemViews[i];
	}
	this->mContainerAmmosItemViews.clear();

	// Add
	for(int i = 0; i < this->mCharacterShip->getWeaponSlotMax(); i++)
	{
		// Weapon view
		ContainerStackWeaponView* newView = NULL;
		if(i < this->mCharacterShip->getWeaponsCount())
		{
			ContainerStack* currentStack = new ContainerStack(new ItemStack(this->mCharacterShip->getWeapon(i)->getWeaponModel(), 1));
			newView = new ContainerStackWeaponView(this, currentStack);
		}
		else
		{
			newView = new ContainerStackWeaponView(this, new ContainerStack());
		}	
		
		for(int j = 0; j < this->mCharacterShip->getShipModel()->getWeaponTypeAllowedCount(); j++)
			newView->getContainerStack()->addItemTypeAllowed(this->mCharacterShip->getShipModel()->getWeaponTypeAllowed(j));
		this->mContainerWeaponStackViews.push_back(newView);

		// Ammo view
		this->mContainerAmmosItemViews.push_back(new ContainerItemAmmoView(this, new ContainerItem()));
	}

	// Update pub
	this->mPUBTypeAllowed.clear(false);
	this->mPUBTypeAllowed.addLine(Resource::resource->getBundle()->getString("hangarShipWeaponAllowed"), false);
	for(int i = 0; i < this->mCharacterShip->getShipModel()->getWeaponTypeAllowedCount(); i++)
	{
		ItemType* currentType = this->mCharacterShip->getShipModel()->getWeaponTypeAllowed(i);
		if(currentType->hasParent())
			this->mPUBTypeAllowed.addLine("- " + currentType->getParent()->getName() + " " + currentType->getName());
		else
			this->mPUBTypeAllowed.addLine("- " + currentType->getName());
	}
	this->mPUBTypeAllowed.notifyDataSetChanged();

	// Update
	this->updateContainerAmmosItems();
	this->updatePosition();
}

void HangarShipWeaponView::notifyContainerWeaponsStacksChanged()
{
	this->updateCharacterShipWeapons();
}

void HangarShipWeaponView::notifyContainerAmmosItemChanged()
{
	this->updateCharacterShipWeaponAmmos();
}





