#pragma once
#include "Selectable.h"

class SelectableGroup
{
public:
	// Constructor - Destructor
	SelectableGroup(void);
	~SelectableGroup(void);

	// Getters - Setters
	Selectable* getSelected();
	bool isSelectedChanged();
	bool isEmpty();

	// Methods
	void init(bool p_selectFirst = true);
	void addSelectable(Selectable* p_selectable);
	void removeSelectable(Selectable* p_selectable);
	void removeSelectable(int p_position);
	void unselectAll();
	void notifySelectedChange();


private:
	// Attributs
	bool mSelectedChanged;
	std::vector<Selectable*> mSelectable;
	Selectable* mSelected;
};

