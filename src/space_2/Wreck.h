#pragma once
#include "Entity.h"
#include "NpcShip.h"
#include "Station.h"
#include "Containerable.h"

class WreckMini;

// Define
#define WRECK_OUTOFTIME			3600	// Hour
#define WRECK_SHIELD			0
#define WRECK_ARMOR				0
#define WRECK_STRUCTURE			100
#define WRECK_OPEN_DISTANCE		250
#define WRECK_CARGOMAX			20

class Wreck : public Entity, public Containerable
{
public:
	// Enum
	enum AlphaState
	{
		Stopped,
		Up,
		Down
	};

	// Constructor - Destructor
	Wreck(Entity* p_entity);
	void init();
	~Wreck(void);

	// Getters - Setters
	std::string getName();
	void setName(std::string p_name);

	long getCredit();
	void setCredit(long p_credit);

	bool isOutOfDate();

	// Methods
	void update();
	void update(sf::Event p_event);
	void updateEmber();
	void updateElec();
	void updateSprite();
	void updateWreckMini();
	void updateWreckMini(sf::Event p_event);
	void draw();
	void loadSprite();
	void unloadSprite();
	void loadFromNpc(Npc* p_npc);
	void loadFromEntity(Entity* p_entity);
	void loadFromNpcShip(NpcShip* p_npcShip);
	void loadFromStation(Station* p_station);
	void notifyRotationChanged();


private:
	// Attributs
	std::string mName;
	long mCredit;

	sf::Sprite* mEmberSprite;
	float mEmberAlpha;
	float mEmberAlphaNextTick;
	AlphaState mEmberAlphaState;
	mks::Clock mEmberAlphaClock;
	mks::Clock mEmberAlphaTickClock;

	sf::Sprite* mElecSprite;
	float mElecAlpha;
	float mElecAlphaNextTick;
	AlphaState mElecAlphaState;
	mks::Clock mElecAlphaClock;
	mks::Clock mElecAlphaTickClock;

	std::vector<WreckMini*> mWreckMini;
	mks::Clock mWreckMiniClock;
	bool mWreckMiniTriggered;

	// Methods
	void computeEmberAlphaNextTick();
	void computeElecAlphaNextTick();
};

