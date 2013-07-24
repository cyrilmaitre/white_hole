#pragma once
#include "Ship.h"
#include "Character.h"
#include "Levelable.h"
#include "NpcType.h"

// Define
#define CHARACTERSHIP_JSON_IDCHARACTERSHIP		"idCharacterShip"
#define CHARACTERSHIP_JSON_LEVEL				"level"
#define CHARACTERSHIP_JSON_EXPERIENCE			"experience"
#define CHARACTERSHIP_JSON_PILOTED				"piloted"
#define CHARACTERSHIP_JSON_IDSHIPMODEL			"idShipModel"
#define CHARACTERSHIP_JSON_IDCHARACTER			"idCharacter"
#define CHARACTERSHIP_JSON_WEAPONS				"weapons"
#define CHARACTERSHIP_JSON_ITEMSTACKS			"itemStacks"
#define CHARACTERSHIP_JSON_ITEMSTACK			"itemStack"
#define CHARACTERSHIP_JSON_ITEMSTACKPOSITION	"position"

class CharacterShip : public Ship, public Containerable, public Levelable
{
public:
	// Constructor - Destructor
	CharacterShip(Json::Value json, Character *p_character);
	~CharacterShip(void);

	// Getters - Setters
	void setX(double p_x);
	void setY(double p_y);

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


private:
	// Attrtributs
	bool mPiloted;
	Character *mCharacter;
	NpcType* mNpcType;

	sf::Sprite* mArrowObjectSelected;
};

