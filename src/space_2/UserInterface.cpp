#include "UserInterface.h"
#include "Game.h"
#include "ContainerStackViewManager.h"


//*************************************************************
// Define
//*************************************************************
#define XPBAR_CHARACTER_WIDTH				INTERFACEBOTTOM_WIDTH	
#define XPBAR_CHARACTER_HEIGHT				10
#define INTERFACEBOTTOM_WEAPON_X			12
#define INTERFACEBOTTOM_WEAPON_Y			12
#define INTERFACEBOTTOM_WEAPON_OFFSETX		9


//*************************************************************
// Init static
//*************************************************************
UserInterface * UserInterface::mUserInterface;


//*************************************************************
// Constructor - Destructor
//*************************************************************
UserInterface::UserInterface(void)
{
	this->mUserInterface = this;

	// Window statics
	this->mWindowShipSmall = new WindowShipSmall();
	this->mWindowSelectedCharacterShip = new WindowSelectedCharacterShip(NULL);
	this->mWindowsSelectedNpcShip = new WindowSelectedNpcShip(NULL);
	this->mWindowsSelectedWreck = new WindowSelectedWreck(NULL);
	this->mWindowSelectedWreckMini = new WindowSelectedWreckMini(NULL);
	this->mWindowSelectedEntity = new WindowSelectedEntity(NULL);
	this->mWindowSelected = NULL;

	// Window dynamics
	this->mWindowCharacter	= new WindowCharacter();
	this->mWindowCargo = new WindowCargo();
	this->mWindowCargoLoot = new WindowCargoLoot();
	this->mWindowMap = new WindowMap();
	this->mWindowJukebox = new WindowJukebox();

	this->mWindowDynamics.push_back(this->mWindowCharacter);
	this->mWindowDynamics.push_back(this->mWindowCargo);
	this->mWindowDynamics.push_back(this->mWindowCargoLoot);
	this->mWindowDynamics.push_back(this->mWindowMap);
	this->mWindowDynamics.push_back(this->mWindowJukebox);

	// Other stuffs
	this->mXpBarCharacter.setSize(XPBAR_CHARACTER_WIDTH - this->mXpBarCharacter.getBorderSize() * 2, XPBAR_CHARACTER_HEIGHT);
	this->mInterfaceBottom.setTexture(*Resource::resource->getTexture(IMG_INTERFACE_BOTTOM));

	// Update
	this->updatePosition();
}

UserInterface::~UserInterface(void)
{
	delete this->mWindowShipSmall;
	delete this->mWindowSelectedCharacterShip;
	delete this->mWindowsSelectedNpcShip;
	delete this->mWindowsSelectedWreck;
	delete this->mWindowSelectedWreckMini;
	delete this->mWindowSelectedEntity;

	delete this->mWindowCharacter;
	delete this->mWindowCargo;
	delete this->mWindowCargoLoot;
	delete this->mWindowMap;
	delete this->mWindowJukebox;
}


//*************************************************************
// Getters - Setters
//*************************************************************
WindowCharacter* UserInterface::getWindowCharacter()
{
	return this->mWindowCharacter;
}

WindowJukebox* UserInterface::getWindowJukebox()
{
	return this->mWindowJukebox;
}

WindowShipSmall* UserInterface::getWindowShipSmall()
{
	return this->mWindowShipSmall;
}

WindowSelectedNpcShip* UserInterface::getWindowSelectedNpcShip()
{
	return this->mWindowsSelectedNpcShip;
}

WindowSelectedCharacterShip* UserInterface::getWindowSelectedCharacterShip()
{
	return this->mWindowSelectedCharacterShip;
}

WindowSelectedWreck* UserInterface::getWindowSelectedWreck()
{
	return this->mWindowsSelectedWreck;
}

WindowSelectedWreckMini* UserInterface::getWindowSelectedWreckMini()
{
	return this->mWindowSelectedWreckMini;
}

WindowSelectedEntity* UserInterface::getWindowSelectedEntity()
{
	return this->mWindowSelectedEntity;
}

WindowSelected* UserInterface::getWindowSelected()
{
	return this->mWindowSelected;
}

WindowCargo* UserInterface::getWindowCargo()
{
	return this->mWindowCargo;
}

WindowCargoLoot* UserInterface::getWindowCargoLoot()
{
	return this->mWindowCargoLoot;
}

WindowMap* UserInterface::getWindowMap()
{
	return this->mWindowMap;
}

void UserInterface::setWindowSelected( WindowSelected* p_window )
{
	if(this->mWindowSelected != NULL)
		this->mWindowSelected->setOpen(false);

	this->mWindowSelected = p_window;

	if(this->mWindowSelected != NULL)
		this->mWindowSelected->setOpen(true);
}

ExperienceBar* UserInterface::getXpBarCharacter()
{
	return &this->mXpBarCharacter;
}

