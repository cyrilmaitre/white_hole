#include "EntityEffect.h"
#include "Entity.h"


//*************************************************************
// Define
//*************************************************************
#define JSON_OFFSETX				"x"
#define JSON_OFFSETY				"y"
#define JSON_SIZE					"size"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
EntityEffect::EntityEffect( Entity* p_entity, Json::Value p_json )
{
	this->setEntity(p_entity);
	if(p_json != NULL)
	{
		this->setOffsetX(p_json.get(JSON_OFFSETX, 0).asInt());
		this->setOffsetY(p_json.get(JSON_OFFSETY, 0).asInt());
		this->setSize(p_json.get(JSON_SIZE, 0).asInt());
		this->updateOffsetRotate();
	}
}

EntityEffect::~EntityEffect(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Entity* EntityEffect::getEntity()
{
	return this->mEntity;
}

void EntityEffect::setEntity( Entity* p_entity )
{
	this->mEntity = p_entity;
}

float EntityEffect::getOffsetX()
{
	return this->mOffset.x;
}

void EntityEffect::setOffsetX( float p_x )
{
	this->mOffset.x = p_x;
}

float EntityEffect::getOffsetXRotate()
{
	return this->mOffsetRotate.x;
}

void EntityEffect::setOffsetXRotate( float p_x )
{
	this->mOffsetRotate.x = p_x;
}

float EntityEffect::getOffsetY()
{
	return this->mOffset.y;
}

void EntityEffect::setOffsetY( float p_y )
{
	this->mOffset.y = p_y;
}

float EntityEffect::getOffsetYRotate()
{
	return this->mOffsetRotate.y;
}

void EntityEffect::setOffsetYRotate( float p_y )
{
	this->mOffsetRotate.y = p_y;
}

int EntityEffect::getSize()
{
	return this->mSize;
}

void EntityEffect::setSize( int p_size )
{
	this->mSize = p_size;
}


//*************************************************************
// Methods
//*************************************************************
void EntityEffect::update()
{
	this->updateOffsetRotate();
}

void EntityEffect::updateOffsetRotate()
{
	if(this->getEntity() != NULL)
		this->mOffsetRotate = Tools::rotatePoint(this->mOffset, this->getEntity()->getRotation());
}

void EntityEffect::draw()
{

}



