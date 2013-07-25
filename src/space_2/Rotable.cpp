#include "Rotable.h"
#include "Tools.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Rotable::Rotable()
{
	this->mRotation = 0;
	this->mRotationTarget = this->mRotation;
}

Rotable::~Rotable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float Rotable::getRotation()
{
	return this->mRotation;
}

void Rotable::setRotation( float p_rotation )
{
	if(p_rotation > 360)
		p_rotation -= 360;
	else if(p_rotation < 0)
		p_rotation = 360 - Tools::getAbsolute(p_rotation);

	if(this->mRotation != p_rotation)
	{
		this->mRotation = p_rotation;
		this->notifyRotationChanged();
	}
}

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
	if(this->isRotationInfinite())
	{
		float rotationDiff = this->mRotationClock.getElapsedTimeAsSeconds() * this->getRotationVelocity();
		this->mRotationClock.restart();
		if(this->isRotationInfiniteRight())
			this->setRotation(this->getRotation() + rotationDiff);
		else
			this->setRotation(this->getRotation() - rotationDiff);
	}
	else if(this->getRotationTarget() != this->getRotation())
	{
		if(this->isRotationVelocityInstant())
		{
			this->setRotation(this->getRotationTarget());
		}
		else
		{
			float targetDiff = this->getRotationTarget() - this->getRotation();
			bool up = targetDiff < -180 || (targetDiff > 0 && targetDiff < 180);
			float newRotation = 0;

			if(up)
				newRotation = this->getRotation() + this->mRotationClock.getElapsedTimeAsSeconds() * this->getRotationVelocity();
			else
				newRotation = this->getRotation() - this->mRotationClock.getElapsedTimeAsSeconds() * this->getRotationVelocity();

			if(Tools::isBetween(this->getRotationTarget(), this->getRotation(), newRotation))
				newRotation = this->getRotationTarget();
			this->setRotation(newRotation);
			this->mRotationClock.restart();
		}
	}
	else
	{
		this->mRotationClock.restart();
	}
}

void Rotable::notifyRotationChanged()
{

}

