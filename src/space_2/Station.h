#pragma once
#include "Entity.h"
#include "StationModel.h"
#include "Npc.h"
#include "EntityData.h"
#include "Clock.h"

class ItemStock;

// Define
#define STATION_PLANE				MAPOBJECT_PLANE_1

class Station : public Entity, public Npc
{
public:
	// Constructor - Destructor
	Station(void);
	~Station(void);

	// Getters - Setters
	StationModel* getModel();
	void setModel(StationModel* p_model);

	int getItemStockCount();
	ItemStock* getItemStock(int p_index);
	ItemStock* getItemStock(Item* p_item);

	float getUpdateStocksTick();
	void setUpdateStocksTick(float p_tick);
	bool isUpdateStocksTime();

	// Methods
	void addItemStock(ItemStock* p_stock);
	void removeItemStock(ItemStock* p_stock);

	void dock();
	void undock();

	void update();
	void updateStocks();
	void updateSpinner();
	void updateSprite();
	void draw();
	void loadSprite();
	void unloadSprite();
	void notifyModelChanged();


private:
	// Attributs
	StationModel* mModel;
	sf::Sprite* mSpinnerSprite;
	Rotable mSpinnerRotation;
	mks::Clock mSpinnerClock;

	std::vector<ItemStock*> mStocks;
	float mUpdateStocksTick;
	mks::Clock mUpdateStocksClock;
	sf::Mutex mMutex;
};

