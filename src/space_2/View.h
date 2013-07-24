#pragma once
#include "Object.h"

class View: public Object
{
public:
	// Constructor - Destructor
	View();
	~View();

	// Getters - Setters
	void setVisible(bool p_display);

	// Methods
	void addObject(Object* p_object);
	void removeObject(Object* p_object);


private:
	// Attributs
	std::list<Object*> mObjects;
};

