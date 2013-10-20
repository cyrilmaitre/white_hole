#include "MapMiniView.h"
#include "Map.h"
#include "Camera.h"
#include "ToolsImage.h"
#include "ToolsMap.h"


//*************************************************************
// Define
//*************************************************************
#define BORDER_COLOR					sf::Color(100, 100, 100)
#define BORDER_SIZE						2
#define BACKGROUND_COLOR				sf::Color(0, 0, 0)
#define CROSS_SIZE						1
#define CROSS_COLOR						sf::Color(255, 255, 255)
#define CLOUD_COLOR						sf::Color(100, 100, 100)
#define TEXTURE_BACKGROUND_COLOR		sf::Color(100, 100, 100)
#define TEXTURE_FOREGROUND_COLOR		sf::Color(0, 0, 0, 0)
#define TEXTURE_FIRSTPLANE_COLOR		sf::Color(0, 0, 0, 0)

#define ZOOM_LARGE						1.0
#define ZOOM_MEDIUM						0.21
#define ZOOM_SMALL						0.011

#define ZOOM_FIRSTPLANE					0.6
#define ZOOM_STAR						0.2
#define ZOOM_CLOUDGAZ					0.2
#define ZOOM_CLOUDWRECK					1.0
#define ZOOM_PLANET						0.2
#define ZOOM_PLANET_MINI				0.1

#define ZOOM_STATION					0.2
#define ZOOM_STATION_MINI				0.1
#define ZOOM_NPCSHIP					0.6
#define ZOOM_NPCSHIP_MINI				1

#define FIRSTPLANE_OBJECT_SIZE			5
#define FIRSTPLANE_WRECK_COLOR			sf::Color(0, 0, 255)

#define FIRSTPLANE_REFRESH				1 // Sec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
MapMiniView::MapMiniView(void)
{
	this->mTextureBackground = NULL;
	this->mTextureForeground = NULL;
	this->mTextureFirstPlane = NULL;
	this->mPreviousSector = NULL;

	this->setBorderSize(BORDER_SIZE, true);
	this->setBorderColor(BORDER_COLOR, true);
	this->setBackgroundColor(BACKGROUND_COLOR, true);

	this->mCrossHorizontal.setFillColor(CROSS_COLOR);
	this->mCrossVertical.setFillColor(CROSS_COLOR);

	this->mMapObjectTypeZoom.insert(std::pair<MapObject::MapObjectType, float>(MapObject::MapObjectType::TypeStar, ZOOM_STAR));
	this->mMapObjectTypeZoom.insert(std::pair<MapObject::MapObjectType, float>(MapObject::MapObjectType::TypePlanet, ZOOM_PLANET));
	this->mMapObjectTypeZoom.insert(std::pair<MapObject::MapObjectType, float>(MapObject::MapObjectType::TypeCloudGaz, ZOOM_CLOUDGAZ));
	this->mMapObjectTypeMiniZoom.insert(std::pair<MapObject::MapObjectType, float>(MapObject::MapObjectType::TypePlanet, ZOOM_PLANET_MINI));
	
	this->mEntityTypeZoom.insert(std::pair<MapObject::MapObjectType, float>(MapObject::MapObjectType::TypeStation, ZOOM_STATION));
	this->mEntityTypeZoom.insert(std::pair<MapObject::MapObjectType, float>(MapObject::MapObjectType::TypeNpcShip, ZOOM_NPCSHIP));
	this->mEntityTypeMiniZoom.insert(std::pair<MapObject::MapObjectType, float>(MapObject::MapObjectType::TypeStation, ZOOM_STATION_MINI));

	this->mTextureColumn = 0;
	this->mTextureLine = 0;
	this->mTextureOffsetX = 0;
	this->mTextureOffsetY = 0;
	this->mPreviousSectorXBegin = 0;
	this->mPreviousSectorXEnd = 0;
	this->mPreviousSectorYBegin = 0;
	this->mPreviousSectorYEnd = 0;
	this->setZoom(1);
	this->mZoomChanged = true;
}

