#include "EventManager.h"
#include "Game.h"
#include "Option.h"
#include "ToolsMap.h"
#include "ContainerViewManager.h"
#include "FactoryGet.h"
#include "UserInterface.h"
#include "WindowMessageInfo.h"
#include "WindowMessageError.h"
#include "WindowMessageWarning.h"
#include "WindowMessageSuccess.h"
#include "WindowChoiceAsk.h"

using namespace sf;


//*************************************************************
// Statics
//*************************************************************
EventManager * EventManager::eventManager;


//*************************************************************
// Constructor - Destructor
//*************************************************************
EventManager::EventManager()
{	
	EventManager::eventManager = this;
	this->resetMouseOverEvent();
}

EventManager::~EventManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::Vector2i EventManager::getMousePositionUiLocal()
{
	return Mouse::getPosition(*Resource::resource->getApp());
}

sf::Vector2i EventManager::getMousePositionUiGlobal()
{
	return Mouse::getPosition();
}

sf::Vector2f EventManager::getMousePositionMapLocal(int p_plane)
{
	return Resource::resource->getApp()->mapPixelToCoords(this->getMousePositionUiLocal(), *Resource::resource->getViewMap(p_plane));
}

sf::Vector2f EventManager::getMousePositionMapGlobal(int p_plane)
{
	return Resource::resource->getApp()->mapPixelToCoords(this->getMousePositionUiGlobal(), *Resource::resource->getViewMap(p_plane));
}

bool EventManager::isMouseOverEvent()
{
	return this->mMouseOverEvent;
}

void EventManager::setMouseOverEvent( bool p_raised )
{
	this->mMouseOverEvent = p_raised;
}


//*************************************************************
// Methods
//*************************************************************
void EventManager::handlePlayerAction( sf::Event p_event )
{
	// Zoom / dezoom
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && p_event.type == sf::Event::MouseWheelMoved)
	{
		int delta = p_event.mouseWheel.delta;
		bool isUp = delta > 0;
		delta = Tools::getAbsolute(delta);

		while(delta > 0)
		{
			if(isUp)
				Camera::getInstance()->incZoom();
			else
				Camera::getInstance()->decZoom();

			delta--;
		}
	}

	// CharacterShip reload
	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == Option::getInstance()->getAppControl(OPTIONKEY_CONTROL_RELOAD))
		Game::game->getShipPiloted()->reload();

	// Drag'n'drop
	if(p_event.type == sf::Event::MouseButtonReleased && p_event.mouseButton.button == sf::Mouse::Button::Left)
		ContainerViewManager::getInstance()->releaseDrag();

	// Unselect selected object
	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == Option::getInstance()->getAppControl(OPTIONKEY_CONTROL_UNSELECT))
		Game::game->getMap()->getMapObjectSelector()->unselect();
}

void EventManager::handlePlayerActionPre()
{
}

void EventManager::handlePlayerActionPost()
{
	// CharacterShip fire
	MapObject* selected = Game::game->getMap()->getMapObjectSelector()->getSelectedMapObject();
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && ToolsMap::isEntity(selected))
		Game::game->getShipPiloted()->fire((Entity*)selected, Game::game->getShipPiloted());
}

void EventManager::raiseMouseOverEvent()
{
	this->setMouseOverEvent(true);
}

void EventManager::resetMouseOverEvent()
{
	this->setMouseOverEvent(false);
}

void EventManager::reset()
{
	this->resetMouseOverEvent();
}
