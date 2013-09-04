#include "StationScreen.h"
#include "ClockManager.h"


//*************************************************************
// Define
//*************************************************************
#define BUTTON_WIDTH			80
#define BUTTON_HEIGHT			18


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
StationScreen::StationScreen(void)
{
	this->mStation = NULL;

	this->mButtonUndock.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->mButtonUndock.setTitle(Resource::resource->getBundle()->getString("undock"));

	this->notifyAppSizeChanged();
}

StationScreen::~StationScreen(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Station* StationScreen::getStation()
{
	return this->mStation;
}

void StationScreen::setStation( Station* p_station )
{
	if(this->mStation != p_station)
	{
		this->mStation = p_station;
		this->notifyStationChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void StationScreen::launch( Station* p_station )
{
	this->setStation(p_station);
	while(Resource::resource->getApp()->isOpen() && Resource::resource->isAppRunning() && this->getStation() != NULL)
	{
		// Update
		EventManager::eventManager->reset();
		if(Resource::resource->getApp()->pollEvent(this->mEvent))
		{
			if( this->mEvent.type == sf::Event::Closed)
				Resource::resource->setAppRunning(false);

			if( this->mEvent.type == sf::Event::Resized)
			{
				Resource::resource->resizeAllView();
				this->notifyAppSizeChanged();
			}

			this->update(mEvent);
		}
		this->update();

		// Draw
		Resource::resource->getApp()->clear(sf::Color::White);
		this->draw();
		PopupBubble::drawAll();
		Resource::resource->getApp()->display();		
	}
}

void StationScreen::update()
{
	EventManager::eventManager->reset();
	ClockManager::update();
}

void StationScreen::updatePosition()
{
	this->mBackground.setPosition(0, 0);
	this->mButtonUndock.setPosition(10, 10);
}

void StationScreen::updateBackgroundScale()
{
	float scaleWidth = Resource::resource->getViewUi()->getSize().x / this->mBackground.getLocalBounds().width;
	float scaleHeight = Resource::resource->getViewUi()->getSize().y / this->mBackground.getLocalBounds().height;
	float scale = scaleWidth > scaleHeight ? scaleWidth : scaleHeight;
	this->mBackground.setScale(scale, scale);
	this->updatePosition();
}

void StationScreen::update( sf::Event p_event )
{
	this->mButtonUndock.update(p_event);
	if(this->mButtonUndock.isClicked())
		this->setStation(NULL);
}

void StationScreen::draw()
{
	Resource::resource->getApp()->draw(this->mBackground);
	this->mButtonUndock.draw();
}

void StationScreen::notifyAppSizeChanged()
{
	this->updatePosition();
	this->updateBackgroundScale();
}

void StationScreen::notifyStationChanged()
{
	if(this->getStation() != NULL)
	{
		this->mBackground.setTexture(*Resource::resource->getTexture(this->getStation()->getModel()->getScreenSprite()));
		this->updateBackgroundScale();
	}
}



