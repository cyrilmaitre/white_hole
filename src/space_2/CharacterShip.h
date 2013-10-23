#pragma once
#include "Ship.h"
#include "Character.h"
#include "Levelable.h"
#include "NpcType.h"

// Define
#define CHARACTERSHIP_JSON_IDCHARACTERSHIP		"idCharacterShip"
#define CHARACTERSHIP_JSON_ITEMSTACK			"itemStack"
#define CHARACTERSHIP_JSON_ITEMSTACKPOSITION	"position"

class CharacterShip : public Ship, public Containerable, public Levelable
{
public:
	// Constructor - Destructor
	CharacterShip(void);
	CharacterShip(Json::Value json, Character *p_character);
	~CharacterShip(void);

	// Getters - Setters
	long getIdCharacterShip();
	void setIdCharacterShip(long p_id);

	std::string getName();
	void setName(std::string p_name);

	bool hasSkillPoints();
	int getSkillPoints();
	void setSkillPoints(int p_points);

	bool isPiloted();
	void setPiloted(bool p_piloted);

	NpcType* getNpcType();
	void setNpcType(NpcType* p_type);

	Character* getCharacter();
	void setCharacter(Character *p_character);

	// Methods
	void draw();
	void drawArrowObjectSelected();
	void update(sf::Event p_event);
	void update();
	void updatePosition();
	void updateQuickeningActive();
	void updateSprite();
	void updateRotation();
	void loadFromJson(Json::Value json);
	Json::Value saveToJson();
	void loadFromShipModel();

	void incSkillPoints();
	void incSkillPoints(int p_inc);
	void decSkillPoints();
	void incLevel();

	void notifyWeaponsChanged();
	void notifyPositionChanged();
	void notifyShieldChanged(bool p_recover);


private:
	// Attrtributs
	bool mLoaded;
	long mIdCharacterShip;
	std::string mName;
	int mSkillPoints;
	bool mPiloted;
	Character *mCharacter;
	NpcType* mNpcType;

	sf::Sprite* mArrowObjectSelected;
};

