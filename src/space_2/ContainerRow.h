#pragma once
#include "ContainerStack.h"

class Containerable;

// Define
#define CONTAINER_ROW_SIZE		8

class ContainerRow
{
public:
	// Constructor
	ContainerRow( Containerable* p_parent, int p_containerStackCount, int p_position, ContainerStack::ContainerStackType p_type = ContainerStack::ContainerStackType::TypeNone);
	~ContainerRow(void);

	// Getters - Setters
	Containerable* getContainerable();
	ContainerStack* getContainerStack(int p_index);

	int getContainerStacksCount();
	void setContainerStacksCount(int p_count);

	ContainerStack::ContainerStackType getType();
	void setType(ContainerStack::ContainerStackType p_type);

	int getPosition();
	void setPosition(int p_position);


public:
	// Attributs
	Containerable* mContainerable;
	ContainerStack* mContainerStacks[CONTAINER_ROW_SIZE];
	ContainerStack::ContainerStackType mType;
	int mPosition;
	int mContainerStacksCount;
};

