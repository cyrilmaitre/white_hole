#include "LoadingGameScreen.h"
#include "ImageGIFFactory.h"


//*************************************************************
// Define
//*************************************************************
#define LOADING_FONTSIZE			32
#define LOADING_MARGINTOP			50
#define GIFLOADING_MARGINTOP		20


//*************************************************************
// Constructor - Destructor
//*************************************************************
LoadingGameScreen::LoadingGameScreen(void)
{
	this->mTBLoading.setText(Resource::resource->getBundle()->getString("loading"));
	this->mTBLoading.setFontSize(LOADING_FONTSIZE);
	this->mGifLoading = ImageGIFFactory::getLoadingBert();
}

LoadingGameScreen::~LoadingGameScreen(void)
{
	delete this->mGifLoading;
}


//*************************************************************
// Methodss
//*************************************************************
double LoadingGameScreen::launch()
{
	this->setRunning(true);
	this->update();
	this->notifyAppSizeChanged();
	while(Resource::resource->isAppRunning())
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
	return 0;
}

void LoadingGameScreen::update()
{
	BaseScreen::update();
	this->mGifLoading->update();
	this->mMarioGame.update();
}

void LoadingGameScreen::update( sf::Event p_event )
{
	this->mMarioGame.update(p_event);
}

void LoadingGameScreen::updatePosition()
{
	BaseScreen::updatePosition();
	this->mTBLoading.setPosition((Resource::resource->getViewUi()->getSize().x - this->mTBLoading.getWidth()) / 2, (Resource::resource->getViewUi()->getSize().y - this->mTBLoading.getHeight()) / 2 - LOADING_MARGINTOP);
	this->mGifLoading->setPosition((Resource::resource->getViewUi()->getSize().x - this->mGifLoading->getWidth()) / 2, this->mTBLoading.getBottomY() + GIFLOADING_MARGINTOP);
	this->mMarioGame.setPosition(0, Resource::resource->getViewUi()->getSize().y - this->mMarioGame.getHeight());
}

void LoadingGameScreen::draw()
{
	Resource::resource->getApp()->clear(sf::Color::White);
	Resource::resource->getApp()->draw(this->mBackgroundSprite);
	this->mTBLoading.draw();
	this->mGifLoading->draw();
	this->mMarioGame.draw();
	Resource::resource->getApp()->display();
}

void LoadingGameScreen::notifyAppSizeChanged()
{
	BaseScreen::notifyAppSizeChanged();
	this->mMarioGame.setWidth(Resource::resource->getViewUi()->getSize().x);
	this->updatePosition();
}
