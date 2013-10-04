#include "Game.h"
#include "RunningStats.h"
#include "ParticleManager.h"
#include "AnimationManager.h"
#include "ImageGIFFactory.h"
#include "AutoManager.h"
#include "NetworkJobManager.h"
#include "WreckManager.h"
#include "Juckebox.h"
#include "ClockManager.h"
#include "EntityManager.h"
#include "PopupManager.h"
#include "CharacterUpdate.h"

using namespace sf;


//*************************************************************
// Implementation static
//*************************************************************
Game * Game::game = NULL;


//*************************************************************
// Constructor - Destructor
//*************************************************************
Game::Game(void)
{
	// Init
	Game::game = this;
	this->mMap = NULL;
	this->mCamera = NULL;
	this->mUserInterface = NULL;
	this->mCharacter = NULL;

	this->mThreadInit = NULL;
	this->mThreadUninit = NULL;
}

Game::~Game(void)
{
	if(this->mThreadInit != NULL)
		delete this->mThreadInit;

	if(this->mThreadUninit != NULL)
		delete this->mThreadUninit;
}


//*************************************************************
// Getters - Setters
//*************************************************************
Map* Game::getMap()
{
	return this->mMap;
}

UserInterface* Game::getUserInterface()
{
	return this->mUserInterface;
}

Character* Game::getCharacter()
{
	return this->mCharacter;
}

CharacterShip* Game::getShipPiloted()
{
	if(this->mCharacter != NULL)
		return this->mCharacter->getShipPiloted();
	else 
		return NULL;
}


//*************************************************************
// Getters - Setters
//*************************************************************
void Game::init()
{
	// Init basic
	this->mMap = new Map();
	this->mCamera = new Camera();
	this->mUserInterface = new UserInterface(this->mCharacter);

	// Init
	sf::Vector2i characterShipPosition = MapObject::convertPosition(sf::Vector2i(SECTOR_WIDTH / 2, SECTOR_HEIGHT / 2), SECTOR_PLANE, SHIP_PLANE);

	this->mCharacter->init();
	this->getShipPiloted()->setPosition(characterShipPosition.x, characterShipPosition.y);
	this->getUserInterface()->getXpBarCharacter()->setLevelable(this->mCharacter);
	this->notifyShipPilotedChanged();

	Resource::resource->getJuckebox()->playlistLaunch();
	Resource::resource->updateViewMap();

	// First update
	this->update(this->mEvent);
	this->update();

	// Finish
	this->mScreenLoading.setRunning(false);
}

void Game::uninit()
{
	// Update character before quit
	NetworkJobManager::getInstance()->addJob(new CharacterUpdate(this->getCharacter()));

	// Wait while all network jobs done
	while(NetworkJobManager::getInstance()->hasJob())
	{
		NetworkJobManager::getInstance()->update();
		sf::sleep(sf::milliseconds(100));
	}

	// Delete
	delete this->mMap;
	this->mMap = NULL;

	delete this->mCamera;
	this->mCamera = NULL;

	delete this->mUserInterface;
	this->mUserInterface = NULL;

	// Finish
	this->mScreenUnloading.setRunning(false);
}

void Game::launchInit( Character* p_character )
{
	// Set character
	this->mCharacter = p_character;

	// Launch thread
	if(this->mThreadInit != NULL)
	{
		delete this->mThreadInit;
		this->mThreadInit = NULL;
	}

	this->mThreadInit = new sf::Thread(&Game::init, this);
	this->mThreadInit->launch();

	// Screen loading
	this->mScreenLoading.launch();
}

void Game::launchUninit()
{
	// Launch thread
	if(this->mThreadUninit != NULL)
	{
		delete this->mThreadUninit;
		this->mThreadUninit = NULL;
	}

	this->mThreadUninit = new sf::Thread(&Game::uninit, this);
	this->mThreadUninit->launch();	

	// Screen unloading
	this->mScreenUnloading.launch();
}

void Game::launch(Character* p_character)
{
	this->launchInit(p_character);
	while(Resource::resource->getApp()->isOpen() && Resource::resource->isAppRunning())
	{
		// Update
		EventManager::eventManager->reset();
		if(Resource::resource->getApp()->pollEvent(this->mEvent))
		{
			if( this->mEvent.type == Event::Closed)
				Resource::resource->setAppRunning(false);

			if( this->mEvent.type == Event::Resized)
				Resource::resource->resizeAllView();

			// Update Game when event
			this->update(this->mEvent);
		}
		this->update();

		// Draw
		this->mCamera->draw();
		PopupManager::getInstance()->draw();
		Resource::resource->getApp()->display();		
	}
	this->launchUninit();
}

void Game::update( sf::Event p_event )
{
	// Event Manager
	EventManager::eventManager->handlePlayerAction(p_event);

	// Update UserInterface
	Game::game->getUserInterface()->updateInGame(p_event);

	// Update show Stats
	RunningStats::update(p_event);

	// Update ship
	Game::game->getShipPiloted()->update(p_event);

	// Update Map
	this->getMap()->update(p_event);
}

void Game::update()
{
	// Update ClockManager
	ClockManager::update();

	// Event Manager Pre
	EventManager::eventManager->handlePlayerActionPre();

	// Update Juckbox
	Resource::resource->getJuckebox()->update();

	// Update Animation
	AnimationManager::update();

	// Update character
	this->getCharacter()->update();

	// Update ship
	this->getShipPiloted()->update();

	// Update runningstats
	RunningStats::update();

	// Update particle
	ParticleManager::update();

	// Update Map
	this->getMap()->update();

	// Update AutoManager
	AutoManager::update();

	// Update NetworkJobManager
	NetworkJobManager::getInstance()->update();

	// Update UserInterface
	this->getUserInterface()->updateInGame();

	// Event Manager Post
	EventManager::eventManager->handlePlayerActionPost();
}

void Game::changedShipPiloted( CharacterShip* p_ship )
{
	EntityManager::remove(this->getShipPiloted());
	this->getMap()->getMapObjectSelector()->removeMapObject(this->getShipPiloted());

	this->getCharacter()->setShipPiloted(p_ship);
	this->notifyShipPilotedChanged();
}

void Game::notifyShipPilotedChanged()
{
	this->mUserInterface->notifyWeaponViewChanged();
	this->mUserInterface->getXpBarCharacterShip()->setLevelable(this->getShipPiloted());
	this->mUserInterface->getWindowShipSmall()->setCharacterShip(this->getCharacter()->getShipPiloted());
	this->mUserInterface->getWindowCargo()->getContainerableView()->setContainerable(this->getCharacter()->getShipPiloted());
	this->mUserInterface->getWindowCargoStationShip()->getContainerableView()->setContainerable(this->getCharacter()->getShipPiloted());

	EntityManager::add(this->getShipPiloted());
	this->getMap()->getMapObjectSelector()->addMapObject(this->getShipPiloted());
}


