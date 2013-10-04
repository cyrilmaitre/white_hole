#include "Weaponable.h"
#include "Weapon.h"
#include "Entity.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Weaponable::Weaponable(void)
{
}

Weaponable::~Weaponable(void)
{
	for(int i = 0; i < this->getWeaponsCount(); i++)
		this->removeWeapon(i);
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool Weaponable::isWeaponFull()
{
	return this->getWeaponsCount() == this->getWeaponSlotMax();
}

bool Weaponable::isWeaponEmpty()
{
	return this->getWeaponsCount() == 0;
}

Weapon * Weaponable::getWeapon( int p_index )
{
	sf::Lock lock(this->mMutex);
	return this->mWeapons[p_index];
}

int Weaponable::getWeaponsCount()
{
	sf::Lock lock(this->mMutex);
	return this->mWeapons.size();
}


//*************************************************************
// Methods
//*************************************************************
void Weaponable::addWeapon( Weapon *p_weapon, bool p_notify )
{
	sf::Lock lock(this->mMutex);
	if(this->getWeaponsCount() < this->getWeaponSlotMax())
	{
		this->mWeapons.push_back(p_weapon);
		if(p_notify)
			this->notifyWeaponsChanged();
	}
}

void Weaponable::removeWeapon( Weapon *p_weapon, bool p_notify )
{
	sf::Lock lock(this->mMutex);
	for(int i = 0; i < this->mWeapons.size(); i++)
	{
		if(this->mWeapons[i] == p_weapon)
		{
			delete this->mWeapons[i];
			this->mWeapons.erase(this->mWeapons.begin() + i);
			if(p_notify)
				this->notifyWeaponsChanged();
			return;
		}
	}
}

void Weaponable::removeWeapon( int p_index, bool p_notify )
{
	sf::Lock lock(this->mMutex);
	delete this->mWeapons[p_index];
	this->mWeapons.erase(this->mWeapons.begin() + p_index);
	if(p_notify)
		this->notifyWeaponsChanged();
}

void Weaponable::removeWeaponAll( bool p_notify )
{
	sf::Lock lock(this->mMutex);
	for(int i = 0; i < this->mWeapons.size(); i++)
	{
		if(this->mWeapons[i] != NULL)
			delete this->mWeapons[i];
	}
	this->mWeapons.clear();
	if(p_notify)
		this->notifyWeaponsChanged();
}

void Weaponable::fire( Entity *p_target, Entity *p_source )
{
	for(int i = 0; i < this->mWeapons.size(); i++)
		this->getWeapon(i)->fire(p_target, p_source);
}

void Weaponable::update()
{
	for(int i = 0; i < this->mWeapons.size(); i++)
		this->getWeapon(i)->update();
}

void Weaponable::reload()
{
	for(int i = 0; i < this->mWeapons.size(); i++)
		this->getWeapon(i)->reload();
}

void Weaponable::notifyWeaponsChanged()
{

}


