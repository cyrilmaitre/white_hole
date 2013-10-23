#include "Destructable.h"
#include "Weapon.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Destructable::Destructable()
{
	this->mClockRegen.restart();

	this->mShield = 0;
	this->mArmor = 0;
	this->mStructure = 1;
	this->mShieldChanged = false;
	this->mArmorChanged = false;
	this->mStructureChanged = false;
}

Destructable::~Destructable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
double Destructable::getShield()
{
	return this->mShield;
}

void Destructable::setShield( double p_shield )
{
	if(p_shield > this->getShieldMax())
		p_shield = this->getShieldMax();
	else if(p_shield < 0)
		p_shield = 0;

	bool recoverShield = false;
	if(this->mShield == 0 && p_shield > 0)
		recoverShield = true;

	this->mShield = p_shield;
	this->notifyShieldChanged(recoverShield);
}

double Destructable::getArmor()
{
	return this->mArmor;
}

void Destructable::setArmor( double p_armor )
{
	if(p_armor > this->getArmorMax())
		p_armor = this->getArmorMax();
	else if(p_armor < 0)
		p_armor = 0;

	this->mArmor = p_armor;
	this->notifyArmorChanged();
}

double Destructable::getStructure()
{
	return this->mStructure;
}

void Destructable::setStructure( double p_structure )
{
	if(p_structure > this->getStructureMax())
		p_structure = this->getStructureMax();
	else if(p_structure < 0)
		p_structure = 0;

	this->mStructure = p_structure;
	this->notifyStructureChanged();
}

bool Destructable::hasShield()
{
	return this->getShield() > 0;
}

bool Destructable::hasArmor()
{
	return this->getArmor() > 0;
}

bool Destructable::hasStructure()
{
	return this->getStructure() > 0;
}

bool Destructable::isAttacked()
{
	return this->mClockAttacked.getElapsedTimeAsSeconds() < DESTRCUTABLE_ATTACKEDCLOCK;
}

void Destructable::setAttacked( bool p_attacked )
{
	if(p_attacked)
		this->mClockAttacked.restart();
}

bool Destructable::isShieldChanged()
{
	bool returnValue = this->mShieldChanged;
	this->mShieldChanged = false;
	return returnValue;
}

bool Destructable::isArmorChanged()
{
	bool returnValue = this->mArmorChanged;
	this->mArmorChanged = false;
	return returnValue;
}

bool Destructable::isStructureChanged()
{
	bool returnValue = this->mStructureChanged;
	this->mStructureChanged = false;
	return returnValue;
}


//*************************************************************
// Methode
//*************************************************************
void Destructable::update()
{
	if(!this->isAttacked())
	{
		float elapsedTime = this->mClockRegen.getElapsedTimeAsSeconds();
		if(this->mClockRegen.getElapsedTimeAsSeconds() > DESTRUCTABLE_UPDATE_PERIOD)
		{
			if(this->getShield() < this->getShieldMax())
				this->incShield(this->getShieldRegen() * elapsedTime);

			if(this->getArmor() < this->getArmorMax())
				this->incArmor(this->getArmorRegen() * elapsedTime);

			if(this->getStructure() < this->getStructureMax())
				this->incStructure(this->getStructureRegen() * elapsedTime);

			this->mClockRegen.restart();
		}
	}
	else
	{
		this->mClockRegen.restart();
	}
}

void Destructable::incShield( double p_value )
{
	this->setShield(this->mShield + p_value);
}

void Destructable::decShield( double p_value )
{
	this->setShield(this->mShield - p_value);
}

void Destructable::incArmor( double p_value )
{
	this->setArmor(this->mArmor + p_value);
}

void Destructable::decArmor( double p_value )
{
	this->setArmor(this->mArmor - p_value);
}

void Destructable::incStructure( double p_value )
{
	this->setStructure(this->mStructure + p_value);
}

void Destructable::decStructure( double p_value )
{
	this->setStructure(this->mStructure - p_value);
}

bool Destructable::takeDamage( Weapon* p_weapon )
{
	double baseDamage = p_weapon->getBaseDamage();
	if(baseDamage <= 0)
		return false;

	if(this->getShield() > 0)
	{
		float shieldDamageMultiplier = p_weapon->getAmmo()->getAmmoType()->getDamageShieldMultiplier();
		double shieldDamage = baseDamage * shieldDamageMultiplier;

		if(shieldDamage > this->getShield())
		{
			baseDamage -= this->getShield() / shieldDamageMultiplier;
			this->setShield(0);
		}
		else
		{
			this->decShield(shieldDamage);
			return false;
		}
	}

	if(this->getArmor() > 0)
	{
		float armorDamageMultiplier = p_weapon->getAmmo()->getAmmoType()->getDamageArmorMultiplier();
		double armorDamage = baseDamage * armorDamageMultiplier;

		if(armorDamage > this->getArmor())
		{
			baseDamage -= this->getArmor() / armorDamageMultiplier;
			this->setArmor(0);
		}
		else
		{
			this->decArmor(armorDamage);
			return false;
		}
	}
	
	if(this->getStructure() > 0)
	{
		float structureDamageMultiplier = p_weapon->getAmmo()->getAmmoType()->getDamageStructureMultiplier();
		double structureDamage = baseDamage * structureDamageMultiplier;

		if(structureDamage > this->getStructure())
		{
			baseDamage -= this->getStructure() / structureDamageMultiplier;
			this->setStructure(0);
			return true;
		}
		else
		{
			this->decStructure(structureDamage);
			return false;
		}
	}
}

void Destructable::heal( double p_heal )
{
	if(p_heal <= 0)
		return;

	double offsetStructure = this->getStructureMax() - this->getStructure();
	if(p_heal > offsetStructure)
	{
		p_heal -= offsetStructure;
		this->setStructure(this->getStructureMax());
	}
	else
	{
		this->incStructure(p_heal);
		return;
	}

	double offsetArmor = this->getArmorMax() - this->getArmor();
	if(p_heal > offsetArmor)
	{
		p_heal -= offsetArmor;
		this->setArmor(this->getArmorMax());
	}
	else
	{
		this->incArmor(p_heal);
		return;
	}

	double offsetShield = this->getShieldMax() - this->getShield();
	if(p_heal > offsetShield)
	{
		p_heal -= offsetShield;
		this->setShield(this->getShieldMax());
	}
	else
	{
		this->incShield(p_heal);
		return;
	}
}

void Destructable::notifyShieldChanged(bool p_recover)
{
	this->mShieldChanged = true;
}

void Destructable::notifyArmorChanged()
{
	this->mArmorChanged = true;
}

void Destructable::notifyStructureChanged()
{
	this->mStructureChanged = true;
}

void Destructable::notifyShieldMaxChanged()
{
	DestructableData::notifyShieldMaxChanged();
	this->setShield(this->getShieldMax());
}

void Destructable::notifyArmorMaxChanged()
{
	DestructableData::notifyArmorMaxChanged();
	this->setArmor(this->getArmorMax());
}

void Destructable::notifyStructureMaxChanged()
{
	DestructableData::notifyStructureMaxChanged();
	this->setStructure(this->getStructureMax());
}


