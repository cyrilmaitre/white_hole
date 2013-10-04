#include "ContainerViewManager.h"
#include "EventManager.h"
#include "ContainerStack.h"
#include "Option.h"


//*************************************************************
// Init static
//*************************************************************
ContainerViewManager* ContainerViewManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerViewManager::ContainerViewManager(void)
{
	this->mDraggedView = NULL;
	this->mDraggedViewIcon = NULL;
}

ContainerViewManager::~ContainerViewManager(void)
{
	this->deleteDraggedViewIcon();
}

void ContainerViewManager::deleteDraggedViewIcon()
{
	if(this->mDraggedViewIcon != NULL)
		delete this->mDraggedViewIcon;
	this->mDraggedViewIcon = NULL;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerViewManager::init()
{
	ContainerViewManager::mInstance = new ContainerViewManager();
}

void ContainerViewManager::uninit()
{
	delete ContainerViewManager::mInstance;
}

ContainerViewManager* ContainerViewManager::getInstance()
{
	return ContainerViewManager::mInstance;
}

ContainerView* ContainerViewManager::getDraggedView()
{
	return this->mDraggedView;
}

void ContainerViewManager::setDraggedView( ContainerView* p_view )
{
	if(p_view == NULL || this->mDraggedView == NULL)
	{
		this->mDraggedView = p_view;
		this->notifyDraggedViewChanged();
	}
}

ContainerView* ContainerViewManager::getDraggedDestinationView()
{
	// Return can be NULL
	std::list<ContainerView*>::iterator current;

	for( current = this->mViews.begin(); current != this->mViews.end(); current++ )
	{
		if((*current)->hasMouseOver())
			return *current;
	}

	return NULL;
}

bool ContainerViewManager::isViewDragged()
{
	return this->mDraggedView != NULL;
}

bool ContainerViewManager::isViewDragged( ContainerView* p_view )
{
	return this->mDraggedView != NULL && this->mDraggedView == p_view;
}

void ContainerViewManager::notifyDraggedViewChanged()
{
	this->deleteDraggedViewIcon();
	if(this->mDraggedView != NULL)
	{
		this->mDraggedViewIcon = new sf::Sprite(*this->mDraggedView->getIcon());
		this->mDraggedViewIcon->setOrigin(this->mDraggedViewIcon->getLocalBounds().width / 2, this->mDraggedViewIcon->getLocalBounds().height / 2);
	}
}

void ContainerViewManager::draw()
{
	if(this->mDraggedViewIcon != NULL)
	{
		sf::Vector2i mousePosition = EventManager::eventManager->getMousePositionUiLocal();
		this->mDraggedViewIcon->setPosition(mousePosition.x, mousePosition.y);
		Resource::resource->getApp()->draw(*this->mDraggedViewIcon);
	}
}

void ContainerViewManager::releaseDrag()
{
	ContainerView* source = this->getDraggedView();
	ContainerView* destination = this->getDraggedDestinationView();

	if(source != NULL && destination != NULL)
	{
		if(source->getContainerViewType() == ContainerView::ContainerViewType::ContainerStackView && destination->getContainerViewType() == ContainerView::ContainerViewType::ContainerStackView)
			this->releaseDrag((ContainerStackView*)source, (ContainerStackView*)destination);
		else if(source->getContainerViewType() == ContainerView::ContainerViewType::ContainerStackView && destination->getContainerViewType() == ContainerView::ContainerViewType::ContainerItemView)
			this->releaseDrag((ContainerStackView*)source, (ContainerItemView*)destination);
		else if(source->getContainerViewType() == ContainerView::ContainerViewType::ContainerItemView && destination->getContainerViewType() == ContainerView::ContainerViewType::ContainerStackView)
			this->releaseDrag((ContainerItemView*)source, (ContainerStackView*)destination);
		else
			this->releaseDrag((ContainerItemView*)source, (ContainerItemView*)destination);
	}
	
	this->setDraggedView(NULL);
}

void ContainerViewManager::releaseDrag( ContainerStackView* p_source, ContainerStackView* p_destination )
{
	if(p_source != p_destination && p_destination->getContainerStack()->isItemTypeAllowed(p_source->getContainerStack()->getItemStack()->getItem()->getItemType()))
	{
		if(!p_destination->getContainerStack()->hasItemStack())
		{
			if(!sf::Keyboard::isKeyPressed(Option::option->getAppControl(OPTION_APP_CONTROL_HALFSTACKMOVE_KEY)))
			{
				p_destination->getContainerStack()->setItemStack(p_source->getContainerStack()->getItemStack());
				p_source->getContainerStack()->setItemStack(NULL);
			}
			else
			{
				if(p_source->getContainerStack()->getItemStack()->getStackSize() > 1)
				{
					ItemStack* newStack = new ItemStack();
					newStack->setItem(p_source->getContainerStack()->getItemStack()->getItem());
					newStack->setStackSize(p_source->getContainerStack()->getItemStack()->getStackSize() / 2);

					p_source->getContainerStack()->decStackSize(newStack->getStackSize());
					p_destination->getContainerStack()->setItemStack(newStack);
				}
			}
		}
		else
		{
			if(p_destination->getContainerStack()->getItemStack()->getItem()->getIdItem() != p_source->getContainerStack()->getItemStack()->getItem()->getIdItem())
			{
				ItemStack* tmp = p_destination->getContainerStack()->getItemStack();
				p_destination->getContainerStack()->setItemStack(p_source->getContainerStack()->getItemStack());
				p_source->getContainerStack()->setItemStack(tmp);
			}
			else
			{
				if(p_destination->getContainerStack()->getItemStack()->getStackSizeFree() >= p_source->getContainerStack()->getItemStack()->getStackSize())
				{
					p_destination->getContainerStack()->incStackSize(p_source->getContainerStack()->getItemStack()->getStackSize());
					p_source->getContainerStack()->setItemStack(NULL);
				}
				else if(p_destination->getContainerStack()->getItemStack()->getStackSizeFree() == 0)
				{
					int stackSizeDestination = p_destination->getContainerStack()->getItemStack()->getStackSize();
					p_destination->getContainerStack()->setStackSize(p_source->getContainerStack()->getItemStack()->getStackSize());
					p_source->getContainerStack()->setStackSize(stackSizeDestination);
				}
				else
				{
					p_source->getContainerStack()->setStackSize(p_destination->getContainerStack()->incStackSize(p_source->getContainerStack()->getItemStack()->getStackSize()));
				}
			}
		}
	}
}

void ContainerViewManager::releaseDrag( ContainerStackView* p_source, ContainerItemView* p_destination )
{

}

void ContainerViewManager::releaseDrag( ContainerItemView* p_source, ContainerStackView* p_destination )
{

}

void ContainerViewManager::releaseDrag( ContainerItemView* p_source, ContainerItemView* p_destination )
{

}

void ContainerViewManager::addView( ContainerView* p_view )
{
	this->mViews.push_back(p_view);
}

void ContainerViewManager::removeView( ContainerView* p_view )
{
	this->mViews.remove(p_view);
}



