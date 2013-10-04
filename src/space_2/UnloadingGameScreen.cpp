#include "UnloadingGameScreen.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
UnloadingGameScreen::UnloadingGameScreen(void)
{
	this->mTBUnloading.setText("Unloading...");
}

UnloadingGameScreen::~UnloadingGameScreen(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void UnloadingGameScreen::launch()
{
	this->setRunning(true);
	this->update();
	this->notifyAppSizeChanged();
	while(this->isRunning())
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

void UnloadingGameScreen::update()
{
	BaseScreen::update();
}

void UnloadingGameScreen::update( sf::Event p_event )
{

}

void UnloadingGameScreen::updatePosition()
{
	BaseScreen::updatePosition();
	this->mTBUnloading.setPosition(0, 0);
}

void UnloadingGameScreen::draw()
{
	Resource::resource->getApp()->clear(sf::Color::White);
	Resource::resource->getApp()->draw(this->mBackgroundSprite);
	this->mTBUnloading.draw();
	Resource::resource->getApp()->display();
}	
