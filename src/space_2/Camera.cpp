#include "Camera.h"
#include "Game.h"
#include "RunningStats.h"
#include "AnimationManager.h"
#include "Jukebox.h"


//*************************************************************
// Define
//*************************************************************
#define ZOOM_DEFAULT		0.0f
#define ZOOM_MIN			0.25f
#define ZOOM_MAX			1.5f
#define ZOOM_INC			0.02f
#define ZOOM_DEC			0.02f


//*************************************************************
// Init statics
//*************************************************************
Camera * Camera::mInstance = NULL;
sf::Vector2f Camera::frameCameraOffset;


//*************************************************************
// Constructor - Destructor
//*************************************************************
Camera::Camera()
{
	// Init with default
	this->mCameraX = 0.0;
	this->mCameraY = 0.0;
	this->mZoom = ZOOM_DEFAULT;
}

Camera::~Camera(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
double Camera::getCameraX()
{
	return this->mCameraX;
}

void Camera::setCameraX( double p_x )
{
	if(this->mCameraX != p_x)
	{
		this->mCameraX = p_x;
		this->notifyPositionChanged();
	}
}

double Camera::getCameraY()
{
	return this->mCameraY;
}

void Camera::setCameraY( double p_y )
{
	if(this->mCameraY != p_y)
	{
		this->mCameraY = p_y;
		this->notifyPositionChanged();
	}
}

void Camera::setCameraPosition( double p_x, double p_y )
{
	if(this->mCameraX != p_x || this->mCameraY != p_y)
	{
		this->mCameraX = p_x;
		this->mCameraY = p_y;
		this->notifyPositionChanged();
	}
}

sf::Vector2f Camera::getPositionInPlane(int p_plane)
{
	return MapObject::convertPosition(sf::Vector2f(this->mCameraX, this->mCameraY), CAMERA_PLANE, p_plane);
}

float Camera::getPlaneWidth( int p_plane )
{
	return (Resource::resource->getViewMap(p_plane)->getSize().x / MapObject::getPlaneRatio(p_plane)) * CAMERA_SCREENSIZE_MULTIPLIER;
}

float Camera::getCameraPlaneWidth()
{
	return Resource::resource->getViewMap(CAMERA_PLANE)->getSize().x * CAMERA_SCREENSIZE_MULTIPLIER;
}

float Camera::getPlaneHeight( int p_plane )
{
	return (Resource::resource->getViewMap(p_plane)->getSize().y / MapObject::getPlaneRatio(p_plane)) * CAMERA_SCREENSIZE_MULTIPLIER;
}

float Camera::getCameraPlaneHeight()
{
	return Resource::resource->getViewMap(CAMERA_PLANE)->getSize().y * CAMERA_SCREENSIZE_MULTIPLIER;
}

float Camera::getZoom()
{
	return this->mZoom;
}

float Camera::getZoom( int p_plane )
{
	return 1 + ((this->mZoom - 1) * MapObject::getPlaneRatio(p_plane));
}

void Camera::setZoom( float p_zoom )
{
	if(p_zoom < ZOOM_MIN)
		p_zoom = ZOOM_MIN;
	else if(p_zoom > ZOOM_MAX)
		p_zoom = ZOOM_MAX;

	bool notify = this->mZoom != p_zoom;
	this->mZoom = p_zoom;

	if(notify)
		this->notifyZoomChanged();
}


//*************************************************************
// Method
//*************************************************************
Camera* Camera::getInstance()
{
	if(Camera::mInstance == NULL)
		Camera::mInstance = new Camera();
	return Camera::mInstance;
}

void Camera::destroyInstance()
{
	if(Camera::mInstance != NULL)
	{
		delete Camera::mInstance;
		Camera::mInstance = NULL;
	}
}

void Camera::draw()
{
	Game::game->getMap()->draw();
	AnimationManager::draw();
	Game::game->getUserInterface()->drawInGame();
	RunningStats::draw();
}

void Camera::incZoom()
{
	this->setZoom(this->getZoom() + ZOOM_INC);
}

void Camera::decZoom()
{
	this->setZoom(this->getZoom() - ZOOM_DEC);
}

void Camera::notifyZoomChanged()
{
	Resource::resource->updateViewMap();
}

void Camera::notifyPositionChanged()
{
	sf::Vector2f positionSector = this->getPositionInPlane(SECTOR_PLANE);
	Jukebox::getInstance()->setListenerPosition(positionSector.x, positionSector.y);
}

sf::Vector2f* Camera::centerPosition( sf::Vector2f* p_position, int p_plane )
{
	sf::View* currentView = Resource::resource->getViewMap(p_plane);
	p_position->x += currentView->getCenter().x;
	p_position->y += currentView->getCenter().y;

	return p_position;
}

sf::Vector2f Camera::getObjectPositionInScreen( MapObject* p_object )
{
	sf::Vector2f screenPosition;
	sf::Vector2f cameraPosition = Camera::getInstance()->getPositionInPlane(p_object->getPlane());
	screenPosition.x = p_object->Object::getX() - cameraPosition.x;
	screenPosition.y = p_object->Object::getY() - cameraPosition.y;
	Camera::centerPosition(&screenPosition, p_object->getPlane());
	return screenPosition;
}