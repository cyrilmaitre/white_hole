#pragma once
#include "Containerable.h"
#include "Character.h"
#include "WindowChoiceActionObject.h"


class CharacterBank : public Containerable, public WindowChoiceActionObject
{
public:
	// Constructor - Destructor
	CharacterBank(Json::Value json, Character *p_character);
	~CharacterBank(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character* p_character);

	long getIdCharacterBank();
	void setIdCharacterBank(long p_id);

	int getNumber();
	void setNumber(int p_number);

	bool isUnlock();
	void setUnlock(bool p_unlock);

	long getPrice();
	void setPrice(long p_price);

	// Methods
	bool canBeUnlock();
	void unlock();
	void loadFromJson(Json::Value json);
	Json::Value saveToJson();

	static long getPrice(int p_number);


private:
	// Attributs
	Character *mCharacter;
	long mIdCharacterBank;
	int mNumber;
	bool mUnlock;
	long mPrice;
};

