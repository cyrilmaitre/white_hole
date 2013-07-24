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
	for(int i = 0; i < this->getWeaponSlot(); i++)
		this->removeWeapon(i);
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool Weaponable::isWeaponFull()
{
	return this->getWeaponSlot() == this->getWeaponSlotMax();
}

bool Weaponable::isWeaponEmpty()
{
	return this->getWeaponSlot() == 0;
}

Weapon * Weaponable::getWeapon( int p_index )
{
	return this->mWeapons[p_index];
}

int Weaponable::getWeaponSlot()
{
	return this->mWeapons.size();
}


//*************************************************************
// Methods
//*************************************************************
void Weaponable::addWeapon( Weapon *p_weapon )
{
	if(this->getWeaponSlot() < this->getWeaponSlotMax())
		this->mWeapons.push_back(p_weapon);
}

void Weaponable::removeWeapon( Weapon *p_weapon )
{
	for(int i = 0; i < this->mWeapons.size(); i++)
	{
		if(this->mWeapons[i] == p_weapon)
		{
			delete this->mWeapons[i];
			this->mWeapons.erase(this->mWeapons.begin() + i);
			return;
		}
	}
}

void Weaponable::removeWeapon( int p_index )
{
	delete this->mWeapons[p_index];
	this->mWeapons.erase(this->mWeapons.begin() + p_index);
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


