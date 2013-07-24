#pragma once
#include "Resource.h"
#include "ContainerRow.h"
#include "ContainerStackView.h"
#include "Object.h"

// Define
#define CONTAINERROWVIEW_WIDTH		CONTAINERVIEW_ROW_WIDTH
#define CONTAINERROWVIEW_HEIGHT		CONTAINERVIEW_ROW_HEIGHT

class ContainerRowView : public Object
{
public:
	// Constructor - Destructor
	ContainerRowView(ContainerRow* p_row);
	~ContainerRowView(void);

	// Getters - Setters
	ContainerRow* getContainerRow();
	void setContainerRow(ContainerRow* p_row);

	// Methods
	void addContainerStackView(ContainerStackView* p_view);
	void clear();

	void notifyContainerRowChanged();
	void update();
	void updatePosition(double newX, double newY);
	void update(sf::Event p_event);
	void draw();


private:
	// Attributs
	ContainerRow* mContainerRow;
	std::vector<ContainerStackView*> mContainerStackViews;
};

