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
	this->mButtonUndock.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->mButtonUndock.setTitle(Resource::resource->getBundle()->getString("undock"));
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
	this->mStation = p_station;
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
	this->mButtonUndock.setPosition(10, 10);
}

void StationScreen::update( sf::Event p_event )
{
	this->mButtonUndock.update(p_event);
	if(this->mButtonUndock.isClicked())
		this->setStation(NULL);
}

void StationScreen::draw()
{
	this->mButtonUndock.draw();
}

void StationScreen::notifyAppSizeChanged()
{
	this->updatePosition();
}



