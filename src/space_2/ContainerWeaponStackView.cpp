#include "ContainerWeaponStackView.h"
#include "HangarShipWeaponView.h"


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
ContainerWeaponStackView::ContainerWeaponStackView(HangarShipWeaponView* p_view, ContainerStack* p_stack) : ContainerStackView(p_stack)
{
	this->setSize(CONTAINERWIDTH, CONTAINERHEIGHT);
	this->setDisplayStackSize(false);

	this->mBackground.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->mBackgroundIcon.setSize(sf::Vector2f(ICONWIDTH, ICONHEIGHT));

	if(this->getContainerStack() != NULL && this->getContainerStack()->getItemStack() != NULL)
	{
		this->mIcon = SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getContainerStack()->getItemStack()->getItem()->getSpriteId(), ICONWIDTH, ICONHEIGHT);
		this->mStackSize.setString(Tools::buildStringWithInt(this->getContainerStack()->getItemStack()->getStackSize()));

		this->mPubItemStack->clear();
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("name") +
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getName(), false);
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("type") + 
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemType()->getName(), false);
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("tier") + 
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemTier()->getName(), false);
		this->mPubItemStack->notifyDataSetChanged();
	}

	this->mHangarView = p_view;
}

ContainerWeaponStackView::~ContainerWeaponStackView(void)
{
	delete this->mContainerStack;
}

//*************************************************************
// Methods
//*************************************************************
void ContainerWeaponStackView::notifyItemStackChanged()
{
	this->deleteIcon();

	if(this->getContainerStack() != NULL && this->getContainerStack()->hasItemStack())
	{
		this->setEnable(true);
		this->mIcon = SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getContainerStack()->getItemStack()->getItem()->getSpriteId(), ICONWIDTH, ICONHEIGHT);
		this->mStackSize.setString(Tools::buildStringWithInt(this->getContainerStack()->getItemStack()->getStackSize()));

		this->mPubItemStack->clear();
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("name") +
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getName(), false);
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("type") + 
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemType()->getName(), false);
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("tier") + 
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemTier()->getName(), false);
		this->mPubItemStack->notifyDataSetChanged();
	}
	else
	{
		this->setEnable(false);
	}

	if(this->mHangarView != NULL)
		this->mHangarView->setContainerWeaponsStacksChanged(true);
	this->notifyPositionChanged();
}	

