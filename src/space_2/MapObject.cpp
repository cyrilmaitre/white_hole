#include "MapObject.h"
#include "Camera.h"
#include "ToolsImage.h"
#include "Game.h"


//*************************************************************
// Static
//*************************************************************
float MapObject::mPlaneRatio[];
IdGenerator MapObject::mIdGenerator;


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
MapObject::MapObject( int p_plane )
{
	this->mObjectSprite = NULL;
	this->mObjectSpriteParameter = NULL;
	this->setIdMapObject(MapObject::mIdGenerator.getNextId());
	this->setPlane(p_plane);
	this->setRotation(0.f);
	this->setScale(1.f);
	this->setObjectType(MapObjectType::TypeMapObject);
	this->setObjectOpacity(MapObjectOpacity::Opacity10);
	this->setSector(NULL);
	this->setVisible(false);
}

MapObject::~MapObject(void)
{
	this->unloadSprite();
}


//*************************************************************
// Getters - Setters
//*************************************************************
long MapObject::getIdMapObject()
{
	return this->mIdMapObject;
}

void MapObject::setIdMapObject( long p_id )
{
	this->mIdMapObject = p_id;
}

double MapObject::getX( int plane )
{
	return (this->Object::getX() / MapObject::getPlaneRatio(this->mPlane)) * MapObject::getPlaneRatio(plane);
}

double MapObject::getSectorX()
{
	double positionXSector = this->getX(SECTOR_PLANE);
	if(this->hasSector())	
		return positionXSector - this->getSector()->getX();

	return positionXSector;
}

float MapObject::getScreenX()
{
	return this->mScreenPosition.x;
}

double MapObject::getCenterX( int plane )
{
	return (this->Object::getCenterX() / MapObject::getPlaneRatio(this->mPlane)) * MapObject::getPlaneRatio(plane);
}

double MapObject::getY( int plane )
{
	return (this->Object::getY() / MapObject::getPlaneRatio(this->mPlane)) * MapObject::getPlaneRatio(plane);
}

double MapObject::getSectorY()
{
	double positionYSector = this->getY(SECTOR_PLANE);
	if(this->hasSector())
		return positionYSector - this->getSector()->getY();

	return positionYSector;
}

float MapObject::getScreenY()
{
	return this->mScreenPosition.y;
}

double MapObject::getCenterY( int plane )
{
	return (this->Object::getCenterY() / MapObject::getPlaneRatio(this->mPlane)) * MapObject::getPlaneRatio(plane);
}

sf::Vector2f MapObject::getScreenPosition()
{
	return this->mScreenPosition;
}

sf::Vector2f MapObject::getPosition( int plane )
{
	sf::Vector2f position;
	position.x = this->getX(plane);
	position.y = this->getY(plane);
	return position;
}

sf::Vector2f MapObject::getCenterPosition( int plane )
{
	sf::Vector2f position;
	position.x = this->getCenterX(plane);
	position.y = this->getCenterY(plane);
	return position;
}

sf::FloatRect MapObject::getHitBox()
{
	return this->mHitBox;
}

int MapObject::getWidth( int p_plane )
{
	return MapObject::convertSize(this->Object::getWidth(), this->getPlane(), p_plane);
}

int MapObject::getHeight( int p_plane )
{
	return MapObject::convertSize(this->Object::getHeight(), this->getPlane(), p_plane);
}

void MapObject::setWidth( int p_witdh )
{
	this->Object::setWidth(p_witdh * this->getScale());
}

void MapObject::setHeight( int p_height )
{
	this->Object::setHeight(p_height * this->getScale());
}

int MapObject::getRadius()
{
	return this->mHitBox.width > this->mHitBox.height ? this->mHitBox.width / 2 : this->mHitBox.height / 2;
}

void MapObject::setSize( int p_witdh, int p_height )
{
	this->Object::setSize(p_witdh * this->getScale(), p_height * this->getScale());
}

int MapObject::getPlane()
{
	return this->mPlane;
}

void MapObject::setPlane( int p_plane )
{
	this->mPlane = p_plane;
}

MapObject::MapObjectType MapObject::getObjectType()
{
	return this->mObjectType;
}

