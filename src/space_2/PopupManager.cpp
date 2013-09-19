#include "PopupManager.h"


//*************************************************************
// Init static
//*************************************************************
PopupManager* PopupManager::mInstance = NULL;


//*************************************************************
// Constructor - Destructor
//*************************************************************
PopupManager::PopupManager(void)
{
}

PopupManager::~PopupManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
PopupManager* PopupManager::getInstance()
{
	if(PopupManager::mInstance == NULL)
		PopupManager::mInstance = new PopupManager();
	return PopupManager::mInstance;
}


//*************************************************************
// Methods
//*************************************************************
void PopupManager::addPopup( Block* p_popup )
{
	if(p_popup != NULL)
		this->mPopups.push_back(p_popup);
}

void PopupManager::removePopup( Block* p_popup )
{
	if(p_popup != NULL)
	{
		for(int i = 0; i < this->mPopups.size(); i++)
		{
			if(this->mPopups[i]->getObjectId() == p_popup->getObjectId())
			{
				this->mPopups.erase(this->mPopups.begin() + i);
				break;
			}
		}
	}
}

void PopupManager::draw()
{
	for(int i = 0; i < this->mPopups.size(); i++)
	{
		if(this->mPopups[i] != NULL)
			this->mPopups[i]->draw();
	}
}