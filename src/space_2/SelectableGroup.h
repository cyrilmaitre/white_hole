#pragma once
#include "Selectable.h"

class SelectableGroup
{
public:
	// Constructor - Destructor
	SelectableGroup(bool p_selectedCanBeNull = false);
	~SelectableGroup(void);

	// Getters - Setters
	Selectable* getSelected();
	bool isSelectedChanged();
	bool isEmpty();

	bool isSelectedCanBeNull();
	void setSelectedCanBeNull(bool p_value);

	// Methods
	void addSelectable(Selectable* p_selectable);
	void removeSelectable(Selectable* p_selectable);
	void removeSelectable(int p_position);
	void unselectAll();
	void notifySelectedChange();
	void notifySelectableChanged();


private:
	// Attributs
	std::vector<Selectable*> mSelectable;
	Selectable* mSelected;
	bool mSelectedChanged;
	bool mSelectedCanBeNull;
};