std::string MapObject::getObjectTypeName()
{
	switch(this->getObjectType())
	{
	case MapObjectType::TypeMapObject:
		return Resource::resource->getBundle()->getString("mapObjectTypeDefault");
		break;

	case MapObjectType::TypeShip:
	case MapObjectType::TypeCharacterShip:
	case MapObjectType::TypeNpcShip:
		return Resource::resource->getBundle()->getString("mapObjectTypeShip");
		break;

	case MapObjectType::TypePlanet:
		return Resource::resource->getBundle()->getString("mapObjectTypePlanet");
		break;

	case MapObjectType::TypeCloudGaz:
		return Resource::resource->getBundle()->getString("mapObjectTypeCloudGaz");
		break;

	case MapObjectType::TypeCloudWreck:
		return Resource::resource->getBundle()->getString("mapObjectTypeCloudWreck");
		break;

	case MapObjectType::TypeWreck:
		return Resource::resource->getBundle()->getString("mapObjectTypeWreck");
		break;

	case MapObjectType::TypeWreckMini:
		return Resource::resource->getBundle()->getString("mapObjectTypeWreckMini");
		break;

	case MapObjectType::TypeStar:
		return Resource::resource->getBundle()->getString("mapObjectTypeStart");
		break;

	case MapObjectType::TypeStation:
		return Resource::resource->getBundle()->getString("mapObjectTypeStation");
		break;

	default:
		return Resource::resource->getBundle()->getString("mapObjectTypeDefault");
		break;
	}
}

void MapObject::setObjectType( MapObject::MapObjectType p_type )
{
	this->mObjectType = p_type;
}

MapObject::MapObjectOpacity MapObject::getObjectOpacity()
{
	return this->mObjectOpacity;
}

void MapObject::setObjectOpacity( MapObjectOpacity p_opacity )
{
	this->mObjectOpacity = p_opacity;
}

bool MapObject::hasSector()
{
	return this->mSector != NULL;
}

Sector* MapObject::getSector()
{
	return this->mSector;
}

void MapObject::setSector( Sector* p_sector )
{
	this->mSector = p_sector;
}

float MapObject::getScale()
{
	return this->mScale;
}

void MapObject::setScale( float p_scale )
{
	if(this->mScale != p_scale)
	{
		this->mScale = p_scale;
		this->notifyScaleChanged();
	}
}

bool MapObject::isSpriteLoaded()
{
	return this->mObjectSprite != NULL || this->mObjectSpriteParameter != NULL;
}

sf::Sprite* MapObject::getObjectSprite()
{
	return this->mObjectSprite;
}

bool MapObject::hasObjectSprite()
{
	return this->mObjectSprite != NULL;
}

int MapObject::getObjectSpriteWidth()
{
	if(this->mObjectSprite != NULL)
		return this->mObjectSprite->getLocalBounds().width;
	else 
		return 0;
}

int MapObject::getObjectSpriteHeight()
{
	if(this->mObjectSprite != NULL)
		return this->mObjectSprite->getLocalBounds().height;
	else 
		return 0;
}

int MapObject::getObjectSpriteRadius()
{
	return this->getObjectSpriteWidth() > this->getObjectSpriteHeight() ? this->getObjectSpriteWidth() : this->getObjectSpriteHeight();
}

SpriteParameter* MapObject::getObjectSpriteParameter()
{
	return this->mObjectSpriteParameter;
}

bool MapObject::hasObjectSpriteParameter()
{
	return this->mObjectSpriteParameter != NULL;
}


//*************************************************************
// Methode
//*************************************************************
void MapObject::update()
{
	Rotable::update();

	if(!this->hasSector())
		this->updateVisible();

	if(this->isVisible())
	{
		this->updateScreenPosition();
		this->updateSprite();
	}
}

void MapObject::update( sf::Event p_event )
{
	Selectable::update(p_event);
}

void MapObject::updateSprite()
{
	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mObjectSpriteParameter != NULL)
		this->mObjectSpriteParameter->getSprite().setPosition(objectPositionScreen.x, objectPositionScreen.y);

	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void MapObject::updateMouseOver()
{
	if(!EventManager::eventManager->isMouseOverEvent() || this->isMouseOverForced())
	{
		sf::Vector2f mousePosition = EventManager::eventManager->getMousePositionMapLocal(this->getPlane());
		sf::Vector2f objectPositionScreen = this->getScreenPosition();
		objectPositionScreen.x -= this->Object::getWidth() / 2;
		objectPositionScreen.y -= this->Object::getHeight() / 2;
		bool mouseOverChanged = false;
		if( Tools::pointOnObject(mousePosition.x, mousePosition.y, objectPositionScreen.x, objectPositionScreen.y, objectPositionScreen.x + this->mWidth, objectPositionScreen.y + this->mHeight) )
		{
			mouseOverChanged = !this->mMouseOver;
			this->mMouseOver = true;
			EventManager::eventManager->raiseMouseOverEvent();
		}
		else
		{
			mouseOverChanged = this->mMouseOver;
			this->mMouseOver = false;
		}

		if(mouseOverChanged)
			this->notifyMouseOverChanged();
	}	
	else
	{
		bool mouseOverChanged = this->mMouseOver;
		this->mMouseOver = false;
		if(mouseOverChanged)
			this->notifyMouseOverChanged();
	}
}

