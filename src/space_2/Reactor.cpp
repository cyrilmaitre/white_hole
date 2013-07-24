#include "Reactor.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Reactor::Reactor( EntityMovable* p_entity, ReactorType p_type, float p_offsetX, float p_offsetY )
{
	this->mEntityMovable = NULL;
	this->mReactor = NULL;
}

Reactor::~Reactor(void)
{
	if(this->mReactor != NULL)
		delete this->mReactor;
}


//*************************************************************
// Getters - Setters
//*************************************************************
EntityMovable* Reactor::getEntityMovable()
{
	return this->mEntityMovable;
}

void Reactor::setEntityMovable( EntityMovable* p_entity )
{
	this->mEntityMovable = p_entity;
}

Reactor::ReactorType Reactor::getType()
{
	return this->mType;
}

void Reactor::setType( ReactorType p_type )
{
	this->mType = p_type;
}

float Reactor::getOffsetX()
{
	return this->mOffsetX;
}

void Reactor::setOffsetX( float p_x )
{
	this->mOffsetX = p_x;
}

float Reactor::getOffsetY()
{
	return this->mOffsetY;
}

void Reactor::setOffsetY( float p_y )
{
	this->mOffsetY = p_y;
}

