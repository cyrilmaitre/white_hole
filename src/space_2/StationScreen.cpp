#include "StationScreen.h"
#include "ClockManager.h"
#include "UserInterface.h"
#include "ContainerViewManager.h"
#include "NetworkJobManager.h"
#include "RunningStats.h"
#include "Jukebox.h"
#include "CharacterBank.h"
#include "Tools.h"
#include "WindowMessageInfo.h"
#include "WindowMessageError.h"
#include "WindowMessageWarning.h"
#include "PopupManager.h"


//*************************************************************
// Define
//*************************************************************
#define LEFTMENU_MARGIN						25
#define RIGHTPANEL_MARGIN					25


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
StationScreen::StationScreen(Character* p_character)
{
	this->mStation = NULL;
	this->mCharacter = NULL;
	this->mLeftMenu = NULL;
	this->mRightPanel = NULL;
	this->mPanelMarket = NULL;

	this->setCharacter(p_character);
	this->mLeftMenu = new StationScreenLeftMenu(p_character, this);
	this->mPanelMarket = new StationScreenMarket(p_character, NULL, this);
	this->mPanelHangar = new StationScreenHangar(p_character, NULL, this);

	this->notifyAppSizeChanged();
}

StationScreen::~StationScreen(void)
{
	if(this->mLeftMenu != NULL)
		delete this->mLeftMenu;

	if(this->mPanelMarket != NULL)
		delete this->mPanelMarket;
}


//*************************************************************
// Getters - Setters
//*************************************************************
int StationScreen::getWidth()
{
	return Resource::resource->getViewUi()->getSize().x;
}

int StationScreen::getHeight()
{
	return Resource::resource->getViewUi()->getSize().y;
}

Character* StationScreen::getCharacter()
{
	return this->mCharacter;
}

void StationScreen::setCharacter( Character* p_character )
{
	if(this->mCharacter != p_character)
	{
		this->mCharacter = p_character;
		this->notifyCharacterChanged();
	}
}

Station* StationScreen::getStation()
{
	return this->mStation;
}

void StationScreen::setStation( Station* p_station )
{
	if(this->mStation != p_station)
	{
		// Undock
		if(this->mStation != NULL)
			this->mStation->undock();

		// Set
		this->mStation = p_station;
		this->notifyStationChanged();
	}
}

StationScreenLeftMenu* StationScreen::getLeftMenu()
{
	return this->mLeftMenu;
}

StationScreenRightPanel* StationScreen::getRightPanel()
{
	return this->mRightPanel;
}