MapMiniView::~MapMiniView(void)
{
	if(this->mTextureBackground != NULL)
		delete this->mTextureBackground;

	if(this->mTextureForeground != NULL)
		delete this->mTextureForeground;

	if(this->mTextureFirstPlane != NULL)
		delete this->mTextureFirstPlane;
}


//*************************************************************
// Getters - Setters
//*************************************************************
int MapMiniView::getWidth()
{
	return Object::getWidth();
}

int MapMiniView::getHeight()
{
	return Object::getHeight();
}

Map* MapMiniView::getMap()
{
	return this->mMap;
}

void MapMiniView::setMap( Map* p_map )
{
	this->mMap = p_map;
}

float MapMiniView::getZoom()
{
	return this->mZoom;
}

void MapMiniView::setZoom( float p_zoom )
{
	this->mZoom = p_zoom;
	this->notifyZoomChanged();
}

bool MapMiniView::isZoomChanged()
{
	bool returnValue = this->mZoomChanged;
	this->mZoomChanged = false;
	return returnValue;
}

int MapMiniView::getSectorMiniWidth()
{
	return SECTOR_MINI_WIDTH * this->getZoom();
}

int MapMiniView::getSectorMiniHeight()
{
	return SECTOR_MINI_HEIGHT * this->getZoom();
}

bool MapMiniView::isMapObjectTypeDraw( MapObject::MapObjectType p_type )
{
	std::map<MapObject::MapObjectType, float>::iterator it;
	it = this->mMapObjectTypeZoom.find(p_type);

	if(it != this->mMapObjectTypeZoom.end())
		return this->getZoom() >= it->second;
	
	return false;
}

bool MapMiniView::isMapObjectTypeMiniDraw( MapObject::MapObjectType p_type )
{
	std::map<MapObject::MapObjectType, float>::iterator it;
	it = this->mMapObjectTypeMiniZoom.find(p_type);

	if(it != this->mMapObjectTypeMiniZoom.end())
		return this->getZoom() >= it->second;

	return false;
}

bool MapMiniView::isEntityTypeDraw( MapObject::MapObjectType p_type )
{
	std::map<MapObject::MapObjectType, float>::iterator it;
	it = this->mEntityTypeZoom.find(p_type);

	if(it != this->mEntityTypeZoom.end())
		return this->getZoom() >= it->second;

	return false;
}

bool MapMiniView::isEntityTypeMiniDraw( MapObject::MapObjectType p_type )
{
	std::map<MapObject::MapObjectType, float>::iterator it;
	it = this->mEntityTypeMiniZoom.find(p_type);

	if(it != this->mEntityTypeMiniZoom.end())
		return this->getZoom() >= it->second;

	return false;
}

std::string MapMiniView::getObjectMiniId( MapObject::MapObjectType p_type )
{
	if(p_type == MapObject::MapObjectType::TypePlanet)
		return IC_16X16_PLANET;
	else if(p_type == MapObject::MapObjectType::TypeStation)
		return IC_16X16_STATION;

	return "";
}


//*************************************************************
// Methods
//*************************************************************
void MapMiniView::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updatePosition();
}

void MapMiniView::notifySizeChanged()
{
	Block::notifySizeChanged();
	this->mCrossHorizontal.setSize(sf::Vector2f(this->Object::getWidth(), CROSS_SIZE));
	this->mCrossVertical.setSize(sf::Vector2f(CROSS_SIZE, this->Object::getHeight()));

	this->updateTexture();
	this->updatePosition();
}

void MapMiniView::notifyZoomChanged()
{
	this->mZoomChanged = true;
	this->updateTexture();
}

void MapMiniView::createTexture()
{
	this->mTextureBackground->clear(TEXTURE_BACKGROUND_COLOR);
	this->mTextureForeground->clear(TEXTURE_FOREGROUND_COLOR);

	if(this->getZoom() <= ZOOM_SMALL)
	{
		this->createTextureBackgroundColor();
	}
	else
	{
		this->createTextureBackground();
		this->createTextureObject();
		this->createTextureForeground();
	}	

	this->mTextureBackground->display();
	this->mTextureForeground->display();

	this->mSpriteBackground.setTexture(this->mTextureBackground->getTexture());
	this->mSpriteForeground.setTexture(this->mTextureForeground->getTexture());
}

