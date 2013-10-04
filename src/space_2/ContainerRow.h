#pragma once
#include "Containerable.h"

// Define
#define CONTAINER_ROW_SIZE		8

class ContainerStack;

class ContainerRow
{
public:
	// Constructor
	ContainerRow( Containerable* p_parent, int p_containerStackCount, int p_position, Containerable::ContainerStackType p_type = Containerable::ContainerStackType::TypeNone);
	~ContainerRow(void);

	// Getters - Setters
	Containerable* getContainerable();
	ContainerStack* getContainerStack(int p_index);

	int getContainerStacksCount();
	void setContainerStacksCount(int p_count);

	Containerable::ContainerStackType getType();
	void setType(Containerable::ContainerStackType p_type);

	int getPosition();
	void setPosition(int p_position);


public:
	// Attributs
	Containerable* mContainerable;
	ContainerStack* mContainerStacks[CONTAINER_ROW_SIZE];
	Containerable::ContainerStackType mType;
	int mPosition;
	int mContainerStacksCount;
};