void MapObject::updateScreenPosition()
{
	sf::Vector2f tmpPosition = Camera::getObjectPositionInScreen(this);
	if(tmpPosition.x != this->mScreenPosition.x || tmpPosition.y != this->mScreenPosition.y)
	{
		this->mScreenPosition = tmpPosition;
		this->notifyScreenPositionChanged();
	}
}

void MapObject::updateVisible()
{
	sf::Vector2f cameraPositionInPlace = Camera::getInstance()->getPositionInPlane(this->getPlane());
	int demiScreenWidthInPlane = Camera::getInstance()->getCameraPlaneWidth() / 2;
	int demiScreenHeightInPlane = Camera::getInstance()->getCameraPlaneHeight() / 2;
	bool valueVisible = !(	this->Object::getX() + this->getWidthHalf() < cameraPositionInPlace.x - demiScreenWidthInPlane || 
							this->Object::getX() - this->getWidthHalf() > cameraPositionInPlace.x + demiScreenWidthInPlane ||
							this->Object::getY() + this->getHeightHalf() < cameraPositionInPlace.y - demiScreenHeightInPlane ||
							this->Object::getY() - this->getHeightHalf() > cameraPositionInPlace.y + demiScreenHeightInPlane);
	Object::setVisible(valueVisible);
}

void MapObject::updateHitBox()
{
	this->mHitBox.width = this->Object::getWidth();
	this->mHitBox.height = this->Object::getHeight();
	this->mHitBox.left = this->mScreenPosition.x - this->MapObject::getWidthHalf();
	this->mHitBox.top = this->mScreenPosition.y - this->MapObject::getHeightHalf();
}

void MapObject::notifyVisibleChanged()
{
	Selectable::notifyVisibleChanged();
	if(this->isVisible())
	{
		if(!this->isSpriteLoaded())
			this->loadSprite();
	}
	else
	{
		this->unloadSprite();
	}
}

void MapObject::notifyScreenPositionChanged()
{
	this->updateHitBox();
}

void MapObject::notifySizeChanged()
{
	Selectable::notifySizeChanged();
	this->updateHitBox();
}

void MapObject::notifyRotationChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setRotation(this->getRotation());

	if(this->mObjectSpriteParameter != NULL)
		this->mObjectSpriteParameter->getSprite().setRotation(this->getRotation());
}

void MapObject::notifyScaleChanged()
{

}

void MapObject::draw()
{
	if(this->isVisible())
	{
		/*
		// Debug Shape
		sf::RectangleShape debugShape;
		debugShape.setFillColor(sf::Color(255, 255, 255, 150));
		debugShape.setSize(sf::Vector2f(this->mHitBox.width, this->mHitBox.height));
		debugShape.setPosition(this->mHitBox.left, this->mHitBox.top);
		Resource::resource->getApp()->draw(debugShape);
		//*/

		if(this->mObjectSprite != NULL)
			Resource::resource->getApp()->draw(*this->mObjectSprite);
		else if(this->mObjectSpriteParameter != NULL)
			Resource::resource->getApp()->draw(this->mObjectSpriteParameter->getSprite());
	}
}

void MapObject::activateSelectable()
{
	this->setUpdateSelected(true);
	this->activateClickable();
}

void MapObject::desactivateSelectable()
{
	this->setUpdateSelected(false);
}

void MapObject::activateClickable()
{
	this->setUpdateClicked(true);
	this->activateFocusable();
}

void MapObject::desactivateClickable()
{
	this->setUpdateClicked(false);
	this->desactivateSelectable();
}

void MapObject::activateFocusable()
{
	this->setUpdateFocus(true);
	this->activateOverable();
}

