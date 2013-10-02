#include "UserInterface.h"
#include "Game.h"
#include "ContainerStackViewManager.h"
#include "CharacterBank.h"


//*************************************************************
// Define
//*************************************************************
#define XPBAR_CHARACTER_WIDTH				INTERFACEBOTTOM_WIDTH	
#define XPBAR_CHARACTER_HEIGHT				10
#define INTERFACEBOTTOM_WEAPON_X			12
#define INTERFACEBOTTOM_WEAPON_Y			12
#define INTERFACEBOTTOM_WEAPON_OFFSETX		9
#define DASHBOARD_X							455
#define DASHBOARD_Y							108
#define DASHBOARD_WIDTH						310
#define DASHBOARD_HEIGHT					52
#define DASHBOARD_BACKGROUNDCOLOR			sf::Color(39, 39, 39)
#define DASHBOARD_BORDERCOLOR				sf::Color(24, 24, 24)
#define DASHBOARD_BORDERSIZE				2
#define DASHBOARD_PADDING					5
#define DASHBOARD_FONTSIZE					13
#define DASHBOARD_LABELMARGINRIGHT			5
#define DASHBOARD_LABELMARGINTOP			2
#define DASHBOARD_UPDATETIME_TICK				1		// Sec
#define TIMEPLAYED_MIN						1		// Sec
#define TIMEPLAYED_HOUR						60		// Sec
#define TIMEPLAYED_DAY						1440


//*************************************************************
// Init static
//*************************************************************
UserInterface * UserInterface::mUserInterface;