void MapMiniView::createTextureObject()
{
	// Draw object
	int currentTextureColumn = 0;
	int currentTextureLine = 0;
	for(int i = this->mPreviousSectorXBegin; i <= this->mPreviousSectorXEnd; i++)
	{
		for(int j = this->mPreviousSectorYBegin; j <= this->mPreviousSectorYEnd; j++)
		{
			Sector* currentSector = this->mMap->getSector(i, j);
			if(currentSector != NULL)
			{
				// Map Object
				for(int o = 0; o < currentSector->getObjectsCount(); o++)
				{
					MapObject* currentObject = currentSector->getObject(o);
					if(this->isMapObjectTypeDraw(currentObject->getObjectType()))
					{
						if(currentObject->hasObjectSprite())
						{
							sf::Sprite currentObjectSprite(*currentObject->getObjectSprite());
							ToolsImage::resizeSprite(&currentObjectSprite, currentObject->getWidth(SECTOR_PLANE) * this->getZoom(), currentObject->getHeight(SECTOR_PLANE) * this->getZoom());
							currentObjectSprite.setPosition(currentTextureColumn * this->getSectorMiniWidth() + currentObject->getSectorX() * this->getZoom(), 
															currentTextureLine * this->getSectorMiniHeight() + currentObject->getSectorY() * this->getZoom());
							this->mTextureBackground->draw(currentObjectSprite);
						}
					}
					else if(this->isMapObjectTypeMiniDraw(currentObject->getObjectType()))
					{
						sf::Sprite currentObjectSprite = SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(this->getObjectMiniId(currentObject->getObjectType()));
						currentObjectSprite.setOrigin(currentObjectSprite.getLocalBounds().width / 2, currentObjectSprite.getLocalBounds().height / 2);
						currentObjectSprite.setPosition(currentTextureColumn * this->getSectorMiniWidth() + currentObject->getSectorX() * this->getZoom(), 
							currentTextureLine * this->getSectorMiniHeight() + currentObject->getSectorY() * this->getZoom());
						this->mTextureBackground->draw(currentObjectSprite);
					}
				}
			}
			currentTextureLine++;
		}
		currentTextureColumn++;
		currentTextureLine = 0;
	}
}

void MapMiniView::createTextureBackground()
{
	sf::Sprite backgroundSprite;
	int currentTextureColumn = 0;
	int currentTextureLine = 0;

	// Draw background
	for(int i = this->mPreviousSectorXBegin; i <= this->mPreviousSectorXEnd; i++)
	{
		for(int j = this->mPreviousSectorYBegin; j <= this->mPreviousSectorYEnd; j++)
		{
			Sector* currentSector = this->mMap->getSector(i, j);
			if(currentSector != NULL && currentSector->isVisited())
			{
				backgroundSprite.setTexture(currentSector->getBackground()->getBackgroundTexture()->getTexture(), true);
				ToolsImage::resizeSprite(&backgroundSprite, this->getSectorMiniWidth(), this->getSectorMiniHeight());
				backgroundSprite.setPosition(currentTextureColumn * this->getSectorMiniWidth(), currentTextureLine * this->getSectorMiniHeight());
				this->mTextureBackground->draw(backgroundSprite);
			}
			currentTextureLine++;
		}
		currentTextureColumn++;
		currentTextureLine = 0;
	}
}

