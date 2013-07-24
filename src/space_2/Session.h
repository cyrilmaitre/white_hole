#pragma once
#include "User.h"
#include "Character.h"


class Session
{
public:
	// Methods
	static void init();
	static void uninit();

	static User* getUser();
	static void setUser(User* p_user);

	static Json::Value* getUserJson();
	static void setUserJson(Json::Value* p_json);

	static Character* getSelectedCharacter();
	static void setSelectedCharacter(Character* p_character);

	static bool isAuthenticated();
	static void setAuthenticated(bool p_authenticated);

	
private:
	// Constructor - Destructor
	Session(void);
	~Session(void);

	// Attributs
	static User* mUser;
	static Json::Value* mUserJson;
	static bool mAuthenticated;

	static Character *mSelectedCharacter;
};

