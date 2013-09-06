#include "EventManager.h"
#include "Game.h"
#include "Option.h"
#include "ToolsMap.h"
#include "ContainerStackViewManager.h"
#include "FactoryGet.h"
#include "UserInterface.h"
#include "WindowInfo.h"
#include "WindowError.h"
#include "WindowWarning.h"

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
				Camera::camera->incZoom();
			else
				Camera::camera->decZoom();

			delta--;
		}
	}


	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::Q)
		UserInterface::mUserInterface->addWindowPopup(new WindowInfo("INFO", "There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which don't look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators on the Internet tend to repeat predefined chunks as necessary, making this the first true generator on the Internet. It uses a dictionary of over 200 Latin words, combined with a handful of model sentence structures, to generate Lorem Ipsum which looks reasonable. The generated Lorem Ipsum is therefore always free from repetition, injected humour, or non-characteristic words etc."));

	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::S)
		UserInterface::mUserInterface->addWindowPopup(new WindowWarning("WARNING", "Azy fait pas ieche"));

	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::D)
		UserInterface::mUserInterface->addWindowPopup(new WindowError("ERROR", "Manouche !"));


	// CharacterShip reload
	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == Option::option->getAppControl(OPTION_APP_CONTROL_RELOAD_KEY))
		Game::game->getCharacterShip()->reload();

	// Drag'n'drop
	if(p_event.type == sf::Event::MouseButtonReleased && p_event.mouseButton.button == sf::Mouse::Button::Left)
		ContainerStackViewManager::getInstance()->releaseDrag();

	// Unselect selected object
	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == Option::option->getAppControl(OPTION_APP_CONTROL_UNSELECT_KEY))
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
		Game::game->getCharacterShip()->fire((Entity*)selected, Game::game->getCharacterShip());
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