void MapMiniView::createTextureForeground()
{
	int currentTextureColumn = 0;
	int currentTextureLine = 0;
	sf::RectangleShape cloudShape(sf::Vector2f(this->getSectorMiniWidth(), this->getSectorMiniHeight()));
	cloudShape.setFillColor(CLOUD_COLOR);

	// Draw foreground
	for(int i = this->mPreviousSectorXBegin; i <= this->mPreviousSectorXEnd; i++)
	{
		for(int j = this->mPreviousSectorYBegin; j <= this->mPreviousSectorYEnd; j++)
		{
			Sector* currentSector = this->mMap->getSector(i, j);
			if(currentSector == NULL || !currentSector->isVisited())
			{
				cloudShape.setPosition(currentTextureColumn * this->getSectorMiniWidth(), currentTextureLine * this->getSectorMiniHeight());
				this->mTextureForeground->draw(cloudShape);
			}
			currentTextureLine++;
		}
		currentTextureColumn++;
		currentTextureLine = 0;
	}
}

void MapMiniView::createTextureFirstPlane()
{
	this->mTextureFirstPlane->clear(TEXTURE_FIRSTPLANE_COLOR);

	// NpcSpawner
	if(this->isEntityTypeDraw(MapObject::MapObjectType::TypeNpcShip))
	{
		Sector* sectorTopLeft = this->mMap->getSector(this->mPreviousSectorXBegin, this->mPreviousSectorYBegin, true);
		int topLeftSectorX = sectorTopLeft->getX();
		int topLeftSectorY = sectorTopLeft->getY();
		sf::CircleShape npcWickedShape;
		for(int i = 0; i < this->getMap()->getNpcShipSpawner()->getSpawnedNpcShipCount(); i++)
		{
			NpcShip* currentNpc = this->getMap()->getNpcShipSpawner()->getSpawnedNpcShip(i);
			sf::Vector2f currentNpcPosition = currentNpc->getPosition(SECTOR_PLANE);

			float radius = ToolsMap::getRadius(currentNpc, SECTOR_PLANE) * this->getZoom();
			if(radius < 1.f)
				radius = 1.f;
			npcWickedShape.setRadius(radius);
			npcWickedShape.setOrigin(npcWickedShape.getRadius(), npcWickedShape.getRadius());

			npcWickedShape.setFillColor(currentNpc->getNpcType()->getColor());
			npcWickedShape.setPosition((currentNpcPosition.x - topLeftSectorX) * this->getZoom(), (currentNpcPosition.y - topLeftSectorY) * this->getZoom());
			this->mTextureFirstPlane->draw(npcWickedShape);
		}
	}

	// Wreck
	if(this->isEntityTypeDraw(MapObject::MapObjectType::TypeWreck))
	{

	}

	// Sector Entities
	int currentTextureColumn = 0;
	int currentTextureLine = 0;
	for(int i = this->mPreviousSectorXBegin; i <= this->mPreviousSectorXEnd; i++)
	{
		for(int j = this->mPreviousSectorYBegin; j <= this->mPreviousSectorYEnd; j++)
		{
			Sector* currentSector = this->mMap->getSector(i, j);
			if(currentSector != NULL)
			{
				for(int o = 0; o < currentSector->getEntitiesCount(); o++)
				{
					Entity* currentEntity = currentSector->getEntity(o);
					if(this->isEntityTypeDraw(currentEntity->getObjectType()))
					{
						Npc* castNpc = dynamic_cast<Npc*>(currentEntity);
						if(castNpc == 0)
						{
							sf::Sprite currentObjectSprite(*currentEntity->getObjectSprite());
							ToolsImage::resizeSprite(&currentObjectSprite, currentEntity->getWidth(SECTOR_PLANE) * this->getZoom(), currentEntity->getHeight(SECTOR_PLANE) * this->getZoom());
							currentObjectSprite.setPosition(currentTextureColumn * this->getSectorMiniWidth() + currentEntity->getSectorX() * this->getZoom(), 
															currentTextureLine * this->getSectorMiniHeight() + currentEntity->getSectorY() * this->getZoom());
							this->mTextureFirstPlane->draw(currentObjectSprite);
						}
						else
						{
							sf::CircleShape entityShape;
							entityShape.setRadius(ToolsMap::getRadius(currentEntity, SECTOR_PLANE) * this->getZoom());
							entityShape.setOrigin(entityShape.getLocalBounds().width / 2, entityShape.getLocalBounds().height / 2);

							entityShape.setFillColor(castNpc->getNpcType()->getColor());
							entityShape.setPosition(currentTextureColumn * this->getSectorMiniWidth() + currentEntity->getSectorX() * this->getZoom(), 
													currentTextureLine * this->getSectorMiniHeight() + currentEntity->getSectorY() * this->getZoom());
							this->mTextureFirstPlane->draw(entityShape);
						}
					}
					else if(this->isEntityTypeMiniDraw(currentEntity->getObjectType()))
					{
						sf::Sprite currentObjectSprite = SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(this->getObjectMiniId(currentEntity->getObjectType()));
						currentObjectSprite.setOrigin(currentObjectSprite.getLocalBounds().width / 2, currentObjectSprite.getLocalBounds().height / 2);
						currentObjectSprite.setPosition(currentTextureColumn * this->getSectorMiniWidth() + currentEntity->getSectorX() * this->getZoom(), 
														currentTextureLine * this->getSectorMiniHeight() + currentEntity->getSectorY() * this->getZoom());
						this->mTextureFirstPlane->draw(currentObjectSprite);
					}
				}
			}
			currentTextureLine++;
		}
		currentTextureColumn++;
		currentTextureLine = 0;
	}

	// Display
	this->mTextureFirstPlane->display();
	this->mSpriteFirstPlane.setTexture(this->mTextureFirstPlane->getTexture());
}

