#pragma once
#include "Selectable.h"

class SelectableGroup
{
public:
	// Constructor - Destructor
	SelectableGroup(bool p_selectedCanBeNull = false);
	~SelectableGroup(void);

	// Getters - Setters
	Selectable* getSelection();
	bool isSelectionChanged();
	bool isEmpty();

	bool isSelectionCanBeNull();
	void setSelectionCanBeNull(bool p_value);

	// Methods
	void addSelectable(Selectable* p_selectable);
	void removeSelectable(Selectable* p_selectable);
	void removeSelectable(int p_position);
	void unselectAll();
	void selectFirst();
	virtual void notifySelectionChanged();
	void notifySelectableChanged();


private:
	// Attributs
	std::vector<Selectable*> mSelectable;
	Selectable* mSelection;
	bool mSelectionChanged;
	bool mSelectionCanBeNull;
};


