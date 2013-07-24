#include "Rotable.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Rotable::Rotable( MapObject* p_object )
{
	this->mMapObject = p_object;
	this->mRotationTarget = this->mMapObject->getRotation();
}

Rotable::~Rotable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float Rotable::getRotationTarget()
{
	return this->mRotationTarget;
}

void Rotable::setRotationTarget( float p_rotation )
{
	this->mRotationTarget = p_rotation;
}


//*************************************************************
// Methods
//*************************************************************
void Rotable::update()
{
	this->updateRotation();
}

void Rotable::updateRotation()
{
	if(this->mMapObject != NULL)
	{
		if(this->getRotationTarget() != this->mMapObject->getRotation())
		{
			if(this->isRotationVelocityInstant())
			{
				this->mMapObject->setRotation(this->getRotationTarget());
			}
			else
			{
				float targetDiff = this->getRotationTarget() - this->mMapObject->getRotation();
				bool up = targetDiff < -180 || (targetDiff > 0 && targetDiff < 180);
				float newRotation = 0;

				if(up)
					newRotation = this->mMapObject->getRotation() + this->mRotationClock.getElapsedTimeAsSeconds() * this->getRotationVelocity();
				else
					newRotation = this->mMapObject->getRotation() - this->mRotationClock.getElapsedTimeAsSeconds() * this->getRotationVelocity();

				if(Tools::isBetween(this->getRotationTarget(), this->mMapObject->getRotation(), newRotation))
					newRotation = this->getRotationTarget();
				this->mMapObject->setRotation(newRotation);
				this->mRotationClock.restart();
			}
		}
	}
}
