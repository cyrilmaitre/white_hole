#include "ContainerStackViewManager.h"
#include "EventManager.h"
#include "ContainerStack.h"
#include "Option.h"


//*************************************************************
// Init static
//*************************************************************
ContainerStackViewManager* ContainerStackViewManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerStackViewManager::ContainerStackViewManager(void)
{
	this->mDraggedView = NULL;
	this->mDraggedViewIcon = NULL;
}

ContainerStackViewManager::~ContainerStackViewManager(void)
{
	this->deleteDraggedViewIcon();
}

void ContainerStackViewManager::deleteDraggedViewIcon()
{
	if(this->mDraggedViewIcon != NULL)
		delete this->mDraggedViewIcon;
	this->mDraggedViewIcon = NULL;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerStackViewManager::init()
{
	ContainerStackViewManager::mInstance = new ContainerStackViewManager();
}

void ContainerStackViewManager::uninit()
{
	delete ContainerStackViewManager::mInstance;
}

ContainerStackViewManager* ContainerStackViewManager::getInstance()
{
	return ContainerStackViewManager::mInstance;
}

ContainerStackView* ContainerStackViewManager::getDraggedView()
{
	return this->mDraggedView;
}

void ContainerStackViewManager::setDraggedView( ContainerStackView* p_view )
{
	if(p_view == NULL || this->mDraggedView == NULL)
	{
		this->mDraggedView = p_view;
		this->notifyDraggedViewChanged();
	}
}

ContainerStackView* ContainerStackViewManager::getDraggedDestinationView()
{
	// Return can be NULL
	std::list<ContainerStackView*>::iterator current;

	for( current = this->mViews.begin(); current != this->mViews.end(); current++ )
	{
		if((*current)->hasMouseOver())
			return *current;
	}

	return NULL;
}

bool ContainerStackViewManager::isViewDragged()
{
	return this->mDraggedView != NULL;
}

bool ContainerStackViewManager::isViewDragged( ContainerStackView* p_view )
{
	return this->mDraggedView != NULL && this->mDraggedView == p_view;
}

void ContainerStackViewManager::notifyDraggedViewChanged()
{
	this->deleteDraggedViewIcon();
	if(this->mDraggedView != NULL)
	{
		this->mDraggedViewIcon = new sf::Sprite(*this->mDraggedView->getIcon());
		this->mDraggedViewIcon->setOrigin(this->mDraggedViewIcon->getLocalBounds().width / 2, this->mDraggedViewIcon->getLocalBounds().height / 2);
	}
}

void ContainerStackViewManager::draw()
{
	if(this->mDraggedViewIcon != NULL)
	{
		sf::Vector2i mousePosition = EventManager::eventManager->getMousePositionUiLocal();
		this->mDraggedViewIcon->setPosition(mousePosition.x, mousePosition.y);
		Resource::resource->getApp()->draw(*this->mDraggedViewIcon);
	}
}

void ContainerStackViewManager::releaseDrag()
{
	ContainerStackView* source = this->getDraggedView();
	ContainerStackView* destination = this->getDraggedDestinationView();
	if(destination != NULL && source != NULL && source != destination)
	{
		if(!destination->getContainerStack()->hasItemStack())
		{
			if(!sf::Keyboard::isKeyPressed(Option::option->getAppControl(OPTION_APP_CONTROL_HALFSTACKMOVE_KEY)))
			{
				destination->getContainerStack()->setItemStack(source->getContainerStack()->getItemStack());
				source->getContainerStack()->setItemStack(NULL);
			}
			else
			{
				if(source->getContainerStack()->getItemStack()->getStackSize() > 1)
				{
					ItemStack* newStack = new ItemStack();
					newStack->setItem(source->getContainerStack()->getItemStack()->getItem());
					newStack->setStackSize(source->getContainerStack()->getItemStack()->getStackSize() / 2);

					source->getContainerStack()->decStackSize(newStack->getStackSize());
					destination->getContainerStack()->setItemStack(newStack);
				}
			}
		}
		else
		{
			if(destination->getContainerStack()->getItemStack()->getItem()->getIdItem() != source->getContainerStack()->getItemStack()->getItem()->getIdItem())
			{
				ItemStack* tmp = destination->getContainerStack()->getItemStack();
				destination->getContainerStack()->setItemStack(source->getContainerStack()->getItemStack());
				source->getContainerStack()->setItemStack(tmp);
			}
			else
			{
				if(destination->getContainerStack()->getItemStack()->getStackSizeFree() >= source->getContainerStack()->getItemStack()->getStackSize())
				{
					destination->getContainerStack()->incStackSize(source->getContainerStack()->getItemStack()->getStackSize());
					source->getContainerStack()->setItemStack(NULL);
				}
				else if(destination->getContainerStack()->getItemStack()->getStackSizeFree() == 0)
				{
					int stackSizeDestination = destination->getContainerStack()->getItemStack()->getStackSize();
					destination->getContainerStack()->setStackSize(source->getContainerStack()->getItemStack()->getStackSize());
					source->getContainerStack()->setStackSize(stackSizeDestination);
				}
				else
				{
					source->getContainerStack()->setStackSize(destination->getContainerStack()->incStackSize(source->getContainerStack()->getItemStack()->getStackSize()));
				}
			}
		}
	}

	this->setDraggedView(NULL);
}

void ContainerStackViewManager::addView( ContainerStackView* p_view )
{
	this->mViews.push_back(p_view);
}

void ContainerStackViewManager::removeView( ContainerStackView* p_view )
{
	this->mViews.remove(p_view);
}



