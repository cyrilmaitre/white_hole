#pragma once
#include "MarioGame.h"

class MarioGameUserData
{
public:
	// Enum
	enum UserDataType
	{
		BlockActive = 0,
		Brick,
		Bonus,
		Mario
	};

	enum UserDataIndex
	{
		IndexA = 0,
		IndexB = 1
	};

	// Constructor - Destructor
	MarioGameUserData(UserDataType p_type);
	~MarioGameUserData(void);

	// Getters - Setters
	UserDataType getUserDataType();
	void setUserDataType(UserDataType p_type);

	// Methods
	virtual void BeginContact(b2Contact* p_contact, UserDataIndex p_index);
	virtual void EndContact(b2Contact* p_contact, UserDataIndex p_index);
	virtual void PreSolve(b2Contact* p_contact, const b2Manifold* p_oldManifold, UserDataIndex p_index);
	virtual void PostSolve(b2Contact* p_contact, const b2ContactImpulse* p_impulse, UserDataIndex p_index);


private:
	// Attributs
	UserDataType mUserDataType;
};

