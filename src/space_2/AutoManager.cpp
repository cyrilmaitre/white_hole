#include "AutoManager.h"


//*************************************************************
// Init static
//*************************************************************
std::vector<Auto*> AutoManager::mAutos;


//*************************************************************
// Constructor - Destructor
//*************************************************************
AutoManager::AutoManager(void)
{
}

AutoManager::~AutoManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int AutoManager::getAutoCount()
{
	return AutoManager::mAutos.size();
}

int AutoManager::getAutoCountMax()
{
	return AUTOMANAGER_MAX;
}


//*************************************************************
// Methods
//*************************************************************
Auto* AutoManager::add( Auto* p_impact )
{
	if(AutoManager::mAutos.size() < AUTOMANAGER_MAX)
		AutoManager::mAutos.push_back(p_impact);
	else
		delete p_impact;
	return p_impact;
}

void AutoManager::remove( int p_position )
{
	delete AutoManager::mAutos[p_position];
	AutoManager::mAutos.erase(AutoManager::mAutos.begin() + p_position);
}

void AutoManager::update()
{
	for(int i = 0; i < AutoManager::mAutos.size(); i++)
	{
		AutoManager::mAutos[i]->update();

		if(AutoManager::mAutos[i]->isFinished())
		{
			AutoManager::mAutos[i]->notifyFinished();
			AutoManager::remove(i);
		}
	}
}

void AutoManager::draw()
{
	for(int i = 0; i < AutoManager::mAutos.size(); i++)
	{
		AutoManager::mAutos[i]->draw();
	}
}

