#include "UnloadingGameScreen.h"
#include "ImageGIFFactory.h"


//*************************************************************
// Define
//*************************************************************
#define UNLOADING_FONTSIZE			32
#define UNLOADING_MARGINTOP			50
#define GIFUNLOADING_MARGINTOP		20


//*************************************************************
// Constructor - Destructor
//*************************************************************
UnloadingGameScreen::UnloadingGameScreen(void)
{
	this->mTBUnloading.setText(Resource::resource->getBundle()->getString("unloadingGame"));
	this->mTBUnloading.setFontSize(UNLOADING_FONTSIZE);
	this->mGifUnloading = ImageGIFFactory::getLoadingBert();
}

UnloadingGameScreen::~UnloadingGameScreen(void)
{
	delete this->mGifUnloading;
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
	this->mGifUnloading->update();
}

void UnloadingGameScreen::update( sf::Event p_event )
{

}

void UnloadingGameScreen::updatePosition()
{
	BaseScreen::updatePosition();
	this->mTBUnloading.setPosition((Resource::resource->getViewUi()->getSize().x - this->mTBUnloading.getWidth()) / 2, (Resource::resource->getViewUi()->getSize().y - this->mTBUnloading.getHeight()) / 2 - UNLOADING_MARGINTOP);
	this->mGifUnloading->setPosition((Resource::resource->getViewUi()->getSize().x - this->mGifUnloading->getWidth()) / 2, this->mTBUnloading.getBottomY() + GIFUNLOADING_MARGINTOP);
}

void UnloadingGameScreen::draw()
{
	Resource::resource->getApp()->clear(sf::Color::White);
	Resource::resource->getApp()->draw(this->mBackgroundSprite);
	this->mTBUnloading.draw();
	this->mGifUnloading->draw();
	Resource::resource->getApp()->display();
}	
