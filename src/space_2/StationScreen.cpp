#include "StationScreen.h"
#include "ClockManager.h"
#include "UserInterface.h"
#include "ContainerStackViewManager.h"


//*************************************************************
// Define
//*************************************************************
#define LEFTMENU_BUTTON_WIDTH				150
#define LEFTMENU_BUTTON_HEIGHT				25
#define LEFTMENU_BUTTON_MARGIN				10
#define LEFTMENU_BUTTON_CARGO_MARGINTOP		75
#define LEFTMENU_MARGIN						25
#define LEFTMENU_PADDING					10
#define LEFTMENU_WIDTH						LEFTMENU_PADDING * 2 + LEFTMENU_BUTTON_WIDTH
#define LEFTMENU_BACKCOLOR					sf::Color(128, 128, 128, 200)
#define LEFTMENU_BORDCOLOR					sf::Color(128, 128, 128, 250)
#define LEFTMENU_BORDSIZE					2


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
StationScreen::StationScreen(void)
{
	this->mStation = NULL;

	this->mFieldsetLeftMenu.setBorderSize(LEFTMENU_BORDSIZE);
	this->mFieldsetLeftMenu.setBorderColor(LEFTMENU_BORDCOLOR, true);
	this->mFieldsetLeftMenu.setBackgroundColor(LEFTMENU_BACKCOLOR);
	this->mFieldsetLeftMenu.setDisplayTitle(false);

	this->mButtonHangar.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonHangar.setTitle(Resource::resource->getBundle()->getString("hangar"));

	this->mButtonMarket.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonMarket.setTitle(Resource::resource->getBundle()->getString("market"));

	this->mButtonCraft.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonCraft.setTitle(Resource::resource->getBundle()->getString("craft"));
	
	this->mButtonShipCargo.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonShipCargo.setTitle(Resource::resource->getBundle()->getString("shipCargo"));

	this->mButtonUndock.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
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
void StationScreen::launchBegin()
{
	UserInterface::mUserInterface->getWindowStationShipCargo()->getContainerView()->notifyContainerableChanged();
}

void StationScreen::launchEnd()
{
	UserInterface::mUserInterface->getWindowCargo()->getContainerView()->notifyContainerableChanged();
}

void StationScreen::launch( Station* p_station )
{
	this->launchBegin();
	this->notifyAppSizeChanged();
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
	this->launchEnd();
}

void StationScreen::update()
{
	// Update Clock 
	ClockManager::update();

	// Update windows
	UserInterface::mUserInterface->updateWindowDynamicsStation();
}

void StationScreen::updatePosition()
{
	this->mBackground.setPosition(0, 0);
	this->mFieldsetLeftMenu.setPosition(LEFTMENU_MARGIN, LEFTMENU_MARGIN);
	
	this->mButtonHangar.setPosition(this->mFieldsetLeftMenu.getLeftX() + LEFTMENU_PADDING, this->mFieldsetLeftMenu.getTopY() + LEFTMENU_PADDING);
	this->mButtonMarket.setPosition(this->mButtonHangar.getLeftX(), this->mButtonHangar.getBottomY() + LEFTMENU_BUTTON_MARGIN);
	this->mButtonCraft.setPosition(this->mButtonMarket.getLeftX(), this->mButtonMarket.getBottomY() + LEFTMENU_BUTTON_MARGIN);
	this->mButtonShipCargo.setPosition(this->mButtonCraft.getLeftX(), this->mButtonCraft.getBottomY() + LEFTMENU_BUTTON_CARGO_MARGINTOP);
	
	this->mButtonUndock.setPosition(this->mFieldsetLeftMenu.getLeftX() + LEFTMENU_BUTTON_MARGIN, this->mFieldsetLeftMenu.getBottomY() - LEFTMENU_BUTTON_MARGIN - this->mButtonUndock.getHeight());
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
		ContainerStackViewManager::getInstance()->releaseDrag();

	// Update windows
	UserInterface::mUserInterface->updateWindowDynamicsStation(p_event);

	// Update button
	this->mButtonHangar.update(p_event);
	this->mButtonMarket.update(p_event);
	this->mButtonCraft.update(p_event);

	this->mButtonShipCargo.update(p_event);
	if(this->mButtonShipCargo.isClicked())
		UserInterface::mUserInterface->getWindowStationShipCargo()->setOpen(!UserInterface::mUserInterface->getWindowStationShipCargo()->isOpen());

	this->mButtonUndock.update(p_event);
	if(this->mButtonUndock.isClicked())
		this->setStation(NULL);
}

void StationScreen::draw()
{
	Resource::resource->getApp()->draw(this->mBackground);
	this->mFieldsetLeftMenu.draw();
	this->mButtonHangar.draw();
	this->mButtonMarket.draw();
	this->mButtonCraft.draw();
	this->mButtonShipCargo.draw();
	this->mButtonUndock.draw();

	UserInterface::mUserInterface->drawWindowDynamicsStation();
	ContainerStackViewManager::getInstance()->draw();
}

void StationScreen::notifyAppSizeChanged()
{
	this->updatePosition();
	this->updateBackgroundScale();

	this->mFieldsetLeftMenu.setSize(LEFTMENU_WIDTH, Resource::resource->getViewUi()->getSize().y - LEFTMENU_MARGIN * 2);
}

void StationScreen::notifyStationChanged()
{
	if(this->getStation() != NULL)
	{
		this->mBackground.setTexture(*Resource::resource->getTexture(this->getStation()->getModel()->getScreenSprite()));
		this->updateBackgroundScale();
	}
}




