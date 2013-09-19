#include "Selectable.h"
#include "SelectableGroup.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
Selectable::Selectable() : Clickable()
{
	this->mSelected = false;
	this->setUpdateSelected(true);
	this->mGroup = NULL;
}


Selectable::~Selectable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool Selectable::isSelected()
{
	return this->mSelected;
}

void Selectable::setSelected( bool p_selected )
{
	if(this->mSelected != p_selected)
	{
		this->mSelected = p_selected;
		this->notifySelectedChanged();
	}
}

bool Selectable::isUpdateSelected()
{
	return this->mUpdateSelected;
}

void Selectable::setUpdateSelected(bool p_canbe)
{
	this->mUpdateSelected = p_canbe;
}

bool Selectable::hasGroup()
{
	return this->mGroup != NULL;
}

SelectableGroup * Selectable::getGroup()
{
	return this->mGroup;
}

void Selectable::setGroup( SelectableGroup* p_group )
{
	this->mGroup = p_group;
}


//*************************************************************
// Methods
//*************************************************************
void Selectable::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		Clickable::update(p_event);
		if(this->isUpdateSelected())
			this->updateSelected();
	}
}

void Selectable::updateSelected()
{
	if(!this->hasGroup())
	{
		if(this->mClicked)
			this->setSelected(!this->isSelected());
	}
	else
	{
		if(this->mClicked && !this->isSelected())
		{
			Selectable* selectedCurrent = this->getGroup()->getSelection();
			if(selectedCurrent != NULL)
				selectedCurrent->setSelected(false);
			this->setSelected(true);
			this->getGroup()->notifySelectionChanged();
		}
	}
}

void Selectable::notifySelectedChanged()
{

}



