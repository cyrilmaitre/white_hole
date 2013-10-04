#pragma once
#include "ContainerView.h"
#include "ContainerItem.h"


class ContainerItemView : public ContainerView
{
public:
	// Constructor - Destructor
	ContainerItemView(ContainerItem* p_item = NULL);
	~ContainerItemView(void);

	// Getters - Setters
	ContainerItem* getContainerItem();
	void setContainerItem(ContainerItem* p_item);

	// Methods
	void update();
	void updateBackgroundColor();
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	virtual void notifyItemChanged();


private:
	// Attributs
	ContainerItem* mContainerItem;
};

