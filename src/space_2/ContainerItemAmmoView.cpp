#include "ContainerItemAmmoView.h"
#include "HangarShipWeaponView.h"
#include "FactoryGet.h"
#include "AmmoModel.h"
#include "WeaponView.h"


//*************************************************************
// Define
//*************************************************************
#define HANGARVIEW_CONTAINERWIDTH				36
#define HANGARVIEW_CONTAINERHEIGHT				36
#define HANGARVIEW_ICONWIDTH					32
#define HANGARVIEW_ICONHEIGHT					32
#define WEAPONVIEW_CONTAINERWIDTH				20
#define WEAPONVIEW_CONTAINERHEIGHT				20
#define WEAPONVIEW_ICONWIDTH					16
#define WEAPONVIEW_ICONHEIGHT					16


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerItemAmmoView::ContainerItemAmmoView( HangarShipWeaponView* p_view, ContainerItem* p_item ) : ContainerItemView(p_item)
{
	this->setSize(HANGARVIEW_CONTAINERWIDTH, HANGARVIEW_CONTAINERHEIGHT);
	this->mBackgroundIcon.setSize(sf::Vector2f(HANGARVIEW_ICONWIDTH, HANGARVIEW_ICONHEIGHT));

	this->init();
	this->mHangarView = p_view;

	this->notifyItemChanged();
}

ContainerItemAmmoView::ContainerItemAmmoView( WeaponView* p_view, ContainerItem* p_item ) : ContainerItemView(p_item)
{
	this->setSize(WEAPONVIEW_CONTAINERWIDTH, WEAPONVIEW_CONTAINERHEIGHT);
	this->mBackgroundIcon.setSize(sf::Vector2f(WEAPONVIEW_ICONWIDTH, WEAPONVIEW_ICONHEIGHT));

	this->init();
	this->mWeaponView = p_view;

	this->notifyItemChanged();	
}

void ContainerItemAmmoView::init()
{
	this->mHangarView = NULL;
	this->mWeaponView = NULL;

	if(this->getContainerItem() != NULL && this->getContainerItem()->getItem() != NULL)
	{
		this->updateIcon();
		this->updatePub();
	}
	this->mBackground.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
}

ContainerItemAmmoView::~ContainerItemAmmoView(void)
{
	delete this->mContainerItem;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerItemAmmoView::updateIcon()
{
	if(this->mHangarView != NULL)
		this->mIcon = SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getContainerItem()->getItem()->getSpriteId(), HANGARVIEW_ICONWIDTH, HANGARVIEW_ICONHEIGHT);
	else if(this->mWeaponView != NULL)
		this->mIcon = SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getContainerItem()->getItem()->getSpriteId(), WEAPONVIEW_ICONWIDTH, WEAPONVIEW_ICONHEIGHT);
}

void ContainerItemAmmoView::updatePub()
{
	this->mPUBInfo->clear();
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("name") +
		":" + Tools::getSpaceAfterColon() + this->getContainerItem()->getItem()->getName(), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("type") + 
		":" + Tools::getSpaceAfterColon() + this->getContainerItem()->getItem()->getItemType()->getAriane(), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("tier") + 
		":" + Tools::getSpaceAfterColon() + this->getContainerItem()->getItem()->getItemTier()->getName(), false);

	AmmoModel* ammoModel = FactoryGet::getAmmoFactory()->getAmmo(this->getContainerItem()->getItem()->getIdItem());
	this->mPUBInfo->addLine("  ");
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipAmmoInfoDamage") + 
		":" + Tools::getSpaceAfterColon() + Tools::formatNumber(ammoModel->getDamage()), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipAmmoInfoSplash") + 
		":" + Tools::getSpaceAfterColon() + Tools::formatNumber(ammoModel->getSplashRadius()), false);
	this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("hangarShipAmmoInfoAmmoTYpe") + 
		":" + Tools::getSpaceAfterColon() + ammoModel->getAmmoType()->getName(), false);

	this->mPUBInfo->notifyDataSetChanged();
}

void ContainerItemAmmoView::notifyItemChanged()
{
	this->deleteIcon();

	if(this->getContainerItem() != NULL && this->getContainerItem()->hasItem())
	{
		AmmoModel* ammoModel = FactoryGet::getAmmoFactory()->getAmmo(this->getContainerItem()->getItem()->getIdItem());

		this->mBackgroundColor = ammoModel->getAmmoType()->getColor();
		this->setEnable(true);
		this->updateIcon();
		this->updatePub();
	}
	else
	{
		this->mBackgroundColor = CONTAINERVIEW_BACKGROUND_COLOR;
		this->setEnable(false);
	}

	if(this->mHangarView != NULL)
		this->mHangarView->setContainerAmmosItemsChanged(true);
	else if(this->mWeaponView != NULL)
		this->mWeaponView->notifyAmmoContainerChanged();
	this->notifyPositionChanged();
}
