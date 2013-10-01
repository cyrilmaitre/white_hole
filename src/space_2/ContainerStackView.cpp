#include "ContainerStackView.h"
#include "ContainerStack.h"
#include "SpriteParameterFactory.h"
#include "ContainerStackViewManager.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define CONTAINERSTACKVIEW_HEIGHT_DRAG					36
#define CONTAINERSTACKVIEW_BACKGROUND_COLOR				sf::Color(65, 65, 65)
#define CONTAINERSTACKVIEW_BACKGROUND_COLOROVER			sf::Color(255, 127, 39)
#define CONTAINERSTACKVIEW_BACKGROUNDICON_COLOR			sf::Color(55, 55, 55)
#define CONTAINERSTACKVIEW_BACKGROUNDICON_WIDTH			32
#define CONTAINERSTACKVIEW_BACKGROUNDICON_HEIGHT		32
#define CONTAINERSTACKVIEW_BACKGROUNDICON_OFFSETX		2
#define CONTAINERSTACKVIEW_BACKGROUNDICON_OFFSETY		2
#define CONTAINERSTACKVIEW_BUTTON_WIDTH					16
#define CONTAINERSTACKVIEW_BUTTON_HEIGHT				10
#define CONTAINERSTACKVIEW_BUTTON_FONTSIZE				8
#define CONTAINERSTACKVIEW_BUTTONINFO_OFFSETX			1
#define CONTAINERSTACKVIEW_BUTTONINFO_OFFSETY			37
#define CONTAINERSTACKVIEW_BUTTONTRASH_OFFSETX			19
#define CONTAINERSTACKVIEW_BUTTONTRASH_OFFSETY			37
#define CONTAINERSTACKVIEW_OVERLAY_COLOR				sf::Color(0, 0, 0, 175)
#define CONTAINERSTACKVIEW_OVERLAY_WIDTH				32
#define CONTAINERSTACKVIEW_OVERLAY_HEIGHT				10
#define CONTAINERSTACKVIEW_OVERLAY_OFFSETX				CONTAINERSTACKVIEW_BACKGROUNDICON_OFFSETX
#define CONTAINERSTACKVIEW_OVERLAY_OFFSETY				CONTAINERSTACKVIEW_BACKGROUNDICON_OFFSETY + CONTAINERSTACKVIEW_BACKGROUNDICON_HEIGHT - CONTAINERSTACKVIEW_OVERLAY_HEIGHT
#define CONTAINERSTACKVIEW_STACKSIZE_OFFSETX			2
#define CONTAINERSTACKVIEW_STACKSIZE_OFFSETY			-2
#define CONTAINERSTACKVIEW_STACKSIZE_FONTSIZE			12
#define CONTAINERSTACKVIEW_STACKSIZE_FONTCOLOR			sf::Color(220, 220, 220)
#define CONTAINERSTACKVIEW_PUB_ITEMSTACK_WIDTH			200


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerStackView::ContainerStackView( ContainerStack* p_stack )
{
	this->setContainerStack(p_stack);

	this->mIcon = NULL;
	this->mPubItemStack = NULL;

	this->setSize(CONTAINERSTACKVIEW_WIDTH, CONTAINERSTACKVIEW_HEIGHT_DRAG);

	this->mBackground.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->mBackground.setFillColor(CONTAINERSTACKVIEW_BACKGROUND_COLOR);

	this->mBackgroundIcon.setSize(sf::Vector2f(CONTAINERSTACKVIEW_BACKGROUNDICON_WIDTH, CONTAINERSTACKVIEW_BACKGROUNDICON_HEIGHT));
	this->mBackgroundIcon.setFillColor(CONTAINERSTACKVIEW_BACKGROUNDICON_COLOR);

	this->mOverlayStackSize.setSize(sf::Vector2f(CONTAINERSTACKVIEW_OVERLAY_WIDTH, CONTAINERSTACKVIEW_OVERLAY_HEIGHT));
	this->mOverlayStackSize.setFillColor(CONTAINERSTACKVIEW_OVERLAY_COLOR);

	this->mStackSize.setFont(*Resource::resource->getFontDefault());
	this->mStackSize.setCharacterSize(CONTAINERSTACKVIEW_STACKSIZE_FONTSIZE);
	this->mStackSize.setColor(CONTAINERSTACKVIEW_STACKSIZE_FONTCOLOR);
	
	this->mPubItemStack = new PopupBubble(this);
	
	this->notifyItemStackChanged();
	ContainerStackViewManager::getInstance()->addView(this);
}

ContainerStackView::~ContainerStackView(void)
{
	this->deleteIcon();

	if(this->mPubItemStack != NULL)
		delete this->mPubItemStack;

	ContainerStackViewManager::getInstance()->removeView(this);
}

void ContainerStackView::deleteIcon()
{
	if(this->mIcon != NULL)
		delete this->mIcon;
	this->mIcon = NULL;
}


//*************************************************************
// Getters - Setters
//*************************************************************
ContainerStack* ContainerStackView::getContainerStack()
{
	return this->mContainerStack;
}

