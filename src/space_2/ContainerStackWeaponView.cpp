#include "ContainerStackWeaponView.h"
#include "HangarShipWeaponView.h"
#include "Weapon.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define CONTAINERWIDTH			68
#define CONTAINERHEIGHT			68
#define ICONWIDTH				64
#define ICONHEIGHT				64


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerStackWeaponView::ContainerStackWeaponView(HangarShipWeaponView* p_view, ContainerStack* p_stack) : ContainerStackView(p_stack)
{
	this->setSize(CONTAINERWIDTH, CONTAINERHEIGHT);
	this->setDisplayStackSize(false);

	this->mBackground.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->mBackgroundIcon.setSize(sf::Vector2f(ICONWIDTH, ICONHEIGHT));

	if(this->getContainerStack() != NULL && this->getContainerStack()->getItemStack() != NULL)
	{
		this->updateIcon();
		this->updatePub();
	}

	this->mHangarView = p_view;
	this->notifyItemStackChanged();
}

ContainerStackWeaponView::~ContainerStackWeaponView(void)
{
	delete this->mContainerStack;
}

//*************************************************************
// Methods
//*************************************************************
void ContainerStackWeaponView::notifyItemStackChanged()
{
	this->deleteIcon();

	if(this->getContainerStack() != NULL && this->getContainerStack()->hasItemStack())
	{
		this->setEnable(true);
		this->updateIcon();
		this->updatePub();
	}
	else
	{
		this->setEnable(false);
	}

	if(this->mHangarView != NULL)
		this->mHangarView->setContainerWeaponsStacksChanged(true);
	this->notifyPositionChanged();
}	

void ContainerStackWeaponView::updateIcon()
{
	this->mIcon = SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getContainerStack()->getItemStack()->getItem()->getSpriteId(), ICONWIDTH, ICONHEIGHT);
}

void ContainerStackWeaponView::updatePub()
{
	this->mPUBInfo->clear();
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("name") +
		":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getName(), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("type") + 
		":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemType()->getAriane(), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("tier") + 
		":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemTier()->getName(), false);

	WeaponModel* weaponModel = FactoryGet::getWeaponModelFactory()->getWeaponModel(this->getContainerStack()->getItemStack()->getItem()->getIdItem());
	this->mPUBInfo->addLine("  ");
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipWeaponInfoDamageMultiplier") + 
		":" + Tools::getSpaceAfterColon() + Tools::formatNumber(weaponModel->getDamageMultiplier()), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipWeaponInfoAmmoMax") + 
		":" + Tools::getSpaceAfterColon() + Tools::formatNumber(weaponModel->getAmmoMax()), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipWeaponInfoRange") + 
		":" + Tools::getSpaceAfterColon() + Tools::formatNumber(weaponModel->getRange()), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipWeaponInfoRangeAngle") + 
		":" + Tools::getSpaceAfterColon() + Tools::formatNumber(weaponModel->getRangeAngle()), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipWeaponInfoRealoadingSpeed") + 
		":" + Tools::getSpaceAfterColon() + Tools::formatNumber(weaponModel->getReloadingSpeed()), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipWeaponInfoFirerate") + 
		":" + Tools::getSpaceAfterColon() + Tools::formatNumber(weaponModel->getFireRate()), false);

	this->mPUBInfo->addLine("  ");
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipWeaponInfoAmmoType"));
	for(int i = 0; i < weaponModel->getAmmoTypeAllowedCount(); i++)
	{
		ItemType* currentType = weaponModel->getAmmoTypeAllowed(i);
		if(currentType->hasParent())
			this->mPUBInfo->addLine("- " + currentType->getParent()->getName() + " " + currentType->getName());
		else
			this->mPUBInfo->addLine("- " + currentType->getName());
	}

	this->mPUBInfo->notifyDataSetChanged();
}



