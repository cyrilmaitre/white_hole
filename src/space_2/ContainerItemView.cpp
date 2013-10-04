#include "ContainerItemView.h"
#include "ContainerViewManager.h"
#include "ContainerStackView.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerItemView::ContainerItemView( ContainerItem* p_item )
{
	this->mContainerItem = NULL;
	this->setContainerItem(p_item);
	this->setContainerViewType(ContainerViewType::ItemView);
}

ContainerItemView::~ContainerItemView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ContainerItem* ContainerItemView::getContainerItem()
{
	return this->mContainerItem;
}

void ContainerItemView::setContainerItem( ContainerItem* p_item )
{
	if(this->mContainerItem != p_item)
	{
		this->mContainerItem = p_item;
		this->notifyItemChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void ContainerItemView::update()
{
	ContainerView::update();
	if(this->mContainerItem != NULL)
	{
		if(this->mContainerItem->isItemChanged())
			this->notifyItemChanged();
		this->updateBackgroundColor();
	}
}

void ContainerItemView::updateBackgroundColor()
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
		if(this->mContainerItem->hasItem() && !viewDragged)
		{
			overColor = true;
		}
		else if(viewDragged)
		{
			ContainerView* draggedView = ContainerViewManager::getInstance()->getDraggedView();
			if(draggedView->getContainerViewType() == ContainerViewType::StackView)
			{
				ContainerStackView* plop;
				bool itemTypeDraggedAllowed = this->mContainerItem->isItemTypeAllowed(((ContainerStackView*)draggedView)->getContainerStack()->getItemStack()->getItem()->getItemType());
				if(itemTypeDraggedAllowed)
					overColor = true;
			}
			else if(draggedView->getContainerViewType() == ContainerViewType::ItemView)
			{
				bool itemTypeDraggedAllowed = this->mContainerItem->isItemTypeAllowed(((ContainerItemView*)draggedView)->getContainerItem()->getItem()->getItemType());
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

void ContainerItemView::update( sf::Event p_event )
{

}

void ContainerItemView::updatePosition()
{

}

void ContainerItemView::draw()
{

}

void ContainerItemView::notifyPositionChanged()
{

}

void ContainerItemView::notifyItemChanged()
{

}