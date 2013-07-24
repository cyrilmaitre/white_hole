#include "BootScreen.h"

//*************************************************************
// Attributs statics
//*************************************************************
bool BootScreen::isRunning;


//*************************************************************
// Constructor - Destructor
//*************************************************************
BootScreen::BootScreen(sf::RenderWindow *p_myApp)
{
	// Init with param
	this->mApp = p_myApp;

	// Init with default
	BootScreen::isRunning = true;
}

BootScreen::~BootScreen(void)
{
}


//*************************************************************
// Methode
//*************************************************************
void BootScreen::launch()
{
	// Init
	sf::Event myEvent;
	
	this->mImageBackground.loadFromFile(FOLDER_IMAGE_BOOT IMG_BOOT_SCREEN);
	this->mTextureBackground.loadFromImage(this->mImageBackground);
	this->mTextureBackground.setSmooth(false);
	this->mSpriteBackground.setTexture(this->mTextureBackground);
	
	this->update();
	while(BootScreen::isRunning)
	{
		// Event
		while(Resource::resource->getApp()->pollEvent(myEvent))
		{
			if( myEvent.type == sf::Event::Closed)
				Resource::resource->setAppRunning(false);

			if( myEvent.type == sf::Event::Resized)
				Resource::resource->resizeAllView();
		}
		this->update();

		// Draw
		this->draw();
	}
}

void BootScreen::update()
{
	// Update Sprite
	this->mSpriteBackground.setPosition((float)this->mApp->getSize().x / 2 - (float)this->mImageBackground.getSize().x / 2, 
										(float)this->mApp->getSize().y / 2 - (float)this->mImageBackground.getSize().y / 2);
}

void BootScreen::draw()
{
	// Clear
	this->mApp->clear(sf::Color::White);

	// Draw & display
	this->mApp->draw(this->mSpriteBackground);
	this->mApp->display();
}

