#include "SelectableGroup.h"

//******************************
// Constructor - Destructor
//******************************
SelectableGroup::SelectableGroup(void)
{
	this->mSelectedChanged = false;
	this->mSelected = NULL;
}

SelectableGroup::~SelectableGroup(void)
{
}


//******************************
// Getters - Setters
//******************************
Selectable* SelectableGroup::getSelected()
{
	return this->mSelected;
}

bool SelectableGroup::isSelectedChanged()
{
	bool returnValue = this->mSelectedChanged;
	this->mSelectedChanged = false;
	return returnValue;
}

bool SelectableGroup::isEmpty()
{
	return this->mSelectable.size() == 0;
}


//******************************
// Methods
//******************************
void SelectableGroup::init(bool p_selectFirst)
{
	if(this->mSelectable.size() == 0)
		return;

	for(int i = 0; i < this->mSelectable.size(); i++)
	{
		this->mSelectable[i]->setSelected(false);
	}

	if(p_selectFirst)
		this->mSelectable[0]->setSelected(true);

	this->notifySelectedChange();
}

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
		this->notifySelectedChange();
}

void SelectableGroup::notifySelectedChange()
{
	this->mSelectedChanged = true;
	this->mSelected = NULL;

	if(this->mSelectable.size() != 0)
	{
		for(int i = 0; i < this->mSelectable.size(); i++)
		{
			if(this->mSelectable[i]->isSelected())
			{
				this->mSelected = this->mSelectable[i];
				break;
			}
		}
	}
}

void SelectableGroup::unselectAll()
{
	Selectable* selected = this->getSelected();
	
	if(selected != NULL)
		selected->setSelected(false);

	this->notifySelectedChange();
}
