#include "ListSelectableGroup.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ListSelectableGroup::ListSelectableGroup( bool p_selectedCanBeNull ) : SelectableGroup(p_selectedCanBeNull)
{

}

ListSelectableGroup::~ListSelectableGroup(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void ListSelectableGroup::update( sf::Event p_event )
{
	List::update(p_event);
	if(this->hasMouseOver())
	{
		if(p_event.type == sf::Event::KeyPressed)
		{
			if((p_event.key.code == sf::Keyboard::Up))
				this->selectPreviousItem();
			else if((p_event.key.code == sf::Keyboard::Down))
				this->selectNextItem();
		}
	}
}

void ListSelectableGroup::selectNextItem()
{
	Selectable* currentSelection = this->getSelection();
	if(currentSelection != NULL)
	{
		int currentIndex = this->getItemIndex((Listable*)currentSelection);
		if(!this->isLastItem(currentIndex))
		{
			this->getItem(currentIndex + 1)->setSelected(true);
			this->incIndexFirstElement();
		}
	}
}

void ListSelectableGroup::selectPreviousItem()
{
	Selectable* currentSelection = this->getSelection();
	if(currentSelection != NULL)
	{
		int currentIndex = this->getItemIndex((Listable*)currentSelection);
		if(!this->isFirstItem(currentIndex))
		{
			this->getItem(currentIndex - 1)->setSelected(true);
			this->decIndexFirstElement();
		}
	}
}

void ListSelectableGroup::notifyItemAdded( Listable *p_item )
{
	this->addSelectable(p_item);
}

void ListSelectableGroup::notifyItemRemoved( Listable *p_item )
{
	this->removeSelectable(p_item);
}
