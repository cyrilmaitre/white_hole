#pragma once
#include "Block.h"

class List;

class Listable: public Block
{
public:
	// Constructor - Destructor
	Listable();
	virtual ~Listable();

	// Getters - Setters
	List* getList();
	void setList(List *p_list);

	// Methods
	virtual void draw();
	virtual void update(sf::Event myEvent);


private:
	// Attributs
	List *mList;
};
