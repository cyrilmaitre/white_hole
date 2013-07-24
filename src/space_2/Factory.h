#pragma once
#include "Resource.h"


template <typename T> 
class Factory
{
public:
	// Constructor - Destructor
	Factory(void);
	~Factory(void);

	// Getters - Setters
	T* getObject(std::string p_name);

	// Methods
	void uninit();
	void addObject(std::string p_name, T* p_object);


protected:
	// Attributs
	std::map<std::string, T*> mObjects;
};

//*************************************************************
// Constructor - Destructor
//*************************************************************
template <typename T>
Factory<T>::Factory( void )
{

}

template <typename T>
Factory<T>::~Factory( void )
{

}


//*************************************************************
// Getters - Setters
//*************************************************************
template <typename T>
T* Factory<T>::getObject( std::string p_name )
{
	std::map<std::string, T*>::iterator it;
	it = this->mObjects.find(p_name);

	if(it != this->mObjects.end())
		return it->second;

	return NULL;	
}


//*************************************************************
// Methods
//*************************************************************
template <typename T>
void Factory<T>::uninit()
{
	for( std::map<std::string, T*>::iterator it = this->mObjects.begin() ; it != this->mObjects.end(); it++ )
	{
		if((*it).second != NULL)
		{
			delete (*it).second;
			(*it).second = NULL;
		}
	}	
}

template <typename T>
void Factory<T>::addObject( std::string p_name, T* p_object )
{
	if(this->getObject(p_name) == NULL)
		this->mObjects.insert(std::pair<std::string, T*>(p_name, p_object));
}

