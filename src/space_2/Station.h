#pragma once
#include "Entity.h"
#include "StationModel.h"
#include "Npc.h"
#include "EntityData.h"
#include "Clock.h"
#include "Terminable.h"

class ItemStock;

// Define
#define STATION_PLANE		MAPOBJECT_PLANE_1

class Station : public Entity, public Npc, public Terminable
{
public:
	// Constructor - Destructor
	Station(void);
	~Station(void);
	void terminate(bool p_instant);

	// Getters - Setters
	StationModel* getModel();
	void setModel(StationModel* p_model);

	int getItemStockCount();
	ItemStock* getItemStock(int p_index);
	ItemStock* getItemStock(Item* p_item);

	bool isUpdateStocks();
	void setUpdateStocks(bool p_value);

	// Methods
	void addItemStock(ItemStock* p_stock);
	void removeItemStock(ItemStock* p_stock);

	void update();
	void updateStocks();
	void updateSpinner();
	void updateSprite();
	void draw();
	void notifyModelChanged();
	void loadSprite();
	void unloadSprite();


private:
	// Attributs
	StationModel* mModel;
	sf::Sprite* mSpinnerSprite;
	Rotable mSpinnerRotation;
	mks::Clock mSpinnerClock;

	std::vector<ItemStock*> mStocks;
	bool mUpdateStocks;
	sf::Mutex mStocksMutex;
	sf::Thread* mStocksThread;
};

