#include "LoadingGameScreen.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
LoadingGameScreen::LoadingGameScreen(void)
{
	this->mTBLoading.setText("Loading...");
}

LoadingGameScreen::~LoadingGameScreen(void)
{
}


//*************************************************************
// Methodss
//*************************************************************
void LoadingGameScreen::launch()
{
	this->setRunning(true);
	this->update();
	this->notifyAppSizeChanged();
	while(Resource::resource->getApp()->isOpen() && Resource::resource->isAppRunning() && this->isRunning())
	{		
		// Update
		this->update();

		// Update event
		if(Resource::resource->getApp()->pollEvent(this->mEvent))
		{
			if( this->mEvent.type == sf::Event::Closed)
				Resource::resource->setAppRunning(false);

			if( this->mEvent.type == sf::Event::Resized)
			{
				Resource::resource->resizeAllView();
				this->notifyAppSizeChanged();
			}

			this->update(this->mEvent);
		}

		// Draw
		this->draw();
	}
}

void LoadingGameScreen::update()
{
	BaseScreen::update();
}

void LoadingGameScreen::update( sf::Event p_event )
{

}

void LoadingGameScreen::updatePosition()
{
	BaseScreen::updatePosition();
	this->mTBLoading.setPosition(0, 0);
}

void LoadingGameScreen::draw()
{
	Resource::resource->getApp()->clear(sf::Color::White);
	Resource::resource->getApp()->draw(this->mBackgroundSprite);
	this->mTBLoading.draw();
	Resource::resource->getApp()->display();
}