void MapMiniView::createTextureBackgroundColor()
{
	int currentTextureColumn = 0;
	int currentTextureLine = 0;

	// Draw background
	for(int i = this->mPreviousSectorXBegin; i <= this->mPreviousSectorXEnd; i++)
	{
		for(int j = this->mPreviousSectorYBegin; j <= this->mPreviousSectorYEnd; j++)
		{
			Sector* currentSector = this->mMap->getSector(i, j);
			if(currentSector != NULL && currentSector->isVisited())
			{
				sf::RectangleShape* sectorShape = currentSector->getDangerLevel()->getShapeMapMini();
				ToolsImage::resizeRectangleShape(sectorShape, this->getSectorMiniWidth(), this->getSectorMiniHeight());
				sectorShape->setPosition(currentTextureColumn * this->getSectorMiniWidth(), currentTextureLine * this->getSectorMiniHeight());
				this->mTextureBackground->draw(*sectorShape);
			}
			currentTextureLine++;
		}
		currentTextureColumn++;
		currentTextureLine = 0;
	}
}

void MapMiniView::update()
{
	Sector* currentSector = this->mMap->getCurrentSector();

	// Update texture if necessary
	if(	this->mPreviousSector != currentSector)
	{
		// Update previous
		this->mPreviousSector = currentSector;
		this->mPreviousSectorXBegin = currentSector->getIdSectorX() - ceil((float)this->mTextureColumn / 2.f);
		this->mPreviousSectorXEnd = currentSector->getIdSectorX() + ceil((float)this->mTextureColumn / 2.f);
		this->mPreviousSectorYBegin = currentSector->getIdSectorY() - ceil((float)this->mTextureLine / 2.f);
		this->mPreviousSectorYEnd = currentSector->getIdSectorY() + ceil((float)this->mTextureLine / 2.f);

		// Create texture
		this->createTexture();
	}

	// Update texture first plane
	if(this->mClockRefreshFirstPlane.getElapsedTimeAsSeconds() > FIRSTPLANE_REFRESH || this->isZoomChanged())
	{
		this->createTextureFirstPlane();
		this->mClockRefreshFirstPlane.restart();
	}

	// Update texture rect
	sf::Vector2f cameraPosition = Camera::getInstance()->getPositionInPlane(SECTOR_PLANE);
	int offsetX = ((currentSector->getX() - cameraPosition.x) / SECTOR_WIDTH) * this->getSectorMiniWidth();
	int offsetY = ((currentSector->getY() - cameraPosition.y) / SECTOR_HEIGHT) * this->getSectorMiniHeight();

	sf::IntRect cameraRect = sf::IntRect(	this->mTextureOffsetX + Tools::getAbsolute(offsetX), 
											this->mTextureOffsetY + Tools::getAbsolute(offsetY), 
											this->getWidth(), this->getHeight());
	this->mSpriteBackground.setTextureRect(cameraRect);
	this->mSpriteForeground.setTextureRect(cameraRect);
	this->mSpriteFirstPlane.setTextureRect(cameraRect);
}

