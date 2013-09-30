#pragma once
#include "Resource.h"

class Character;

// Define
#define USER_JSON_IDUSER			"idUser"
#define USER_JSON_USERNAME			"username"
#define USER_JSON_EMAIL				"email"
#define USER_JSON_REGISTERDATE		"registerDate"
#define USER_JSON_ADMIN				"admin"
#define USER_JSON_CHARACTERSCOUNT	"charactersCount"
#define USER_JSON_CHARACTERS		"characters"

class User
{
public:
	// Constructor - Destructor
	User(Json::Value json);
	~User(void);
	void destroyCharacters();

	// Getters - Setters
	long getIdUser();
	void setIdUser(long p_id);

	std::string getUsername();
	void setUsername(std::string p_username);

	std::string getEmail();
	void setEmail(std::string p_email);

	long getRegisterDate();
	void setRegisterDate(long p_date);

	bool isAdmin();
	void setAdmin(bool p_admin);

	int getCharactersCount();
	void setCharactersCount(int p_count);

	Character** getCharacters();
	Character* getCharacter(int p_index);

	// Methods
	void loadFromJson(Json::Value json);


private:
	// Attributs
	long mIdUser;
	std::string mUsername;
	std::string mEmail;
	long mRegisterDate;
	bool mAdmin;
	Character** mCharacters;
	int mCharactersCount;
};

