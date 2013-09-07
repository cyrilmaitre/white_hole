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
		UserInterface::mUserInterface->addWindowPopup(new WindowInfo("INFO", "Plop Il a été au XVIe siècle rendu célèbre par Michel de Montaigne ; dans ses Essais, il aborde de nombreux sujets d'étude du point de vue strictement personnel. On a souvent fait remarquer qu'il accordait une telle importance à cet angle d'approche qu'il y décrit par le détail ses propres sensations, perceptions et, parfois, ses maladies. Mais ce mode de travail lui permet de fonder une réflexion philosophique féconde. Il lance ce genre qui inspirera le philosophe et homme politique anglais Francis Bacon des Essais de morale et de politique (1597)."));

	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::S)
		UserInterface::mUserInterface->addWindowPopup(new WindowWarning("WARNING", "Contrairement à l’étude, l’essai peut être polémique ou partisan. C’est un texte littéraire qui se prête bien à la réflexion philosophique, mais aussi à d'autres domaines : essais historiques, essais scientifiques, essais politiques, etc."));

	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::D)
		UserInterface::mUserInterface->addWindowPopup(new WindowError("ERROR", "une expérience, une naissance, en philosophie : une phénoménologie (conscience au monde individuelle qui vise à rejoindre un savoir plus vaste)"));


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