void ContainerStackView::setContainerStack( ContainerStack* p_stack )
{
	this->mContainerStack = p_stack;
}

sf::Sprite* ContainerStackView::getIcon()
{
	return this->mIcon;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerStackView::update()
{
	this->mPubItemStack->update();

	if(	this->hasMouseOver() && (this->getContainerStack()->hasItemStack() || ContainerStackViewManager::getInstance()->isViewDragged()) || 
		ContainerStackViewManager::getInstance()->isViewDragged(this))
	{
		this->mBackground.setFillColor(CONTAINERSTACKVIEW_BACKGROUND_COLOROVER);
	}
	else
	{
		this->mBackground.setFillColor(CONTAINERSTACKVIEW_BACKGROUND_COLOR);
	}

	if(this->getContainerStack()->isItemStackChanged())
		this->notifyItemStackChanged();
}

void ContainerStackView::updatePosition( double newX, double newY )
{
	this->setPosition(newX, newY);
}

void ContainerStackView::update( sf::Event p_event )
{
	Focusable::update(p_event);
	this->mPubItemStack->update(p_event);

	if(this->hasFocus() && this->getContainerStack()->hasItemStack())
		ContainerStackViewManager::getInstance()->setDraggedView(this);
}

void ContainerStackView::notifyPositionChanged()
{
	Focusable::notifyPositionChanged();
	this->mBackground.setPosition(this->getX(), this->getY());
	this->mBackgroundIcon.setPosition(this->getX() + CONTAINERSTACKVIEW_BACKGROUNDICON_OFFSETX, this->getY() + CONTAINERSTACKVIEW_BACKGROUNDICON_OFFSETY);

	if(this->mIcon != NULL)
	{
		this->mIcon->setPosition(this->getX() + CONTAINERSTACKVIEW_BACKGROUNDICON_OFFSETX, this->getY() + CONTAINERSTACKVIEW_BACKGROUNDICON_OFFSETY);
		this->mOverlayStackSize.setPosition(this->getX() + CONTAINERSTACKVIEW_OVERLAY_OFFSETX, this->getY() + CONTAINERSTACKVIEW_OVERLAY_OFFSETY);
		this->mStackSize.setPosition(	this->getX() + CONTAINERSTACKVIEW_OVERLAY_OFFSETX + CONTAINERSTACKVIEW_OVERLAY_WIDTH - this->mStackSize.getLocalBounds().width - CONTAINERSTACKVIEW_STACKSIZE_OFFSETX, 
										this->getY() + CONTAINERSTACKVIEW_OVERLAY_OFFSETY + CONTAINERSTACKVIEW_STACKSIZE_OFFSETY + ((this->mOverlayStackSize.getLocalBounds().height - this->mStackSize.getLocalBounds().height) / 2));
	}
}

void ContainerStackView::notifyItemStackChanged()
{
	this->deleteIcon();

	if(this->getContainerStack() != NULL && this->getContainerStack()->hasItemStack())
	{
		this->setEnable(true);
		this->mIcon = SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getContainerStack()->getItemStack()->getItem()->getSpriteId(), CONTAINERSTACKVIEW_BACKGROUNDICON_WIDTH, CONTAINERSTACKVIEW_BACKGROUNDICON_HEIGHT);
		this->mStackSize.setString(Tools::buildStringWithInt(this->getContainerStack()->getItemStack()->getStackSize()));

		this->mPubItemStack->clear();
		this->mPubItemStack->addLine(	Resource::resource->getBundle()->getString("name") +
										":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getName(), false);
		this->mPubItemStack->addLine(	Resource::resource->getBundle()->getString("type") + 
										":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemType()->getName(), false);
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("tier") + 
										":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemTier()->getName(), false);
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("price") + 
										":" + Tools::getSpaceAfterColon() + Tools::buildStringWithDouble(this->getContainerStack()->getItemStack()->getItem()->getPrice()) +
										" " + Resource::resource->getBundle()->getString("creditAb"), false);
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("itemStackSize") + 
										":" + Tools::getSpaceAfterColon() + Tools::buildStringWithInt(this->getContainerStack()->getItemStack()->getStackSize()), false);
		this->mPubItemStack->addLine(Resource::resource->getBundle()->getString("itemStackPrice") + 
										":" + Tools::getSpaceAfterColon() + Tools::buildStringWithDouble(this->getContainerStack()->getItemStack()->getStackPrice()) + 
										" " + Resource::resource->getBundle()->getString("creditAb"), false);
		this->mPubItemStack->notifyDataSetChanged();
	}
	else
	{
		this->setEnable(false);
	}

	this->notifyPositionChanged();
}

void ContainerStackView::draw()
{
	Resource::resource->getApp()->draw(this->mBackground);
	Resource::resource->getApp()->draw(this->mBackgroundIcon);

	if(this->mIcon != NULL)
	{
		Resource::resource->getApp()->draw(*this->mIcon);	
		Resource::resource->getApp()->draw(this->mOverlayStackSize);
		Resource::resource->getApp()->draw(this->mStackSize);
	}
}

