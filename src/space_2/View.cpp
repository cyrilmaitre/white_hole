#include "View.h"

//******************************
// Constructor - Destructor
//******************************
View::View()
{

}

View::~View()
{
}


//******************************
// Getters - Setters
//******************************
void View::setVisible( bool p_display )
{
	// Update view
	Object::setVisible(p_display);

	// Update view's objects
	std::list<Object*>::iterator current;
	for( current = this->mObjects.begin(); current != this->mObjects.end(); current++ )
	{
		(*current)->setVisible(p_display);
	}
}


//******************************
// Methods
//******************************
void View::addObject( Object* p_object )
{
	this->mObjects.push_back(p_object);
}

void View::removeObject( Object* p_object )
{
	this->mObjects.remove(p_object);
}
