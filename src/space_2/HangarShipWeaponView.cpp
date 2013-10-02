#include "HangarShipWeaponView.h"
#include "ItemStack.h"
#include "Weapon.h"
#include "WeaponModel.h"


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

	this->mWeaponsChanged = false;
	this->mIgnoreWeaponsChanged = false;
	this->mTBWeapon.setText(Resource::resource->getBundle()->getString("hangarShipWeapon"));
	this->mTBWeapon.setFontSize(WEAPON_FONTSIZE);
}

HangarShipWeaponView::~HangarShipWeaponView(void)
{
	for(int i = 0; i < this->mWeaponsView.size(); i++)
	{
		if(this->mWeaponsView[i] != NULL)
			delete this->mWeaponsView[i];
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

bool HangarShipWeaponView::isWeaponsChanged()
{
	bool returnValue = this->mWeaponsChanged;
	this->mWeaponsChanged = false;
	return returnValue;
}

void HangarShipWeaponView::setWeaponsChanged( bool p_value )
{
	this->mWeaponsChanged = p_value;
}


//*************************************************************
// Methods
//*************************************************************
void HangarShipWeaponView::update()
{
	if(this->isVisible())
	{
		for(int i = 0; i < this->mWeaponsView.size(); i++)
			this->mWeaponsView[i]->update();

		if(this->isWeaponsChanged())
			this->notifyWeaponsChanged();
	}
}

void HangarShipWeaponView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		for(int i = 0; i < this->mWeaponsView.size(); i++)
			this->mWeaponsView[i]->update(p_event);
	}
	FieldSet::update(p_event);
}

void HangarShipWeaponView::updatePosition()
{
	this->mTBWeapon.setPosition(this->getContentX(), this->getContentY());
	for(int i = 0; i < this->mWeaponsView.size(); i++)
	{
		if(i == 0)
			this->mWeaponsView[i]->setPosition(this->mTBWeapon.getRightX() + WEAPON_MARGINRIGHT, this->getContentY());
		else
			this->mWeaponsView[i]->setPosition(this->mWeaponsView[i-1]->getRightX() + WEAPONVIEW_MARGIN_LEFT, this->getContentY());
	}
}

void HangarShipWeaponView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTBWeapon.draw();
		for(int i = 0; i < this->mWeaponsView.size(); i++)
			this->mWeaponsView[i]->draw();
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
	for(int i = 0; i < this->mWeaponsView.size(); i++)
	{
		if(this->mWeaponsView[i] != NULL)
			delete this->mWeaponsView[i];
	}
	this->mWeaponsView.clear();

	// Add
	for(int i = 0; i < this->mCharacterShip->getWeaponSlotMax(); i++)
	{
		if(i < this->mCharacterShip->getWeaponsCount())
		{
			ContainerStack* currentStack = new ContainerStack(new ItemStack(this->mCharacterShip->getWeapon(i)->getWeaponModel(), 1));
			this->mWeaponsView.push_back(new ContainerWeaponStackView(this, currentStack));
		}
		else
		{
			this->mWeaponsView.push_back(new ContainerWeaponStackView(this, new ContainerStack()));
		}			
	}

	// Update position
	this->updatePosition();
}

void HangarShipWeaponView::notifyWeaponsChanged()
{
	if(!this->mIgnoreWeaponsChanged)
	{
		this->mIgnoreWeaponsChanged = true;


		this->mIgnoreWeaponsChanged = false;
	}
}

