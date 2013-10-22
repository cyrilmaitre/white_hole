#include "Listable.h"
#include "List.h"
#include "Jukebox.h"


//******************************
// Constructor - Destructor
//******************************
Listable::Listable()
{
	this->mList = NULL;
}

Listable::~Listable(void)
{
}


//******************************
// Getters - Setters
//******************************
List* Listable::getList()
{
	return this->mList;
}

void Listable::setList( List *p_list )
{
	this->mList = p_list;
}


//******************************
// Methods
//******************************
void Listable::draw()
{
	if(this->isVisible())
	{
		Block::draw();
	}
}

void Listable::update(sf::Event myEvent)
{
	if(this->isVisible())
	{
		Block::update(myEvent);
	}
}

