#include "SelectableGroup.h"

//******************************
// Constructor - Destructor
//******************************
SelectableGroup::SelectableGroup(bool p_selectedCanBeNull)
{
	this->mSelectionChanged = false;
	this->mSelectionCanBeNull = p_selectedCanBeNull;
	this->mSelection = NULL;
}

SelectableGroup::~SelectableGroup(void)
{
}


//******************************
// Getters - Setters
//******************************
Selectable* SelectableGroup::getSelection()
{
	return this->mSelection;
}

bool SelectableGroup::isSelectionChanged()
{
	bool returnValue = this->mSelectionChanged;
	this->mSelectionChanged = false;
	return returnValue;
}

bool SelectableGroup::isEmpty()
{
	return this->mSelectable.size() == 0;
}

bool SelectableGroup::isSelectionCanBeNull()
{
	return this->mSelectionCanBeNull;
}

void SelectableGroup::setSelectionCanBeNull( bool p_value )
{
	this->mSelectionCanBeNull = p_value;
}


//******************************
// Methods
//******************************
void SelectableGroup::addSelectable( Selectable* p_selectable )
{
	// Check if not already in
	bool selectableExist = false;
	for(int i = 0; i < this->mSelectable.size(); i++)
	{
		if(this->mSelectable[i]->getObjectId() == p_selectable->getObjectId())
		{
			selectableExist = true;
			break;
		}
	}	

	// Add
	if(!selectableExist)
	{
		p_selectable->setSelected(false);
		this->mSelectable.push_back(p_selectable);
		p_selectable->setGroup(this);
		this->notifySelectableChanged();
	}
}

void SelectableGroup::removeSelectable( Selectable* p_selectable )
{
	for(int i = 0; i < this->mSelectable.size(); i++)
	{
		if(this->mSelectable[i]->getObjectId() == p_selectable->getObjectId())
		{
			this->removeSelectable(i);
			break;
		}
	}	
}

void SelectableGroup::removeSelectable( int p_position )
{
	bool notify = this->mSelectable[p_position]->isSelected();
	this->mSelectable.erase(this->mSelectable.begin() + p_position);
	if(notify)
		this->notifySelectionChanged();
	this->notifySelectableChanged();
}

void SelectableGroup::notifySelectionChanged()
{
	this->mSelectionChanged = true;
	this->mSelection = NULL;

	if(this->mSelectable.size() != 0)
	{
		for(int i = 0; i < this->mSelectable.size(); i++)
		{
			if(this->mSelectable[i]->isSelected())
			{
				this->mSelection = this->mSelectable[i];
				break;
			}
		}
	}
}

void SelectableGroup::notifySelectableChanged()
{
	if(this->mSelectable.size() == 0)
		return;

	if(this->getSelection() == NULL)
	{
		// Selecte first
		for(int i = 0; i < this->mSelectable.size(); i++)
		{
			this->mSelectable[i]->setSelected(false);
		}

		if(!this->isSelectionCanBeNull())
			this->mSelectable[0]->setSelected(true);

		this->notifySelectionChanged();
	}
}

void SelectableGroup::unselectAll()
{
	Selectable* selected = this->getSelection();
	
	if(selected != NULL)
		selected->setSelected(false);

	this->notifySelectionChanged();
}


