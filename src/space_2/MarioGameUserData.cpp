#include "MarioGameUserData.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameUserData::MarioGameUserData( UserDataType p_type )
{
	this->setUserDataType(p_type);
}

MarioGameUserData::~MarioGameUserData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
MarioGameUserData::UserDataType MarioGameUserData::getUserDataType()
{
	return this->mUserDataType;
}

void MarioGameUserData::setUserDataType( UserDataType p_type )
{
	this->mUserDataType = p_type;
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameUserData::BeginContact( b2Contact* p_contact, UserDataIndex p_index )
{

}

void MarioGameUserData::EndContact( b2Contact* p_contact, UserDataIndex p_index )
{

}

void MarioGameUserData::PreSolve( b2Contact* p_contact, const b2Manifold* p_oldManifold, UserDataIndex p_index )
{

}

void MarioGameUserData::PostSolve( b2Contact* p_contact, const b2ContactImpulse* p_impulse, UserDataIndex p_index )
{

}