void MapMiniView::updatePosition()
{
	this->mSpriteBackground.setPosition(this->getX(), this->getY());
	this->mSpriteForeground.setPosition(this->getX(), this->getY());
	this->mSpriteFirstPlane.setPosition(this->getX(), this->getY());

	this->mCrossHorizontal.setPosition(this->getX(), this->getY() + (this->Object::getHeight() - CROSS_SIZE) / 2);
	this->mCrossVertical.setPosition(this->getX() + (this->Object::getWidth() - CROSS_SIZE) / 2, this->getY());
}

void MapMiniView::updateTexture()
{
	// Compute texture size
	int textureWidth = this->getWidth() + this->getSectorMiniWidth() * 2;
	if(textureWidth % this->getSectorMiniWidth() != 0)
		textureWidth += this->getSectorMiniWidth() - textureWidth % this->getSectorMiniWidth();
	if((textureWidth / this->getSectorMiniWidth()) % 2 != 0)
		textureWidth += this->getSectorMiniWidth();

	int textureHeight = this->getHeight() + this->getSectorMiniHeight() * 2;
	if(textureHeight % this->getSectorMiniHeight() != 0)
		textureHeight += this->getSectorMiniHeight() - textureHeight % this->getSectorMiniHeight();
	if((textureHeight / this->getSectorMiniHeight()) % 2 != 0)
		textureHeight += this->getSectorMiniHeight();

	// Create textures
	if(this->mTextureBackground != NULL)
	{
		delete this->mTextureBackground;
		this->mTextureBackground = NULL;
	}
	this->mTextureBackground = new sf::RenderTexture();
	this->mTextureBackground->create(textureWidth, textureHeight);

	if(this->mTextureForeground != NULL)
	{
		delete this->mTextureForeground;
		this->mTextureForeground = NULL;
	}
	this->mTextureForeground = new sf::RenderTexture();
	this->mTextureForeground->create(textureWidth, textureHeight);

	if(this->getZoom() >= ZOOM_FIRSTPLANE)
	{
		if(this->mTextureFirstPlane != NULL)
		{
			delete this->mTextureFirstPlane;
			this->mTextureFirstPlane = NULL;
		}
		this->mTextureFirstPlane = new sf::RenderTexture();
		this->mTextureFirstPlane->create(textureWidth, textureHeight);
	}

	// Compute Column / line
	this->mTextureColumn = ceil((float)textureWidth / (float)this->getSectorMiniWidth());
	this->mTextureLine = ceil((float)textureHeight / (float)this->getSectorMiniWidth());

	if(this->mTextureColumn % 2 == 0)
		this->mTextureOffsetX = (textureWidth - this->getWidth()) / 2;
	else
		this->mTextureOffsetX = (textureWidth - this->getWidth() + this->getSectorMiniWidth()) / 2;
	
	if(this->mTextureLine % 2 == 0)
		this->mTextureOffsetY = (textureHeight - this->getHeight()) / 2;
	else
		this->mTextureOffsetY = (textureHeight - this->getHeight() + this->getSectorMiniHeight()) / 2;

	// Reset
	this->mPreviousSector = NULL;
	this->mPreviousSectorXBegin = 0;
	this->mPreviousSectorXEnd = 0;
	this->mPreviousSectorYBegin = 0;
	this->mPreviousSectorYEnd = 0;
}

void MapMiniView::draw()
{
	Block::draw();
	Resource::resource->getApp()->draw(this->mSpriteBackground);
	Resource::resource->getApp()->draw(this->mSpriteFirstPlane);
	Resource::resource->getApp()->draw(this->mSpriteForeground);
	Resource::resource->getApp()->draw(this->mCrossHorizontal);
	Resource::resource->getApp()->draw(this->mCrossVertical);
}






