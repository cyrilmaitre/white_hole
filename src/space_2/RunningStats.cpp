#include "RunningStats.h"
#include "Game.h"
#include "Tools.h"
#include "FactoryGet.h"
#include "AutoManager.h"
#include "NetworkJobManager.h"
#include "ParticleManager.h"
#include "EntityManager.h"
#include "WreckManager.h"
#include "Movable.h"


//*************************************************************
// Init statics
//*************************************************************
mks::Clock RunningStats::mFrameRateClock;
mks::Clock RunningStats::mRunningStatsClock;
float RunningStats::mFrameRate;
bool RunningStats::mShow;
HANDLE RunningStats::mSelf;
int RunningStats::mNumProcessors;
ULARGE_INTEGER RunningStats::mLastUserCPU;
ULARGE_INTEGER RunningStats::mLastSysCPU;
ULARGE_INTEGER RunningStats::mLastCPU;
double RunningStats::mCPUUsage;
int RunningStats::mFrameCount;


//*************************************************************
// Constructor - Destructor
//*************************************************************
RunningStats::RunningStats(void)
{
}

RunningStats::~RunningStats(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool RunningStats::isShow()
{
	return RunningStats::mShow;
}

void RunningStats::setShow( bool p_isShow )
{
	RunningStats::mShow = p_isShow;
}

sf::Vector2f RunningStats::getTextPosition( int line, int column )
{
	int columnOffset = 0;
	if(column == 1)
		columnOffset = 200;
	else if(column == 2)
		columnOffset = 500;
	else if(column == 3)
		columnOffset = 740;
	else if(column == 4)
		columnOffset = 1000;
	else if(column == 5)
		columnOffset = 1200;

	return sf::Vector2f(column + columnOffset + RUNNINGSTATS_BACKGROUND_PADDING, line * RUNNINGSTATS_LINE_OFFSET + RUNNINGSTATS_BACKGROUND_PADDING);
}

float RunningStats::getFrameRate()
{
	float timeElapsed = (float)RunningStats::mFrameRateClock.getElapsedTimeAsMilliseconds();
	RunningStats::mFrameRateClock.restart();
	float frameRate = (float)RunningStats::mFrameCount / (timeElapsed / 1000.f);
	RunningStats::mFrameCount = 0;

	return frameRate;
}

SIZE_T RunningStats::getMemoryUsage()
{
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	
	return pmc.WorkingSetSize;
}

double RunningStats::getCpuUsage()
{
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));

	GetProcessTimes(mSelf, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (sys.QuadPart - mLastSysCPU.QuadPart) + (user.QuadPart - mLastUserCPU.QuadPart);
	percent /= (now.QuadPart - mLastCPU.QuadPart);
	percent /= mNumProcessors;
	mLastCPU = now;
	mLastUserCPU = user;
	mLastSysCPU = sys;

	return percent * 100;
}


//*************************************************************
// Methode
//*************************************************************
void RunningStats::init()
{
	// Init
	RunningStats::mShow = false;
	RunningStats::mFrameCount = 0;

	// Init cpu usage
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	mNumProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&mLastCPU, &ftime, sizeof(FILETIME));

	mSelf = GetCurrentProcess();
	GetProcessTimes(mSelf, &ftime, &ftime, &fsys, &fuser);
	memcpy(&mLastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&mLastUserCPU, &fuser, sizeof(FILETIME));
}

void RunningStats::update()
{
	if(mShow)
	{
		RunningStats::mFrameCount++;

		// Update
		if(RunningStats::mRunningStatsClock.getElapsedTimeAsMilliseconds() > RUNNINGSTATS_UPDATE_FREQUENCY)
		{
			// Update frame rate
			RunningStats::mFrameRate = RunningStats::getFrameRate();

			// Update cpu usage
			RunningStats::mCPUUsage = RunningStats::getCpuUsage();

			// Restart clock
			RunningStats::mRunningStatsClock.restart();
		}
	}
}

void RunningStats::update( sf::Event p_event )
{
	if( p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::F11)
		RunningStats::setShow(!RunningStats::isShow());
}

