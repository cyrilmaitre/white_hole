#include "Session.h"


//*************************************************************
// Init static
//*************************************************************
User* Session::mUser;
Character * Session::mSelectedCharacter;
Json::Value* Session::mUserJson;
bool Session::mAuthenticated;


//*************************************************************
// Constructor - Destructor
//*************************************************************
Session::Session(void)
{
}

Session::~Session(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
User* Session::getUser()
{
	return Session::mUser;
}

void Session::setUser( User* p_user )
{
	if(Session::mUser != NULL)
		delete Session::mUser;

	Session::mUser = p_user;
}

Json::Value* Session::getUserJson()
{
	return Session::mUserJson;
}

void Session::setUserJson( Json::Value* p_json )
{
	if(Session::mUserJson != NULL)
		delete Session::mUserJson;

	Session::mUserJson = p_json;
}

Character* Session::getSelectedCharacter()
{
	return Session::mSelectedCharacter;
}

void Session::setSelectedCharacter( Character* p_character )
{
	Session::mSelectedCharacter = p_character;
}

bool Session::isAuthenticated()
{
	return Session::mAuthenticated;
}

void Session::setAuthenticated( bool p_authenticated )
{
	Session::mAuthenticated = p_authenticated;
}


//*************************************************************
// Methods
//*************************************************************
void Session::init()
{
	Session::mUser = NULL;
	Session::mUserJson = NULL;
	Session::mSelectedCharacter = NULL;
	Session::mAuthenticated = false;
}

void Session::uninit()
{
	if(Session::mUser != NULL)
		delete Session::mUser;

	if(Session::mUserJson != NULL)
		delete Session::mUserJson;
}