void StationScreen::setRightPanel( StationScreenRightPanel* p_panel )
{
	if(this->mRightPanel != p_panel)
	{
		if(this->mRightPanel != NULL)
			this->mRightPanel->unload();

		this->mRightPanel = p_panel;
		this->notifyRightPanelChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void StationScreen::undock()
{
	this->unloadPanel();
	this->setStation(NULL);
}

void StationScreen::unloadPanel()
{
	this->setRightPanel(NULL);
}

void StationScreen::loadPanelHangar()
{
	this->setRightPanel(this->mPanelHangar);
}

void StationScreen::loadPanelMarket()
{
	this->setRightPanel(this->mPanelMarket);
}

void StationScreen::loadPanelCraft()
{

}

void StationScreen::launchBegin()
{
	// Ship Cargo refresh
	UserInterface::mUserInterface->getWindowCargoStationShip()->notifyContainerableViewChanged();
	UserInterface::mUserInterface->getWindowCargoStationShip()->notifyPositionChanged();
}

void StationScreen::launchEnd()
{
	// Ship Cargo refresh
	UserInterface::mUserInterface->getWindowCargo()->notifyContainerableViewChanged();
	UserInterface::mUserInterface->getWindowCargo()->notifyPositionChanged();
}

void StationScreen::launch( Station* p_station )
{
	this->launchBegin();
	this->setStation(p_station);
	this->notifyAppSizeChanged();
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
		PopupManager::getInstance()->draw();
		Resource::resource->getApp()->display();		
	}
	this->launchEnd();
}

void StationScreen::update()
{
	// Update Clock 
	ClockManager::update();

	// Update Juckbox
	Jukebox::getInstance()->update();

	// Update Network Manager
	NetworkJobManager::getInstance()->update();

	// Update runningstats
	RunningStats::update();

	// Update Windows
	UserInterface::mUserInterface->updateInStation();

	// Update character
	this->getCharacter()->update();

	// Update Left menu
	this->mLeftMenu->update();

	// Update Right panel
	if(this->mRightPanel != NULL)
		this->mRightPanel->update();
}

void StationScreen::updatePosition()
{
	this->mBackground.setPosition(0, 0);
	this->mLeftMenu->setPosition(LEFTMENU_MARGIN, LEFTMENU_MARGIN);
	this->updateRightPanelPositon();
}

void StationScreen::updateRightPanelPositon()
{
	if(this->mRightPanel != NULL)
		this->mRightPanel->setPosition(this->mLeftMenu->getRightX() + LEFTMENU_MARGIN, RIGHTPANEL_MARGIN);
}

void StationScreen::updateRightPanelSize()
{
	if(this->mRightPanel != NULL)
		this->mRightPanel->setSize(this->getWidth() - this->mLeftMenu->getWidth() - 2 * LEFTMENU_MARGIN - RIGHTPANEL_MARGIN, Resource::resource->getViewUi()->getSize().y - RIGHTPANEL_MARGIN * 2);
}

void StationScreen::updateRightPanelCharacter()
{
	if(this->mRightPanel != NULL)
		this->mRightPanel->setCharacter(this->getCharacter());
}

void StationScreen::updateRightPanelStation()
{
	if(this->mRightPanel != NULL)
		this->mRightPanel->setStation(this->getStation());
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
	// Update drag'n'drop stack view
	if(p_event.type == sf::Event::MouseButtonReleased && p_event.mouseButton.button == sf::Mouse::Button::Left)
		ContainerViewManager::getInstance()->releaseDrag();

	// Update show Stats
	RunningStats::update(p_event);

	// Update windows
	UserInterface::mUserInterface->updateInStation(p_event);

	// Update left menu
	this->mLeftMenu->update(p_event);	

	// Update Right Panel
	if(this->mRightPanel != NULL)
		this->mRightPanel->update(p_event);
}

void StationScreen::draw()
{
	Resource::resource->getApp()->draw(this->mBackground);
	this->mLeftMenu->draw();
	if(this->mRightPanel != NULL)
		this->mRightPanel->draw();

	UserInterface::mUserInterface->drawInStation();
	RunningStats::draw();
}

void StationScreen::notifyAppSizeChanged()
{
	this->updatePosition();
	this->updateBackgroundScale();

	this->mLeftMenu->setSize(StationScreenLeftMenu::getWidth(), Resource::resource->getViewUi()->getSize().y - LEFTMENU_MARGIN * 2);
	this->updateRightPanelSize();
}

void StationScreen::notifyStationChanged()
{
	if(this->mStation != NULL)
	{
		// Dock
		this->mStation->dock();

		this->mBackground.setTexture(*Resource::resource->getTexture(this->mStation->getModel()->getScreenSprite()));
		this->updateBackgroundScale();
	}

	this->updateRightPanelStation();
}

void StationScreen::notifyCharacterChanged()
{
	if(this->mLeftMenu != NULL)
		this->mLeftMenu->setCharacter(this->getCharacter());

	this->updateRightPanelCharacter();
}

void StationScreen::notifyRightPanelChanged()
{
	if(this->mRightPanel != NULL)
	{
		this->updateRightPanelPositon();
		this->updateRightPanelSize();
		this->updateRightPanelCharacter();
		this->updateRightPanelStation();
		this->mRightPanel->load();
	}
}