void MapObject::desactivateFocusable()
{
	this->setUpdateFocus(false);
	this->desactivateClickable();
}

void MapObject::activateOverable()
{
	this->setUpdateMouseOver(true);
}

void MapObject::desactivateOverable()
{
	this->setUpdateMouseOver(false);
	this->desactivateFocusable();
}

void MapObject::loadSprite()
{
	this->unloadSprite();
}

void MapObject::unloadSprite()
{
	if(this->mObjectSprite != NULL)
	{
		delete this->mObjectSprite;
		this->mObjectSprite = NULL;
	}

	if(this->mObjectSpriteParameter != NULL)
	{
		delete this->mObjectSpriteParameter;
		this->mObjectSpriteParameter = NULL;
	}
}

void MapObject::setObjectSprite( std::string p_sprite )
{
	if(this->mObjectSprite != NULL)
	{
		delete this->mObjectSprite;
		this->mObjectSprite = NULL;
	}

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(p_sprite));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
}

bool MapObject::intersect( MapObject* p_object )
{
	if(p_object == NULL || p_object == this || p_object->getPlane() != this->getPlane())
		return false;

	sf::FloatRect thisRect(this->Object::getX() - this->getWidthHalf(), this->Object::getY() - this->getHeightHalf(), this->Object::getWidth(), this->Object::getHeight());
	sf::FloatRect objectRect(p_object->Object::getX() - p_object->getWidthHalf(), p_object->Object::getY() - p_object->getHeightHalf(), p_object->Object::getWidth(), p_object->Object::getHeight());
	return thisRect.intersects(objectRect);
}

int MapObject::cover( MapObject* p_object )
{
	if(p_object == NULL)
		return 0;

	if(!this->mHitBox.intersects(p_object->mHitBox))
		return 0;

	// Compute intersects
	int intersectPoint = 0;
	bool intersectTopLeft = false;
	bool intersectTopRight = false;
	bool intersectBottomLeft = false;
	bool intersectBottomRight = false;

	if(p_object->mHitBox.contains(this->mHitBox.left, this->mHitBox.top))
	{
		intersectPoint++;
		intersectTopLeft = true;
	}

	if(p_object->mHitBox.contains(this->mHitBox.left + this->mHitBox.width, this->mHitBox.top))
	{
		intersectPoint++;
		intersectTopRight = true;
	}

	if(p_object->mHitBox.contains(this->mHitBox.left, this->mHitBox.top + this->mHitBox.height))
	{
		intersectPoint++;
		intersectBottomLeft = true;
	}

	if(p_object->mHitBox.contains(this->mHitBox.left + this->mHitBox.width, this->mHitBox.top + this->mHitBox.height))
	{
		intersectPoint++;
		intersectBottomRight = true;
	}

	// Compute cover X and Y
	int coverX = 0;
	int coverY = 0;
	
	if(intersectPoint == 0)
	{
		if(this->mHitBox.left < p_object->mHitBox.left && this->mHitBox.left + this->mHitBox.width > p_object->mHitBox.left + p_object->mHitBox.width)
		{
			coverX = p_object->mHitBox.width;
			if(this->mHitBox.top < p_object->mHitBox.top)
				coverY = (this->mHitBox.top + this->mHitBox.height) - p_object->mHitBox.top;
			else
				coverY = p_object->mHitBox.top + p_object->mHitBox.height - this->mHitBox.top;
		}
		else
		{
			if(this->mHitBox.left < p_object->mHitBox.left)
				coverX = (this->mHitBox.left + this->mHitBox.width) - p_object->mHitBox.left;
			else
				coverX = p_object->mHitBox.left + p_object->mHitBox.width - this->mHitBox.left;
			coverY = p_object->mHitBox.height;
		}
	}
	else if(intersectPoint == 1)
	{
		if(intersectTopLeft || intersectBottomLeft)
			coverX = p_object->mHitBox.left + p_object->mHitBox.width - this->mHitBox.left;
		else if(intersectTopRight || intersectBottomRight)
			coverX = (this->mHitBox.left + this->mHitBox.width) - p_object->mHitBox.left;

		if(intersectTopLeft || intersectTopRight)
			coverY = p_object->mHitBox.top + p_object->mHitBox.height - this->mHitBox.top;
		else if(intersectBottomLeft || intersectBottomRight)
			coverY = (this->mHitBox.top + this->mHitBox.height) - p_object->mHitBox.top;
	}
	else if(intersectPoint == 2)
	{
		if(intersectBottomLeft && intersectBottomRight)
		{
			coverX = this->mHitBox.width;
			coverY = (this->mHitBox.top + this->mHitBox.height) - p_object->mHitBox.top;
		}
		else if(intersectTopLeft && intersectTopRight)
		{
			coverX = this->mHitBox.width;;
			coverY = p_object->mHitBox.top + p_object->mHitBox.height - this->mHitBox.top;
		}
		else if(intersectTopRight && intersectBottomRight)
		{
			coverX = (this->mHitBox.left + this->mHitBox.width) - p_object->mHitBox.left;
			coverY = this->mHitBox.height;
		}
		else 
		{
			coverX = p_object->mHitBox.left + p_object->mHitBox.width - this->mHitBox.left;
			coverY = this->mHitBox.height;
		}
	}
	else
	{
		coverX = this->mHitBox.width;
		coverY = this->mHitBox.height;
	}

	// Return
	return coverX * coverY;
}