void RunningStats::draw()
{
	if(mShow)
	{
		// Load informations
		Sector* currentSector = Game::game->getMap()->getCurrentSector();


		// Draw Background
		sf::RectangleShape background;

		background.setFillColor(RUNNINGSTATS_BACKGROUND_COLOR);
		background.setSize(sf::Vector2f(Resource::resource->getViewUi()->getSize().x, RUNNINGSTATS_BACKGROUND_HEIGHT));
		background.setPosition(RUNNINGSTATS_BACKGROUND_POSITION);
		Resource::resource->getApp()->draw(background);

		// Init
		std::stringstream ss;
		sf::Text text;
		text.setFont(*Resource::resource->getFontDefault());
		text.setColor(sf::Color::White);
		text.setCharacterSize(14);

		// Draw Title
		text.setString(sf::String(Resource::resource->getBundle()->getString("runningStatsTitle")));
		text.setPosition(RunningStats::getTextPosition(0, 0));
		Resource::resource->getApp()->draw(text);

		// Draw app's width
		ss	<< Resource::resource->getBundle()->getString("runningStatsAppWidth") 
			<< Tools::getSpaceAfterColon()
			<< Resource::resource->getViewUi()->getSize().x;
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(1, 0));
		Resource::resource->getApp()->draw(text);
		ss.str("");
			
		// Draw app's height
		ss	<< Resource::resource->getBundle()->getString("runningStatsAppHeight") 
			<< Tools::getSpaceAfterColon()
			<< Resource::resource->getViewUi()->getSize().y;
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(2, 0));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw app's frame rate
		ss	<< Resource::resource->getBundle()->getString("runningStatsAppFPS") 
			<< Tools::getSpaceAfterColon()
			<< (int)RunningStats::mFrameRate;
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(3, 0));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw app's memory usage
		ss	<< Resource::resource->getBundle()->getString("runningStatsAppMemoryWorkingset") 
			<< Tools::getSpaceAfterColon()
			<< Tools::formatNumber((int)(RunningStats::getMemoryUsage() / 1000000)) 
			<< " MB";
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(5, 0));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw app's cpu usage
		ss	<< Resource::resource->getBundle()->getString("runningStatsAppCpuUsage") 
			<< Tools::getSpaceAfterColon()
			<< (int)RunningStats::mCPUUsage
			<< " %";
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(6, 0));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw ship's velovity 
		ss	<< Resource::resource->getBundle()->getString("runningStatsPlayerShipV");
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(1, 1));
		Resource::resource->getApp()->draw(text);
		ss.str("");
		
		sf::Vector2f positionTop = RunningStats::getTextPosition(2, 1);
		sf::Vector2f positionMed = RunningStats::getTextPosition(3, 1);
		sf::Vector2f positionBottom = RunningStats::getTextPosition(4, 1);
		
		ss << (int)Game::game->getShipPiloted()->getVelocityAt(Movable::MovableCardinality::NorthWest);
		text.setString(sf::String(ss.str()));
		text.setPosition(positionTop.x, positionTop.y);
		Resource::resource->getApp()->draw(text);
		ss.str("");

		ss << (int)Game::game->getShipPiloted()->getVelocityAt(Movable::MovableCardinality::North);
		text.setString(sf::String(ss.str()));
		text.setPosition(positionTop.x + RUNNINGSTATS_VELOCITY_OFFSET, positionTop.y);
		Resource::resource->getApp()->draw(text);
		ss.str("");

		ss << (int)Game::game->getShipPiloted()->getVelocityAt(Movable::MovableCardinality::NorthEast);
		text.setString(sf::String(ss.str()));
		text.setPosition(positionTop.x + RUNNINGSTATS_VELOCITY_OFFSET * 2, positionTop.y);
		Resource::resource->getApp()->draw(text);
		ss.str("");

		ss << (int)Game::game->getShipPiloted()->getVelocityAt(Movable::MovableCardinality::West);
		text.setString(sf::String(ss.str()));
		text.setPosition(positionMed.x, positionMed.y);
		Resource::resource->getApp()->draw(text);
		ss.str("");

		ss << (int)Game::game->getShipPiloted()->getVelocityAt(Movable::MovableCardinality::East);
		text.setString(sf::String(ss.str()));
		text.setPosition(positionMed.x + RUNNINGSTATS_VELOCITY_OFFSET * 2, positionMed.y);
		Resource::resource->getApp()->draw(text);
		ss.str("");

		ss << (int)Game::game->getShipPiloted()->getVelocityAt(Movable::MovableCardinality::SouthWest);
		text.setString(sf::String(ss.str()));
		text.setPosition(positionBottom.x, positionBottom.y);
		Resource::resource->getApp()->draw(text);
		ss.str("");

		ss << (int)Game::game->getShipPiloted()->getVelocityAt(Movable::MovableCardinality::South);
		text.setString(sf::String(ss.str()));
		text.setPosition(positionBottom.x + RUNNINGSTATS_VELOCITY_OFFSET, positionBottom.y);
		Resource::resource->getApp()->draw(text);
		ss.str("");

		ss << (int)Game::game->getShipPiloted()->getVelocityAt(Movable::MovableCardinality::SouthEast);
		text.setString(sf::String(ss.str()));
		text.setPosition(positionBottom.x + RUNNINGSTATS_VELOCITY_OFFSET * 2, positionBottom.y);
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw ship's position plane 1
		ss	<< Resource::resource->getBundle()->getString("runningStatsPlayerShipPositionP1") 
			<< Tools::getSpaceAfterColon()
			<< "x: " 
			<< Tools::formatNumber((int)Game::game->getShipPiloted()->getX(SHIP_PLANE)) 
			<< "  y: " 
			<< Tools::formatNumber((int)Game::game->getShipPiloted()->getY(SHIP_PLANE));
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(5, 1));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw ship's position plane 10
		ss	<< Resource::resource->getBundle()->getString("runningStatsPlayerShipPositionP10") 
			<< Tools::getSpaceAfterColon()
			<< "x: " 
			<< Tools::formatNumber((int)Game::game->getShipPiloted()->getX(SECTOR_PLANE)) 
			<< "  y: " 
			<< Tools::formatNumber((int)Game::game->getShipPiloted()->getY(SECTOR_PLANE));
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(6, 1));
		Resource::resource->getApp()->draw(text);
		ss.str("");	

		// Draw ship's position sector
		ss	<< Resource::resource->getBundle()->getString("runningStatsPlayerShipPositionSector") 
			<< Tools::getSpaceAfterColon()
			<< "x: " 
			<< Tools::formatNumber(currentSector->getIdSectorX()) 
			<< "  y: " 
			<< Tools::formatNumber(currentSector->getIdSectorY());
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(7, 1));
		Resource::resource->getApp()->draw(text);
		ss.str("");	

		// Draw sectors visible number
		ss	<< Resource::resource->getBundle()->getString("runningStatsMapSectorsVisible") 
			<< Tools::getSpaceAfterColon()
			<< MAP_SECTORS_TAB_SIZE * MAP_SECTORS_TAB_SIZE;
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(1, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw sectors loaded number
		ss	<< Resource::resource->getBundle()->getString("runningStatsMapSectorsLoaded") 
			<< Tools::getSpaceAfterColon()
			<< Game::game->getMap()->getSectorsLoadedNumber();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(2, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw sectors loaded number
		ss	<< Resource::resource->getBundle()->getString("runningStatsBackgroundSpaceCached") 
			<< Tools::getSpaceAfterColon()
			<< BackgroundSpace::getBackgroundSpaceCachedCount();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(3, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw current Sector
		ss	<< Resource::resource->getBundle()->getString("runningStatsMapSectorsCurrent");
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(5, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw current Sector Position
		ss	<< Resource::resource->getBundle()->getString("runningStatsMapSectorsCurrentPosition") 
			<< Tools::getSpaceAfterColon()
			<< "x: " 
			<< Tools::formatNumber(currentSector->getIdSectorX()) 
			<< "  y: " 
			<< Tools::formatNumber(currentSector->getIdSectorY());
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(6, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw current Sector Danger Level
		ss	<< Resource::resource->getBundle()->getString("runningStatsMapSectorsCurrentDangerLevel") 
			<< Tools::getSpaceAfterColon()
			<< Tools::formatNumber(currentSector->getDangerLevel()->getDangerLevel());
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(7, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw current Sector Planet count
		ss	<< Resource::resource->getBundle()->getString("runningStatsMapSectorsCurrentPlanets") 
			<< Tools::getSpaceAfterColon()
			<< Tools::formatNumber(currentSector->getPlanetsCount());
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(8, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw current Sector Cloud Gaz count
		ss	<< Resource::resource->getBundle()->getString("runningStatsMapSectorsCurrentCloudGazs") 
			<< Tools::getSpaceAfterColon()
			<< Tools::formatNumber(currentSector->getCloudGazsCount());
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(9, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw current Sector Cloud Wreck count
		ss	<< Resource::resource->getBundle()->getString("runningStatsMapSectorsCurrentCloudWreck") 
			<< Tools::getSpaceAfterColon()
			<< Tools::formatNumber(currentSector->getCloudWrecksCount());
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(10, 2));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw spawned npc
		for(int i = 0; i < currentSector->getDangerLevel()->getShipTypeSpawnCount(); i++)
		{
			int npcShipTypeCurrent = currentSector->getDangerLevel()->getShipTypeSpawn(i);
			int npcShipTypeNumberCurrent = Game::game->getMap()->getNpcShipSpawner()->getNpcShipCountByType(npcShipTypeCurrent);
			int npcShipTypeNumberMax = currentSector->getDangerLevel()->getShipTypeSpawnNumber(npcShipTypeCurrent);

			ss	<< Resource::resource->getBundle()->getString("runningStatsSpawnedNpc") 
				<< " "
				<< FactoryGet::getNpcTypeFactory()->getNpcType(npcShipTypeCurrent)->getName()
				<< ":" + Tools::getSpaceAfterColon() 
				<< npcShipTypeNumberCurrent 
				<< " / "
				<< npcShipTypeNumberMax;
			text.setString(sf::String(ss.str()));
			text.setPosition(RunningStats::getTextPosition(i + 1, 3));
			Resource::resource->getApp()->draw(text);
			ss.str("");
		}

		// Draw Auto Manager
		ss	<< Resource::resource->getBundle()->getString("runningStatsAutoManager") 
			<< Tools::getSpaceAfterColon()
			<< AutoManager::getAutoCount() 
			<< " / " 
			<< AutoManager::getAutoCountMax();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(1, 4));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw Network Job Manager
		ss	<< Resource::resource->getBundle()->getString("runningStatsNetworkJobManager") 
			<< Tools::getSpaceAfterColon()
			<< NetworkJobManager::getInstance()->getJobCount()
			<< " / "
			<< NetworkJobManager::getInstance()->getJobCountMax();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(2, 4));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw Particle Manager
		ss	<< Resource::resource->getBundle()->getString("runningStatsParticleManager") 
			<< Tools::getSpaceAfterColon()
			<< ParticleManager::getParticleCount()
			<< " / "
			<< ParticleManager::getParticleCountMax();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(3, 4));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw Wreck Manager
		ss	<< Resource::resource->getBundle()->getString("runningStatsWreckManager") 
			<< Tools::getSpaceAfterColon()
			<< WreckManager::getWreckCount()
			<< " / "
			<< WreckManager::getWreckCountMax();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(4, 4));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw Entity Manager
		ss	<< Resource::resource->getBundle()->getString("runningStatsEntityManager") 
			<< Tools::getSpaceAfterColon()
			<< EntityManager::getEntitiesCount();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(5, 4));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw selected angle
		ss	<< Resource::resource->getBundle()->getString("runningStatsSelectedAngle") 
			<< Tools::getSpaceAfterColon()
			<< Game::game->getMap()->getMapObjectSelector()->getObjectSelectedAngle();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(1, 5));
		Resource::resource->getApp()->draw(text);
		ss.str("");

		// Draw selected Distance
		ss	<< Resource::resource->getBundle()->getString("runningStatsSelectedDistance") 
			<< Tools::getSpaceAfterColon()
			<< Game::game->getMap()->getMapObjectSelector()->getObjectSelectedDistance();
		text.setString(sf::String(ss.str()));
		text.setPosition(RunningStats::getTextPosition(2, 5));
		Resource::resource->getApp()->draw(text);
		ss.str("");
	}
}






