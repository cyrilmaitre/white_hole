#pragma once
#include "Clickable.h"

class SelectableGroup;

class Selectable: public Clickable
{
public:
	// Constructor - Destructor
	Selectable();
	~Selectable();

	// Getters - Setters
	bool isSelected();
	void setSelected(bool p_selected);

	bool isUpdateSelected();
	void setUpdateSelected(bool p_canbe);

	bool hasGroup();
	SelectableGroup *getGroup();
	void setGroup(SelectableGroup* p_group);

	// Methods
	virtual void notifySelectedChanged();


protected:
	// Attributs
	bool mSelected;
	bool mUpdateSelected;
	SelectableGroup *mGroup;

	// Methods
	void update(sf::Event p_event);


private:
	// Methods
	virtual void updateSelected();
};