sf::Vector2i UserInterface::getInterfaceBottom()
{
	return sf::Vector2i(this->mInterfaceBottom.getPosition().x, this->mInterfaceBottom.getPosition().y);
}


//*************************************************************
// Method
//*************************************************************
void UserInterface::handleScreenAppResized()
{
	this->updatePosition();
}

void UserInterface::update(sf::Event p_event)
{
	// Window dynamics
	for(int i = 0; i < this->mWindowDynamics.size(); i++)
		this->mWindowDynamics[i]->update(p_event);
	this->updateWindowDynamics();

	// Window statics
	this->mWindowShipSmall->update(p_event);
	if(this->mWindowSelected != NULL)
		this->mWindowSelected->update(p_event);

	// Update others
	this->mMenuQuick.update(p_event);
	this->mXpBarCharacter.update(p_event);
	for(int i = 0; i < this->mWeaponViews.size(); i++)
		this->mWeaponViews[i]->update(p_event);
}

void UserInterface::update()
{
	// Window dynamics
	for(int i = 0; i < this->mWindowDynamics.size(); i++)
		this->mWindowDynamics[i]->update();

	// Window statics
	this->mWindowShipSmall->update();
	if(this->mWindowSelected != NULL)
		this->mWindowSelected->update();
	
	// Update others
	this->mMenuQuick.update();
	this->mXpBarCharacter.update();
	for(int i = 0; i < this->mWeaponViews.size(); i++)
		this->mWeaponViews[i]->update();
}

void UserInterface::draw()
{
	// Draw others
	Resource::resource->getApp()->draw(this->mInterfaceBottom);
	this->mMenuQuick.draw();
	this->mXpBarCharacter.draw();
	for(int i = 0; i < this->mWeaponViews.size(); i++)
		this->mWeaponViews[i]->draw();

	// Draw window statics
	this->mWindowShipSmall->draw();
	if(this->mWindowSelected != NULL)
		this->mWindowSelected->draw();

	// Draw window dynamics
	for(int i = this->mWindowDynamics.size() - 1; i >= 0; i--)
		this->mWindowDynamics[i]->draw();

	// Draw dragged item (if exist)
	ContainerStackViewManager::getInstance()->draw();
}

void UserInterface::notifyWeaponViewChanged()
{
	// Clear 
	for(int i = 0; i < this->mWeaponViews.size(); i++)
		delete this->mWeaponViews[i];
	this->mWeaponViews.clear();

	// Add new weapon
	for(int i = 0; i < Game::game->getCharacterShip()->getWeaponSlot(); i++)
		this->mWeaponViews.push_back(new WeaponView(Game::game->getCharacterShip()->getWeapon(i), 0, 0));

	// Update
	this->updateWeaponPosition();
}

void UserInterface::updatePosition()
{
	// Update interfaceBottom
	this->mInterfaceBottom.setPosition(	Resource::resource->getViewUi()->getSize().x / 2 - INTERFACEBOTTOM_WIDTH / 2, 
										Resource::resource->getViewUi()->getSize().y - INTERFACEBOTTOM_HEIGHT);

	// Update weaponView
	this->updateWeaponPosition();

	// Update xp bar
	this->mXpBarCharacter.setPosition(	this->mInterfaceBottom.getPosition().x + this->mXpBarCharacter.getBorderSize(), 
										this->mInterfaceBottom.getPosition().y - this->mXpBarCharacter.getHeight() - this->mXpBarCharacter.getBorderSize());

	// Map
	this->mWindowMap->setY(Resource::resource->getViewUi()->getSize().y - this->mWindowMap->getHeight());

	// Menu Quick
	this->mMenuQuick.updatePosition();
}

void UserInterface::updateWeaponPosition()
{
	for(int i = 0; i < this->mWeaponViews.size(); i++)
	{
		this->mWeaponViews[i]->setX(this->getInterfaceBottom().x + INTERFACEBOTTOM_WEAPON_X + ((WEAPONVIEW_WIDTH + INTERFACEBOTTOM_WEAPON_OFFSETX) * i));
		this->mWeaponViews[i]->setY(this->getInterfaceBottom().y + INTERFACEBOTTOM_WEAPON_Y);
	}
}

void UserInterface::updateWindowDynamics()
{
	for(int i = 0; i < this->mWindowDynamics.size(); i++)
	{
		if(this->mWindowDynamics[i]->hasFocus())
		{
			this->moveWindowDynamicToBegin(i);
			break;
		}
	}
}

void UserInterface::moveWindowDynamicToBegin( int p_index )
{
	Window* tmpWindow = this->mWindowDynamics[p_index];
	this->mWindowDynamics.erase(this->mWindowDynamics.begin() + p_index);
	this->mWindowDynamics.insert(this->mWindowDynamics.begin(), tmpWindow);
}



