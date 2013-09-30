#include "WreckManager.h"
#include "EntityManager.h"
#include "Game.h"


//*************************************************************
// Init Static
//*************************************************************
std::vector<Wreck*> WreckManager::mWrecks;


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WreckManager::WreckManager(void)
{
}

WreckManager::~WreckManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int WreckManager::getWreckCount()
{
	return WreckManager::mWrecks.size();
}

int WreckManager::getWreckCountMax()
{
	return WRECKMANAGER_COUNT_MAX;
}

bool WreckManager::isFull()
{
	return WreckManager::getWreckCount() >= WreckManager::getWreckCountMax();
}


//*************************************************************
// Methods
//*************************************************************
void WreckManager::add( Wreck* p_wreck )
{
	if(WreckManager::isFull())
		WreckManager::removeFirst();

	EntityManager::add(p_wreck);
	Game::game->getMap()->getMapObjectSelector()->addMapObject(p_wreck);
	WreckManager::mWrecks.push_back(p_wreck);
}

void WreckManager::update()
{
	for(int i = 0; i < WreckManager::mWrecks.size(); i++)
	{
		WreckManager::mWrecks[i]->update();

		if(WreckManager::mWrecks[i]->isDestroy() || WreckManager::mWrecks[i]->isOutOfDate())
			WreckManager::remove(i);
	}
}

void WreckManager::update( sf::Event p_event )
{
	for(int i = 0; i < WreckManager::mWrecks.size(); i++)
	{
		WreckManager::mWrecks[i]->update(p_event);
	}
}

void WreckManager::draw()
{
	for(int i = 0; i < WreckManager::mWrecks.size(); i++)
	{
		WreckManager::mWrecks[i]->draw();
	}
}

void WreckManager::remove( int p_position )
{
	Game::game->getMap()->getMapObjectSelector()->removeMapObject(WreckManager::mWrecks[p_position]);
	EntityManager::remove(WreckManager::mWrecks[p_position]->getIdMapObject());
	WreckManager::mWrecks.erase(WreckManager::mWrecks.begin() + p_position);
}

void WreckManager::removeFirst()
{
	WreckManager::remove(0);
}
