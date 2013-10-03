#include "User.h"
#include "Character.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
User::User( Json::Value json )
{
	this->loadFromJson(json);
}

User::~User(void)
{
	this->destroyCharacters();
}

void User::destroyCharacters()
{
	for(int i = 0; i < this->mCharacters.size(); i++)
	{
		if(this->mCharacters[i] != NULL)
			delete this->mCharacters[i];
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
long User::getIdUser()
{
	return this->mIdUser;
}

void User::setIdUser( long p_id )
{
	this->mIdUser = p_id;
}

std::string User::getUsername()
{
	return this->mUsername;
}

void User::setUsername( std::string p_username )
{
	this->mUsername = p_username;
}

std::string User::getEmail()
{
	return this->mEmail;
}

void User::setEmail( std::string p_email )
{
	this->mEmail = p_email;
}

long User::getRegisterDate()
{
	return this->mRegisterDate;
}

void User::setRegisterDate( long p_date )
{
	this->mRegisterDate = p_date;
}

bool User::isAdmin()
{
	return this->mAdmin;
}

void User::setAdmin( bool p_admin )
{
	this->mAdmin = p_admin;
}

int User::getCharactersCount()
{
	return this->mCharacters.size();
}

Character* User::getCharacter( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->mCharacters.size())
		p_index = this->mCharacters.size() - 1;

	return this->mCharacters[p_index];
}


//*************************************************************
// Methods
//*************************************************************
void User::addCharacter( Character* p_character )
{
	this->mCharacters.push_back(p_character);
}

void User::loadFromJson( Json::Value json )
{
	this->setIdUser(json.get(USER_JSON_IDUSER, -1).asInt());
	this->setUsername(json.get(USER_JSON_USERNAME, "").asString());
	this->setEmail(json.get(USER_JSON_EMAIL, "").asString());
	this->setRegisterDate(json.get(USER_JSON_REGISTERDATE, 0).asInt64());
	this->setAdmin(json.get(USER_JSON_ADMIN, false).asBool());

	this->destroyCharacters();
	Json::Value jsonCharacters = json.get(USER_JSON_CHARACTERS, NULL);
	for(int i = 0; i < jsonCharacters.size(); i++)
		this->addCharacter(new Character(this, jsonCharacters.get(i, NULL)));
}



