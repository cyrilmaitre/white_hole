#include "User.h"
#include "Character.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
User::User( Json::Value json )
{
	this->mCharacters = NULL;
	this->mCharactersCount = 0;
	this->loadFromJson(json);
}

User::~User(void)
{
	this->destroyCharacters();
}

void User::destroyCharacters()
{
	if(this->mCharacters != NULL)
	{
		for(int i = 0; i < this->mCharactersCount; i++)
		{
			if(this->mCharacters[i] != NULL)
				delete this->mCharacters[i];
		}
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
	return this->mCharactersCount;
}

void User::setCharactersCount( int p_count )
{
	this->mCharactersCount = p_count;
}

Character** User::getCharacters()
{
	return this->mCharacters;
}

Character* User::getCharacter( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->getCharactersCount())
		p_index = this->getCharactersCount() - 1;

	return this->mCharacters[p_index];
}


//*************************************************************
// Methods
//*************************************************************
void User::loadFromJson( Json::Value json )
{
	this->setIdUser(json.get(USER_JSON_IDUSER, -1).asInt());
	this->setUsername(json.get(USER_JSON_USERNAME, "").asString());
	this->setEmail(json.get(USER_JSON_EMAIL, "").asString());
	this->setRegisterDate(json.get(USER_JSON_REGISTERDATE, 0).asInt64());
	this->setAdmin(json.get(USER_JSON_ADMIN, false).asBool());
	this->setCharactersCount(json.get(USER_JSON_CHARACTERSCOUNT, 0).asInt());

	this->destroyCharacters();
	this->mCharacters = new Character*[this->getCharactersCount()];
	Json::Value jsonCharacters = json.get(USER_JSON_CHARACTERS, NULL);
	for(int i = 0; i < this->getCharactersCount(); i++)
		this->mCharacters[i] = new Character(this, jsonCharacters.get(i, NULL));
}