//*************************************************************
// Constructor - Destructor
//*************************************************************
UserInterface::UserInterface( Character* p_character )
{
	this->mUserInterface = this;
	this->mStationScreen = NULL;
	this->mCharacter = NULL;
	this->setCharacter(p_character);

	// Window statics
	this->mWindowShipSmall = new WindowShipSmall();
	this->mWindowSelectedCharacterShip = new WindowSelectedCharacterShip(NULL);
	this->mWindowsSelectedNpcShip = new WindowSelectedNpcShip(NULL);
	this->mWindowsSelectedWreck = new WindowSelectedWreck(NULL);
	this->mWindowSelectedWreckMini = new WindowSelectedWreckMini(NULL);
	this->mWindowSelectedStation = new WindowSelectedStation(NULL);
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

	this->mWindowCargoStationShip = new WindowCargoStation(Resource::resource->getBundle()->getString("shipCargo"));

	this->mWindowDynamicsStation.push_back(this->mWindowCargoStationShip);
	
	// Other stuffs
	this->mStationScreen = new StationScreen(this->getCharacter());
	this->mXpBarCharacter.setSize(XPBAR_CHARACTER_WIDTH - this->mXpBarCharacter.getBorderSize() * 2, XPBAR_CHARACTER_HEIGHT);
	this->mXpBarCharacterShip.setSize(XPBAR_CHARACTER_WIDTH - this->mXpBarCharacter.getBorderSize() * 2, XPBAR_CHARACTER_HEIGHT);
	this->mXpBarCharacterShip.setType(ExperienceBar::ExperienceBarType::TypeCharacterShip);
	this->mInterfaceBottom.setTexture(*Resource::resource->getTexture(IMG_INTERFACE_BOTTOM));

	this->mDashboard.setSize(DASHBOARD_WIDTH, DASHBOARD_HEIGHT);
	this->mDashboard.setBackgroundColor(DASHBOARD_BACKGROUNDCOLOR, true);
	this->mDashboard.setBorderColor(DASHBOARD_BORDERCOLOR, true);
	this->mDashboard.setBorderSize(DASHBOARD_BORDERSIZE, true);
	this->mDashboard.setPadding(DASHBOARD_PADDING);
	this->mDashboard.setDisplayTitle(false);

	this->mDashboardDayLabel.setFontSize(DASHBOARD_FONTSIZE);
	this->mDashboardDay.setFontSize(DASHBOARD_FONTSIZE);
	this->mDashboardTimeLabel.setFontSize(DASHBOARD_FONTSIZE);
	this->mDashboardTime.setFontSize(DASHBOARD_FONTSIZE);
	this->mDashboardPositionLabel.setFontSize(DASHBOARD_FONTSIZE);
	this->mDashboardPosition.setFontSize(DASHBOARD_FONTSIZE);

	this->mDashboardDayLabel.setText(Resource::resource->getBundle()->getString("dashboardDay"));
	this->mDashboardTimeLabel.setText(Resource::resource->getBundle()->getString("dashboardTime"));
	this->mDashboardPositionLabel.setText(Resource::resource->getBundle()->getString("dashboardPosition"));

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
	delete this->mWindowSelectedStation;
	delete this->mWindowSelectedEntity;

	delete this->mWindowCharacter;
	delete this->mWindowCargo;
	delete this->mWindowCargoLoot;
	delete this->mWindowMap;
	delete this->mWindowJukebox;

	delete this->mWindowCargoStationShip;
	for(int i = 0; i < this->mWindowCargoStationBanks.size(); i++)
	{
		if(this->mWindowCargoStationBanks[i] != NULL)
			delete this->mWindowCargoStationBanks[i];
	}

	delete this->mStationScreen;
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* UserInterface::getCharacter()
{
	return this->mCharacter;
}

void UserInterface::setCharacter( Character* p_character )
{
	if(this->mCharacter != p_character)
	{
		this->mCharacter = p_character;
		this->notifyCharacterChanged();
	}
}

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

WindowSelectedStation* UserInterface::getWindowSelectedStation()
{
	return this->mWindowSelectedStation;
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

WindowCargoStation* UserInterface::getWindowCargoStationShip()
{
	return this->mWindowCargoStationShip;
}

int UserInterface::getWindowCargoStationBankCount()
{
	return this->mWindowCargoStationBanks.size();
}

WindowCargoStation* UserInterface::getWindowCargoStationBank( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->getWindowCargoStationBankCount())
		p_index = this->getWindowCargoStationBankCount() - 1;

	return this->mWindowCargoStationBanks[p_index];
}

void UserInterface::setWindowSelected( WindowSelected* p_window )
{
	if(this->mWindowSelected != NULL)
		this->mWindowSelected->setOpen(false);

	this->mWindowSelected = p_window;

	if(this->mWindowSelected != NULL)
		this->mWindowSelected->setOpen(true);
}

StationScreen* UserInterface::getStationScreen()
{
	return this->mStationScreen;
}

ExperienceBar* UserInterface::getXpBarCharacter()
{
	return &this->mXpBarCharacter;
}

ExperienceBar* UserInterface::getXpBarCharacterShip()
{
	return &this->mXpBarCharacterShip;
}

sf::Vector2i UserInterface::getInterfaceBottom()
{
	return sf::Vector2i(this->mInterfaceBottom.getPosition().x, this->mInterfaceBottom.getPosition().y);
}


//*************************************************************
// Method
//*************************************************************
void UserInterface::addWindowPopup( WindowPopup* p_window )
{
	this->mWindowPopups.insert(this->mWindowPopups.begin(), p_window);
	this->mWindowDynamics.insert(this->mWindowDynamics.begin(), p_window);
	this->mWindowDynamicsStation.insert(this->mWindowDynamicsStation.begin(), p_window);
}

void UserInterface::removeWindowPopup( WindowPopup* p_window )
{
	// Remove from dynamics 
	for(int i = 0; i < this->mWindowDynamics.size(); i++)
	{
		if(this->mWindowDynamics[i]->getIdObject() == p_window->getIdObject())
			this->mWindowDynamics.erase(this->mWindowDynamics.begin() + i);
	}

	for(int i = 0; i < this->mWindowDynamicsStation.size(); i++)
	{
		if(this->mWindowDynamicsStation[i]->getIdObject() == p_window->getIdObject())
			this->mWindowDynamicsStation.erase(this->mWindowDynamicsStation.begin() + i);
	}

	// Remove from pop up
	for(int i = 0; i < this->mWindowPopups.size(); i++)
	{
		if(this->mWindowPopups[i]->getIdObject() == p_window->getIdObject())
		{
			delete this->mWindowPopups[i];
			this->mWindowPopups.erase(this->mWindowPopups.begin() + i);
		}
	}
}

void UserInterface::handleScreenAppResized()
{
	this->updatePosition();
}

void UserInterface::update(sf::Event p_event)
{
	// Window dynamics
	this->updateWindowDynamics(p_event);

	// Window statics
	this->updateWindowStatics(p_event);

	// Update others
	this->mMenuQuick.update(p_event);
	this->mXpBarCharacter.update(p_event);
	this->mXpBarCharacterShip.update(p_event);
	for(int i = 0; i < this->mWeaponViews.size(); i++)
		this->mWeaponViews[i]->update(p_event);
}

void UserInterface::updateWindowStatics( sf::Event p_event )
{
	this->mWindowShipSmall->update(p_event);
	if(this->mWindowSelected != NULL)
		this->mWindowSelected->update(p_event);
}

void UserInterface::updateWindowDynamics(sf::Event p_event)
{
	for(int i = 0; i < this->mWindowDynamics.size(); i++)
		this->mWindowDynamics[i]->update(p_event);

	for(int i = 0; i < this->mWindowDynamics.size(); i++)
	{
		if(this->mWindowDynamics[i]->hasFocus())
		{
			this->moveWindowDynamicToBegin(i);
			break;
		}
	}
}

void UserInterface::updateWindowDynamicsStation( sf::Event p_event )
{
	for(int i = 0; i < this->mWindowDynamicsStation.size(); i++)
		this->mWindowDynamicsStation[i]->update(p_event);

	for(int i = 0; i < this->mWindowDynamicsStation.size(); i++)
	{
		if(this->mWindowDynamicsStation[i]->hasFocus())
		{
			this->moveWindowDynamicStationToBegin(i);
			break;
		}
	}
}

void UserInterface::update()
{
	// Window dynamics
	this->updateWindowDynamics();

	// Window statics
	this->updateWindowStatics();
	
	// Update others
	this->mMenuQuick.update();
	this->mXpBarCharacter.update();
	this->mXpBarCharacterShip.update();
	for(int i = 0; i < this->mWeaponViews.size(); i++)
		this->mWeaponViews[i]->update();
	this->updateDashboard();
}

void UserInterface::updateDashboard()
{
	// Update day & time
	if(this->mDashboardClock.getElapsedTimeAsSeconds() > DASHBOARD_UPDATETIME_TICK)
	{
		this->mDashboardClock.restart();
		long timePlayed = this->getCharacter()->getTimePlayedReal();
		long dayPlayed = timePlayed / TIMEPLAYED_DAY;
		timePlayed = timePlayed % TIMEPLAYED_DAY;
		long hourPlayed = timePlayed / TIMEPLAYED_HOUR;
		long minPlayed = timePlayed % TIMEPLAYED_HOUR;

		this->mDashboardDay.setText(Tools::formatNumber(dayPlayed));
		this->mDashboardTime.setText(Tools::formatHour(hourPlayed, minPlayed));
	}

	// Update position
	Sector* currentSector = Game::game->getMap()->getCurrentSector();
	this->mDashboardPosition.setFontColor(currentSector->getDangerLevel()->getDangerLevelColor());
	this->mDashboardPosition.setText("[" + Tools::formatNumber((int)Game::game->getShipPiloted()->getX(SECTOR_PLANE)) + ";" + Tools::formatNumber((int)Game::game->getShipPiloted()->getY(SECTOR_PLANE)) + "]");
}

void UserInterface::updateWindowPopups()
{
	for(int i = 0; i < this->mWindowPopups.size(); i++)
	{
		if(!this->mWindowPopups[i]->isOpen())
		{
			this->removeWindowPopup(this->mWindowPopups[i]);
			i--;
		}
	}
}

void UserInterface::updateWindowStatics()
{
	this->mWindowShipSmall->update();
	if(this->mWindowSelected != NULL)
		this->mWindowSelected->update();
}

void UserInterface::updateWindowDynamics()
{
	// Dynamics
	for(int i = 0; i < this->mWindowDynamics.size(); i++)
		this->mWindowDynamics[i]->update();

	// Popups
	this->updateWindowPopups();
}

void UserInterface::updateWindowDynamicsStation()
{
	// Dynamics
	for(int i = 0; i < this->mWindowDynamicsStation.size(); i++)
		this->mWindowDynamicsStation[i]->update();

	// Popups
	this->updateWindowPopups();
}

void UserInterface::draw()
{
	// Draw others
	Resource::resource->getApp()->draw(this->mInterfaceBottom);
	this->mMenuQuick.draw();
	this->mXpBarCharacter.draw();
	this->mXpBarCharacterShip.draw();
	for(int i = 0; i < this->mWeaponViews.size(); i++)
		this->mWeaponViews[i]->draw();
	this->mDashboard.draw();
	this->mDashboardDayLabel.draw();
	this->mDashboardDay.draw();
	this->mDashboardTimeLabel.draw();
	this->mDashboardTime.draw();
	this->mDashboardPositionLabel.draw();
	this->mDashboardPosition.draw();

	// Draw window statics
	this->drawWindowStatics();
	
	// Draw window dynamics
	this->drawWindowDynamics();

	// Draw dragged item (if exist)
	ContainerStackViewManager::getInstance()->draw();
}

void UserInterface::drawWindowStatics()
{
	this->mWindowShipSmall->draw();
	if(this->mWindowSelected != NULL)
		this->mWindowSelected->draw();
}

void UserInterface::drawWindowDynamics()
{
	for(int i = this->mWindowDynamics.size() - 1; i >= 0; i--)
		this->mWindowDynamics[i]->draw();
}

void UserInterface::drawWindowDynamicsStation()
{
	for(int i = this->mWindowDynamicsStation.size() - 1; i >= 0; i--)
		this->mWindowDynamicsStation[i]->draw();
}

void UserInterface::notifyWeaponViewChanged()
{
	// Clear 
	for(int i = 0; i < this->mWeaponViews.size(); i++)
		delete this->mWeaponViews[i];
	this->mWeaponViews.clear();

	// Add new weapon
	for(int i = 0; i < Game::game->getShipPiloted()->getWeaponsCount(); i++)
		this->mWeaponViews.push_back(new WeaponView(Game::game->getShipPiloted()->getWeapon(i), 0, 0));

	// Update
	this->updateWeaponPosition();
}

void UserInterface::notifyCharacterChanged()
{
	// Update station screen
	if(this->mStationScreen != NULL)
		this->mStationScreen->setCharacter(this->getCharacter());

	// Clear bank
	for(int i = 0; i < this->mWindowCargoStationBanks.size(); i++)
	{
		if(this->mWindowCargoStationBanks[i] != NULL)
			delete this->mWindowCargoStationBanks[i];
	}
	this->mWindowCargoStationBanks.clear();

	if(this->getCharacter() != NULL)
	{
		for(int i = 0; i < this->getCharacter()->getBankCount(); i++)
		{
			CharacterBank* currentBank = this->getCharacter()->getBank(i);
			WindowCargoStation* currentWindowBank = new WindowCargoStation(Resource::resource->getBundle()->getString("bankCargo") + Tools::buildStringWithInt(currentBank->getNumber()));
			currentWindowBank->getContainerView()->setContainerable(currentBank);
			this->mWindowCargoStationBanks.push_back(currentWindowBank);
			this->mWindowDynamicsStation.push_back(currentWindowBank);
		}
	}
}

void UserInterface::updatePosition()
{
	// Update interfaceBottom
	this->mInterfaceBottom.setPosition(	Resource::resource->getViewUi()->getSize().x / 2 - INTERFACEBOTTOM_WIDTH / 2, 
										Resource::resource->getViewUi()->getSize().y - INTERFACEBOTTOM_HEIGHT);

	// Update weaponView
	this->updateWeaponPosition();

	// Update Dashboard
	this->mDashboard.setPosition(this->getInterfaceBottom().x + DASHBOARD_X, this->getInterfaceBottom().y + DASHBOARD_Y);
	this->mDashboardDayLabel.setPosition(this->mDashboard.getContentX(), this->mDashboard.getContentY());
	this->mDashboardDay.setPosition(this->mDashboardDayLabel.getRightX() + DASHBOARD_LABELMARGINRIGHT, this->mDashboardDayLabel.getY());
	this->mDashboardTimeLabel.setPosition(this->mDashboardDayLabel.getX(), this->mDashboardDayLabel.getBottomY() + DASHBOARD_LABELMARGINTOP);
	this->mDashboardTime.setPosition(this->mDashboardTimeLabel.getRightX() + DASHBOARD_LABELMARGINRIGHT, this->mDashboardTimeLabel.getY());
	this->mDashboardPositionLabel.setPosition(this->mDashboardTimeLabel.getX(), this->mDashboardTimeLabel.getBottomY() + DASHBOARD_LABELMARGINTOP);
	this->mDashboardPosition.setPosition(this->mDashboardPositionLabel.getRightX() + DASHBOARD_LABELMARGINRIGHT, this->mDashboardPositionLabel.getY());

	// Update xp bar
	this->mXpBarCharacter.setPosition(	this->mInterfaceBottom.getPosition().x + this->mXpBarCharacter.getBorderSize(), 
										this->mInterfaceBottom.getPosition().y - this->mXpBarCharacter.getHeight() - this->mXpBarCharacter.getBorderSize());
	this->mXpBarCharacterShip.setPosition(this->mXpBarCharacter.getX(), this->mXpBarCharacter.getY() - this->mXpBarCharacterShip.getHeight() - this->mXpBarCharacterShip.getBorderSize() * 2);

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

void UserInterface::moveWindowDynamicToBegin( int p_index )
{
	Window* tmpWindow = this->mWindowDynamics[p_index];
	this->mWindowDynamics.erase(this->mWindowDynamics.begin() + p_index);
	this->mWindowDynamics.insert(this->mWindowDynamics.begin(), tmpWindow);
}

void UserInterface::moveWindowDynamicStationToBegin( int p_index )
{
	Window* tmpWindow = this->mWindowDynamicsStation[p_index];
	this->mWindowDynamicsStation.erase(this->mWindowDynamicsStation.begin() + p_index);
	this->mWindowDynamicsStation.insert(this->mWindowDynamicsStation.begin(), tmpWindow);
}

