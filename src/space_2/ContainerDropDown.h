#pragma once
#include "DropDownable.h"
#include "Containerable.h"


class ContainerDropDown : public DropDownable
{
public:
	// Constructor - Destructor
	ContainerDropDown(Containerable* p_container);
	~ContainerDropDown(void);

	// Getters - Setters
	Containerable* getContainer();
	void setContainer(Containerable* p_container);

	// Methods
	void notifyContainerChanged();


private:
	// Attributs
	Containerable* mContainer;
};

