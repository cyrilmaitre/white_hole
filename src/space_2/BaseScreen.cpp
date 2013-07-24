#include "BaseScreen.h"
#include "BackgroundSpaceManager.h"
#include "Option.h"
#include "ClockManager.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define BASESCREEN_GAME_VERSION_OFFSETX		10
#define BASESCREEN_GAME_VERSION_OFFSETY		10
#define BASESCREEN_OVERLAY_COLOR			sf::Color(128, 128, 128, 75)
#define BORDER_BOTTOM_COLOR					sf::Color(128, 128, 128, 125)
#define BORDER_BOTTOM_HEIGHT				2


//*************************************************************
// Constructor - Destructor
//*************************************************************
BaseScreen::BaseScreen(void)
{
	this->mRunning = true;
	this->mScreenView = new View();
	this->mScreenView->setWidth(Resource::resource->getViewUi()->getSize().x);
	this->mScreenView->setHeight(Resource::resource->getViewUi()->getSize().y);

	this->mGameVersion.setFontColor(sf::Color::White);
	this->mGameVersion.setFontSize(ManagerConfig::FontSize::Tiny);
	this->mGameVersion.setText(Resource::resource->getBundle()->getString("version") + " " + OPTION_VERSION_VALUE);
	this->mGameVersion.setView(this->mScreenView);

	this->mOverlayBottom.setFillColor(BASESCREEN_OVERLAY_COLOR);
	this->mBorderBottom.setFillColor(BORDER_BOTTOM_COLOR);
	this->mBackgroundSprite.setPosition(0, 0);

	this->notifyAppSizeChanged();
}

BaseScreen::~BaseScreen(void)
{
	if(this->mScreenView != NULL)
		delete this->mScreenView;
}


//*************************************************************
// Methods
//*************************************************************
void BaseScreen::draw()
{
	Resource::resource->getApp()->clear(sf::Color::White);
	Resource::resource->getApp()->draw(this->mBackgroundSprite);
	Resource::resource->getApp()->draw(this->mOverlayBottom);
	Resource::resource->getApp()->draw(this->mBorderBottom);
	this->mGameVersion.draw();
}

void BaseScreen::update()
{
	EventManager::eventManager->reset();
	ClockManager::update();
}

void BaseScreen::updatePosition()
{
	this->mOverlayBottom.setPosition(sf::Vector2f(0, Resource::resource->getViewUi()->getSize().y - BASESCREEN_OVERLAY_HEIGHT));
	this->mBorderBottom.setPosition(sf::Vector2f(0, Resource::resource->getViewUi()->getSize().y - BASESCREEN_OVERLAY_HEIGHT - BORDER_BOTTOM_HEIGHT));

	this->mGameVersion.setX(BASESCREEN_GAME_VERSION_OFFSETX);
	this->mGameVersion.setY((int)Resource::resource->getViewUi()->getSize().y - this->mGameVersion.getHeight() - BASESCREEN_GAME_VERSION_OFFSETY);
}

void BaseScreen::notifyAppSizeChanged()
{
	this->mBackgroundSprite.setTexture(BackgroundSpaceManager::getInstance()->getBackgroundSpaceScreen()->getBackgroundTexture()->getTexture(), true);

	this->mOverlayBottom.setSize(sf::Vector2f(Resource::resource->getViewUi()->getSize().x, BASESCREEN_OVERLAY_HEIGHT));
	this->mBorderBottom.setSize(sf::Vector2f(Resource::resource->getViewUi()->getSize().x, BORDER_BOTTOM_HEIGHT));

	this->updatePosition();
}

void BaseScreen::hideScreen()
{
	this->mScreenView->setVisible(false);
}

void BaseScreen::showScreen()
{
	this->mScreenView->setVisible(true);
	this->notifyAppSizeChanged();
}
