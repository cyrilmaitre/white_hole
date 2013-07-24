#include "NpcMovable.h"


//*************************************************************
// Define
//*************************************************************
#define TICK_TARGET_MIN		20	// Sec
#define TICK_TARGET			20	// Sec 
#define TICK_ROTATION_MIN	2	//Sec
#define TICK_ROTATION		5	//Sec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
NpcMovable::NpcMovable(EntityMovable* p_entity) : Npc(p_entity)
{
	this->mEntityMovable = p_entity;
	this->generateNextTickTarget();
	this->generateNextTickRotation();
}

NpcMovable::~NpcMovable(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
EntityMovable* NpcMovable::getEntityMovable()
{
	return this->mEntityMovable;
}


//*************************************************************
// Methods
//*************************************************************
void NpcMovable::update()
{
	Npc::update();

	if(this->getEntityMovable()->getTarget()->isEntityValid())
	{
		// Dist Max (75% of min weapon range)
		this->getEntityMovable()->setTargetDistanceMax(500);
	}
	else
	{
		// Dist Max
		this->getEntityMovable()->setTargetDistanceMax(TARGET_DISTANCE_MAX_DEFAULT);

		// Define position
		if(!this->getEntityMovable()->isTargetPositionDefined())
		{
			if(this->mClockTickTarget.getElapsedTimeAsSeconds() > this->mNextTickTarget)
			{
				if(this->getEntityBinded()->isEntityValid())
				{
					// Get target position by entity binded
				}
				else
					this->getEntityMovable()->setTargetPosition(this->getEntityMovable()->generateTargetPositionX(), this->getEntityMovable()->generateTargetPositionY());

				this->mClockTickTarget.restart();
				this->generateNextTickTarget();
			}	
			else if(this->mClockTickRotation.getElapsedTimeAsSeconds() > this->mNextTickRotation)
			{
				this->getEntityMovable()->setRotationTarget(Tools::random(0, 360));
				this->mClockTickRotation.restart();
				this->generateNextTickRotation();
			}
		}
	}
}

void NpcMovable::generateNextTickTarget()
{
	this->mNextTickTarget = TICK_TARGET_MIN + Tools::randomZeroToOne() * TICK_TARGET;
}

void NpcMovable::generateNextTickRotation()
{
	this->mNextTickRotation = TICK_ROTATION_MIN + Tools::randomZeroToOne() * TICK_ROTATION;
}