float MapObject::coverPercent( MapObject* p_object )
{
	float cover = (float)this->cover(p_object);
	float area = (float)p_object->getArea();
	float returnValue = cover / area;
	if(returnValue > 1)
		returnValue = 1;
	return returnValue;
}


//*************************************************************
// Static Methods
//*************************************************************
float MapObject::getPlaneRatio( int plane )
{
	if(plane >= MapObject::getPlaneForeground() && plane <= MapObject::getPlaneBackground())
		return MapObject::mPlaneRatio[plane];
	else
		return 1;
}

int MapObject::getPlaneForeground()
{
	return MAPOBJECT_PLANE_1; 
}

int MapObject::getPlaneBackground()
{
	return MAPOBJECT_PLANE_21;
}

sf::Vector2f MapObject::convertPosition( sf::Vector2f position, int sourcePlane, int destinationPlane )
{
	sf::Vector2f newPosition;
	newPosition.x = (position.x / MapObject::getPlaneRatio(sourcePlane)) * MapObject::getPlaneRatio(destinationPlane);
	newPosition.y = (position.y / MapObject::getPlaneRatio(sourcePlane)) * MapObject::getPlaneRatio(destinationPlane);
	return newPosition;
}

sf::Vector2i MapObject::convertPosition( sf::Vector2i position, int sourcePlane, int destinationPlane )
{
	sf::Vector2f tmp = MapObject::convertPosition(sf::Vector2f(position.x, position.y), sourcePlane, destinationPlane);
	return sf::Vector2i(tmp.x, tmp.y);
}

float MapObject::convertSize( float size, int sourcePlane, int destinationPlane )
{
	return (size / MapObject::getPlaneRatio(sourcePlane)) * MapObject::getPlaneRatio(destinationPlane);
}

int MapObject::convertSize( int size, int sourcePlane, int destinationPlane )
{
	return MapObject::convertSize((float)size, sourcePlane, destinationPlane);
}

void MapObject::init()
{
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_1]		= (float)MAPOBJECT_PLANE_1_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_2]		= (float)MAPOBJECT_PLANE_2_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_3]		= (float)MAPOBJECT_PLANE_3_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_4]		= (float)MAPOBJECT_PLANE_4_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_5]		= (float)MAPOBJECT_PLANE_5_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_6]		= (float)MAPOBJECT_PLANE_6_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_7]		= (float)MAPOBJECT_PLANE_7_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_8]		= (float)MAPOBJECT_PLANE_8_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_9]		= (float)MAPOBJECT_PLANE_9_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_10]		= (float)MAPOBJECT_PLANE_10_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_11]		= (float)MAPOBJECT_PLANE_11_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_12]		= (float)MAPOBJECT_PLANE_12_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_13]		= (float)MAPOBJECT_PLANE_13_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_14]		= (float)MAPOBJECT_PLANE_14_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_15]		= (float)MAPOBJECT_PLANE_15_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_16]		= (float)MAPOBJECT_PLANE_16_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_17]		= (float)MAPOBJECT_PLANE_17_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_18]		= (float)MAPOBJECT_PLANE_18_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_19]		= (float)MAPOBJECT_PLANE_19_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_20]		= (float)MAPOBJECT_PLANE_20_RATIO;
	MapObject::mPlaneRatio[MAPOBJECT_PLANE_21]		= (float)MAPOBJECT_PLANE_21_RATIO;
}













