#include "IdGenerator.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
IdGenerator::IdGenerator( long p_index )
{
	this->reset(p_index);
}

IdGenerator::~IdGenerator(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long IdGenerator::getNextId()
{
	long returnValue = this->mIndex;
	this->mIndex++;
	return returnValue;
}


//*************************************************************
// Methods
//*************************************************************
void IdGenerator::reset( long p_index )
{
	this->mIndex = p_index;
}

void IdGenerator::incIndex( long p_offset )
{
	this->mIndex += p_offset;
}

void IdGenerator::decIndex( long p_offset )
{
	this->mIndex -= p_offset;
}