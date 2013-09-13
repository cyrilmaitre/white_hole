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
void ListSelectableGroup::notifyItemAdded( Listable *p_item )
{
	this->addSelectable(p_item);
}

void ListSelectableGroup::notifyItemRemoved( Listable *p_item )
{
	this->removeSelectable(p_item);
}