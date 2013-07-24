#pragma once
#include "Resource.h"

template <typename T> 
class IdValue
{
public:
	// Constructor - Destructor
	IdValue(void);
	~IdValue(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	T getValue();
	void setValue(T p_value);


protected:
	// Methods
	virtual void compute(std::string p_idValue, std::string p_valueDelimeterBegin, std::string p_valueDelimeterEnd) = 0;

private:
	// Attributs
	long mId;
	T mValue;
};

//*************************************************************
// Constructor - Destructor
//*************************************************************
template <typename T>
IdValue<T>::IdValue()
{
}

template <typename T>
IdValue<T>::~IdValue(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
template <typename T>
long IdValue<T>::getId()
{
	return this->mId;
}

template <typename T>
void IdValue<T>::setId( long p_id )
{
	this->mId = p_id;
}

template <typename T>
T IdValue<T>::getValue()
{
	return this->mValue;
}

template <typename T>
void IdValue<T>::setValue( T p_value )
{
	this->mValue = p_value;
}
