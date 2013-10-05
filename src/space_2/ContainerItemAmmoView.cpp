#include "ContainerItemAmmoView.h"
#include "HangarShipWeaponView.h"


//*************************************************************
// Define
//*************************************************************
#define CONTAINERWIDTH			36
#define CONTAINERHEIGHT			36
#define ICONWIDTH				32
#define ICONHEIGHT				32


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerItemAmmoView::ContainerItemAmmoView( HangarShipWeaponView* p_view, ContainerItem* p_item )
{
	this->setSize(CONTAINERWIDTH, CONTAINERHEIGHT);

	this->mBackground.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->mBackgroundIcon.setSize(sf::Vector2f(ICONWIDTH, ICONHEIGHT));

	if(this->getContainerItem() != NULL && this->getContainerItem()->getItem() != NULL)
	{
		this->updateIcon();
		this->updatePub();
	}

	this->mHangarView = p_view;
	this->notifyItemChanged();
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
	this->mIcon = SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getContainerItem()->getItem()->getSpriteId(), ICONWIDTH, ICONHEIGHT);
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
	this->mPUBInfo->notifyDataSetChanged();
}

void ContainerItemAmmoView::notifyItemChanged()
{
	this->deleteIcon();

	if(this->getContainerItem() != NULL && this->getContainerItem()->hasItem())
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
		this->mHangarView->setContainerAmmosItemsChanged(true);
	this->notifyPositionChanged();
}
