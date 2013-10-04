#include "ContainerStackView.h"
#include "ContainerStack.h"
#include "SpriteParameterFactory.h"
#include "ContainerViewManager.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define CONTAINERSTACKVIEW_OVERLAY_COLOR				sf::Color(0, 0, 0, 175)
#define CONTAINERSTACKVIEW_OVERLAY_WIDTH				32
#define CONTAINERSTACKVIEW_OVERLAY_HEIGHT				10
#define CONTAINERSTACKVIEW_OVERLAY_OFFSETY				CONTAINERVIEW_BACKGROUNDICON_HEIGHT - CONTAINERSTACKVIEW_OVERLAY_HEIGHT
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
	this->mContainerStack = NULL;
	this->setContainerViewType(ContainerViewType::StackView);
	this->setContainerStack(p_stack);

	this->mOverlayStackSize.setSize(sf::Vector2f(CONTAINERSTACKVIEW_OVERLAY_WIDTH, CONTAINERSTACKVIEW_OVERLAY_HEIGHT));
	this->mOverlayStackSize.setFillColor(CONTAINERSTACKVIEW_OVERLAY_COLOR);

	this->mStackSize.setFont(*Resource::resource->getFontDefault());
	this->mStackSize.setCharacterSize(CONTAINERSTACKVIEW_STACKSIZE_FONTSIZE);
	this->mStackSize.setColor(CONTAINERSTACKVIEW_STACKSIZE_FONTCOLOR);
	this->mDisplayStackSize = true;
}

ContainerStackView::~ContainerStackView(void)
{
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
	if(this->mContainerStack != p_stack)
	{
		this->mContainerStack = p_stack;
		this->notifyItemStackChanged();
	}
}

bool ContainerStackView::isDisplayStackSize()
{
	return this->mDisplayStackSize;
}

void ContainerStackView::setDisplayStackSize( bool p_value )
{
	this->mDisplayStackSize = p_value;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerStackView::update()
{
	ContainerView::update();
	if(this->mContainerStack != NULL)
	{
		if(this->mContainerStack->isItemStackChanged())
			this->notifyItemStackChanged();
		this->updateBackgroundColor();
	}
}

void ContainerStackView::updateBackgroundColor()
{
	bool instanceIsDraggedView = ContainerViewManager::getInstance()->isViewDragged(this);
	bool overColor = false;

	if(instanceIsDraggedView)
	{
		overColor = true;
	}
	else if(this->hasMouseOver())
	{
		bool viewDragged = ContainerViewManager::getInstance()->isViewDragged();
		if(this->getContainerStack()->hasItemStack() && !viewDragged)
		{
			overColor = true;
		}
		else if(viewDragged)
		{
			ContainerView* draggedView = ContainerViewManager::getInstance()->getDraggedView();
			if(draggedView->getContainerViewType() == ContainerViewType::StackView)
			{
				bool itemTypeDraggedAllowed = this->getContainerStack()->isItemTypeAllowed(((ContainerStackView*)draggedView)->getContainerStack()->getItemStack()->getItem()->getItemType());
				if(itemTypeDraggedAllowed)
					overColor = true;
			}
		}
	}

	if(overColor)
		this->mBackground.setFillColor(CONTAINERVIEW_BACKGROUND_COLOROVER);
	else
		this->mBackground.setFillColor(CONTAINERVIEW_BACKGROUND_COLOR);
}

void ContainerStackView::updatePosition(void)
{
	if(this->mIcon != NULL)
	{
		this->mOverlayStackSize.setPosition(this->mIcon->getPosition().x, this->mIcon->getPosition().y + CONTAINERSTACKVIEW_OVERLAY_OFFSETY);
		this->mStackSize.setPosition(	this->mOverlayStackSize.getPosition().x + CONTAINERSTACKVIEW_OVERLAY_WIDTH - this->mStackSize.getLocalBounds().width - CONTAINERSTACKVIEW_STACKSIZE_OFFSETX, 
										this->mOverlayStackSize.getPosition().y + CONTAINERSTACKVIEW_STACKSIZE_OFFSETY + ((this->mOverlayStackSize.getLocalBounds().height - this->mStackSize.getLocalBounds().height) / 2));
	}
}

void ContainerStackView::update( sf::Event p_event )
{
	ContainerView::update(p_event);

	if(this->hasFocus() && this->getContainerStack()->hasItemStack())
		ContainerViewManager::getInstance()->setDraggedView(this);
}

void ContainerStackView::notifyPositionChanged()
{
	ContainerView::notifyPositionChanged();
	this->updatePosition();
}

void ContainerStackView::notifyItemStackChanged()
{
	this->deleteIcon();

	if(this->getContainerStack() != NULL && this->getContainerStack()->hasItemStack())
	{
		this->setEnable(true);
		this->mIcon = SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getContainerStack()->getItemStack()->getItem()->getSpriteId(), CONTAINERVIEW_BACKGROUNDICON_WIDTH, CONTAINERVIEW_BACKGROUNDICON_HEIGHT);
		this->mStackSize.setString(Tools::buildStringWithInt(this->getContainerStack()->getItemStack()->getStackSize()));

		this->mPUBInfo->clear();
		this->mPUBInfo->addLine(	Resource::resource->getBundle()->getString("name") +
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getName(), false);
		this->mPUBInfo->addLine(	Resource::resource->getBundle()->getString("type") + 
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemType()->getAriane(), false);
		this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("tier") + 
			":" + Tools::getSpaceAfterColon() + this->getContainerStack()->getItemStack()->getItem()->getItemTier()->getName(), false);
		this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("price") + 
			":" + Tools::getSpaceAfterColon() + Tools::buildStringWithDouble(this->getContainerStack()->getItemStack()->getItem()->getPrice()) +
			" " + Resource::resource->getBundle()->getString("creditAb"), false);
		this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("itemStackSize") + 
			":" + Tools::getSpaceAfterColon() + Tools::buildStringWithInt(this->getContainerStack()->getItemStack()->getStackSize()), false);
		this->mPUBInfo->addLine(Resource::resource->getBundle()->getString("itemStackPrice") + 
			":" + Tools::getSpaceAfterColon() + Tools::buildStringWithDouble(this->getContainerStack()->getItemStack()->getStackPrice()) + 
			" " + Resource::resource->getBundle()->getString("creditAb"), false);
		this->mPUBInfo->notifyDataSetChanged();
	}
	else
	{
		this->setEnable(false);
	}

	this->notifyPositionChanged();
}

void ContainerStackView::draw()
{
	ContainerView::draw();
	
	if(this->mIcon != NULL && this->isDisplayStackSize())
	{
		Resource::resource->getApp()->draw(this->mOverlayStackSize);
		Resource::resource->getApp()->draw(this->mStackSize);
	}
}

