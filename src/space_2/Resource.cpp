#include <iostream>
#include "Resource.h"
#include "Juckebox.h"
#include "BootScreen.h"
#include "Game.h"
#include "Camera.h"
#include "Ship.h"
#include "KeyValueFile.h"
#include "Option.h"
#include "ParticleManager.h"
#include "RunningStats.h"
#include "Dirent.h"
#include "BackgroundSpace.h"
#include "Session.h"
#include "Network.h"
#include "FactoryGet.h"
#include "DangerLevelManager.h"
#include "ContainerStackViewManager.h"
#include "NetworkJobManager.h"
#include "PlanetManager.h"
#include "CloudGazManager.h"
#include "CloudWreckManager.h"
#include "Camera.h"
#include "MapObject.h"
#include "BackgroundSpaceManager.h"
#include "StarManager.h"
#include "StationManager.h"
#include "Manager.h"
#include "ResourceConfig.h"

using namespace std;
using namespace sf;


//*************************************************************
// Init Static
//*************************************************************
Resource * Resource::resource;


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Resource::Resource(): mApp(VideoMode(Option::option->getAppScreenWidth(), Option::option->getAppScreenHeight(), APP_SCREEN_COLOR), APP_GAME_NAME, Option::option->getAppScreenMode(), sf::ContextSettings(0, 0, Option::option->getAppAntiAliasingLevel()))
{
	//*************************************************************
	// Sauvegarde de l'objet ressource
	//*************************************************************
	Resource::resource = this;


	//*************************************************************
	// Configure Global
	//*************************************************************
	// Init static and singleton
	this->initBeforeLoad();

	// Other init
	this->mApp.setPosition(sf::Vector2i(RESOURCE_APP_INITIAL_POSITION_X, RESOURCE_APP_INITIAL_POSITION_Y));		// Display window in corner top-left
	this->mApp.setFramerateLimit(RESOURCE_APP_FRAME_LIMIT);											// Set frame limit
	this->setAppRunning(true);																		// App is running
	srand((unsigned int)time(NULL));																// Initialize random 
	

	//*************************************************************
	// Configure Internationalisation
	//*************************************************************
	this->mBundle = new Internationalisation();
	

	//*************************************************************
	// Launch boot screen & Load ressource
	//*************************************************************	
	sf::Thread loadingThread(&Resource::loadAsync, this);
	loadingThread.launch();	

	BootScreen myBootScreen(this->getApp());
	myBootScreen.launch();

	this->loadSync();
	this->initAfterLoad();


	//*************************************************************
	// Configure Juckebox
	//*************************************************************
	this->mJuckebox	= new Juckebox();


	//*************************************************************
	// Configure Views
	//*************************************************************
	for(int i = 0; i < MAPOBJECT_PLANE_NUMBER; i++)
	{
		this->mViewMap.push_back(new sf::View());
	}

	this->resizeAllView();	
}

Resource::~Resource()
{
	// Uninit Singleton
	this->uninit();

	// Unload ressource
	this->unload();

	// Delete views
	for(int i = 0 ; i < this->mViewMap.size(); i++)
	{
		if(this->mViewMap[i] != NULL)
			delete this->mViewMap[i];
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::RenderWindow* Resource::getApp()
{
	return &(this->mApp);
}

sf::View* Resource::getViewUi()
{
	return &this->mViewUi;
}

sf::View* Resource::getViewMap(int p_plane)
{
	return this->mViewMap[p_plane];
}

sf::Image* Resource::getImage( std::string p_name )
{
	map<string, Image*>::iterator it;
	it = this->mImage.find(p_name);

	if(it != this->mImage.end())
	{
		return it->second;
	}
	else
	{
		cout << "Unable to find loaded image: " << p_name << endl;
	}

	return NULL;
}

sf::Texture* Resource::getTexture( std::string p_name )
{
	map<string, Texture*>::iterator it;
	it = this->mTexture.find(p_name);

	if(it != this->mTexture.end())
	{
		return it->second;
	}
	else
	{
		cout << "Unable to find loaded texture: " << p_name << endl;
		it = this->mTexture.find("notfound.png");
		if(it != this->mTexture.end())
			return it->second;
	}

	return NULL;
}

sf::Font* Resource::getFont( std::string p_name )
{
	map<string, Font*>::iterator it;
	it = this->mFont.find(p_name);

	if(it != this->mFont.end())
	{
		return it->second;
	}
	else
	{
		cout << "Unable to find loaded font: " << p_name << endl;
	}

	return NULL;
}

sf::Font* Resource::getFontDefault()
{
	return this->getFont(FONT_DEFAULT);
}

sf::Font* Resource::getFontUi()
{
	return this->getFont(FONT_UI);
}

sf::Font* Resource::getFontUiTheme()
{
	return this->getFont(FONT_UITHEME);
}

sf::SoundBuffer* Resource::getBuffer( std::string p_name )
{
	map<string, SoundBuffer*>::iterator it;
	it = this->mBuffer.find(p_name);

	if(it != this->mBuffer.end())
	{
		return it->second;
	}
	else
	{
		cout << "Unable to find loaded sound: " << p_name << endl;
	}

	return NULL;
}

sf::Music* Resource::getMusic( std::string p_name )
{
	map<string, Music*>::iterator it;
	it = this->mMusic.find(p_name);

	if(it != this->mMusic.end())
	{
		return it->second;
	}
	else
	{
		cout << "Unable to find loaded music: " << p_name << endl;
	}

	return NULL;
}

Internationalisation* Resource::getBundle()
{
	return this->mBundle;
}

Juckebox* Resource::getJuckebox()
{
	return this->mJuckebox;
}

KeyValueFile* Resource::getConfig( std::string p_name )
{
	map<string, KeyValueFile>::iterator it;
	it = this->mConfig.find(p_name);

	if(it != this->mConfig.end())
	{
		return &(it->second);
	}
	else
	{
		cout << "Unable to find loaded config: " << p_name << endl;
	}

	return NULL;
}

std::vector<KeyValueFile*> Resource::getConfigs( std::string p_configName )
{
	std::vector<KeyValueFile*> returnVector;

	for( std::map<std::string, KeyValueFile>::iterator it = this->mConfig.begin() ; it != this->mConfig.end(); it++ )
	{
		std::string currentConfigName = it->first;
		if (currentConfigName.compare(0, p_configName.length(), p_configName) == 0)
		{
			returnVector.push_back(&(it->second));
		}
	}

	return returnVector;
}

bool Resource::isAppRunning()
{
	return this->mAppRunning;
}

void Resource::setAppRunning( bool p_isAppRunning )
{
	this->mAppRunning = p_isAppRunning;
}


//*************************************************************
// Methode
//*************************************************************
void Resource::resizeAllView()
{
	// Resize all views
	this->mViewUi.setSize((float)this->mApp.getSize().x, (float)this->mApp.getSize().y);
	this->mViewUi.setCenter((float)this->mApp.getSize().x / 2, (float)this->mApp.getSize().y / 2);
	this->updateViewMap();
	
	// Select default view
	this->selectView(RESOURCE_ID_VIEW_DEFAULT);

	// Init other thing when screen size change
	ParticleManager::handleScreenAppResized();

	if(BackgroundSpaceManager::getInstance() != NULL)
		BackgroundSpaceManager::getInstance()->notifyAppSizeChanged();

	if(Game::game != NULL && Game::game->getUserInterface() != NULL)
		Game::game->getUserInterface()->handleScreenAppResized();
}

void Resource::updateViewMap()
{
	if(Game::game != NULL && Game::game->getMap() != NULL)
	{
		for(int i = 0 ; i < this->mViewMap.size(); i++)
		{
			int currentPlane = i;
			sf::View* currentView = this->mViewMap[i];

			if(currentView != NULL)
			{
				float zoom = Camera::camera->getZoom(currentPlane);
				currentView->zoom(zoom);

				int viewWidth = this->mApp.getSize().x / zoom;
				int viewHeight = this->mApp.getSize().y / zoom;
				currentView->setSize((float)viewWidth, (float)viewHeight);
				currentView->setCenter((float)viewWidth / 2, (float)viewHeight / 2);
			}
		}
	}
}

void Resource::selectView( int id_view, int p_plane )
{
	sf::View *myView;

	switch(id_view)
	{
	case RESOURCE_ID_VIEW_UI:
		myView = Resource::resource->getViewUi();
		break;

	case RESOURCE_ID_VIEW_MAP:
		myView = Resource::resource->getViewMap(p_plane);
		break;

	default:
		myView = Resource::resource->getViewUi();
		break;
	}
	
	if(myView != NULL)
		this->mApp.setView(*myView);
}

void Resource::initBeforeLoad()
{
	// Statics
	MapObject::init();
	
	// Singletons
	ParticleManager::init();
	RunningStats::init();
	Session::init();
	FactoryGet::init();
	ContainerStackViewManager::init();
	NetworkJobManager::init();
}

void Resource::initAfterLoad()
{		
	Manager::getInstance()->setConfig(new ResourceConfig());

	DangerLevelManager::init();
	PlanetManager::init();
	CloudGazManager::init();
	CloudWreckManager::init();
	BackgroundSpaceManager::init();
	StarManager::init();
	StationManager::init();
	Network::init();

	FactoryGet::getItemTypeFactory()->buildItemTypeList();
	FactoryGet::getItemTypeFactory()->buildItemTypeTree();
	FactoryGet::getItemFactory()->buildItemList();
}

void Resource::uninit()
{
	ParticleManager::uninit();
	SpriteParameterFactory::uninit();
	Session::uninit();
	FactoryGet::uninit();
	DangerLevelManager::uninit();
	ContainerStackViewManager::uninit();
	NetworkJobManager::uninit();
	PlanetManager::uninit();
	CloudGazManager::uninit();
	CloudWreckManager::uninit();
	BackgroundSpaceManager::uninit();
	StarManager::uninit();
	StationManager::uninit();
}

void Resource::loadAsync()
{
	// Load
	this->loadImages();
	this->loadFonts();
	this->loadSoundBuffers();
	this->loadMusic();
	this->loadConfigs();

	// Close bootScreen
	BootScreen::isRunning = false;
}

void Resource::loadSync()
{
	// Load
	this->loadTextures();
}

void Resource::unload()
{
	// Unload
	this->unloadImages();
	this->unloadTextures();
	this->unloadFonts();
	this->unloadSoundBuffers();
	this->unloadMusic();
}


//*************************************************************
// Configuration image
//*************************************************************
void Resource::loadImages()
{
	this->loadImages(FOLDER_IMAGE);
	this->loadImages(FOLDER_IMAGE_BOOT);
	this->loadImages(FOLDER_IMAGE_SPACE_SHIP);
	this->loadImages(FOLDER_IMAGE_SPACE);
	this->loadImages(FOLDER_IMAGE_SPACE_CLOUDGAZ);
	this->loadImages(FOLDER_IMAGE_SPACE_CLOUDWRECK);
	this->loadImages(FOLDER_IMAGE_SPACE_SHIP);
	this->loadImages(FOLDER_IMAGE_SPACE_PLANET);
	this->loadImages(FOLDER_IMAGE_SPACE_TURRET);
	this->loadImages(FOLDER_IMAGE_SPACE_STAR);
	this->loadImages(FOLDER_IMAGE_SPACE_WRECK);
	this->loadImages(FOLDER_IMAGE_SPACE_STATION);
	this->loadImages(FOLDER_IMAGE_SPACE_PROJECTILE);
	this->loadImages(FOLDER_IMAGE_UIGAME);
	this->loadImages(FOLDER_IMAGE_UIGAME_WINDOW);
	this->loadImages(FOLDER_IMAGE_UIGAME_SCREENSTATION);
	this->loadImages(FOLDER_IMAGE_MISC);
}

void Resource::loadImages( std::string path )
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.data());

	if (dir != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			string file_name = ent->d_name;

			if(file_name[0] != '.' && ent->d_type != DT_DIR)
			{
				Image *tmpImage = new Image();
				if(tmpImage->loadFromFile(path+file_name))
					tmpImage->createMaskFromColor(Color(0,255,255));
				else
					cout << "Error while loading image: " << path+file_name << endl;

				this->mImage.insert(pair<string, Image*>(file_name, tmpImage));
			}
		}
		closedir(dir);
	}
	else
	{
		cout << "Enable to find image folder: " << path << endl;
	}	
}

void Resource::unloadImages()
{
	for( map<string, Image*>::iterator it = this->mImage.begin() ; it != this->mImage.end(); it++ )
	{
		if((*it).second != NULL)
		{
			delete (*it).second;
			(*it).second = NULL;
		}
	}
}


//*************************************************************
// Configuration texture
//*************************************************************
void Resource::loadTextures()
{
	for( map<string, Image*>::iterator it = this->mImage.begin(); it != this->mImage.end(); it++ )
	{
		if((*it).second != NULL)
		{
			Texture *tmpTexture = new Texture();

			if((*it).second->getSize().x != 0 && (*it).second->getSize().y != 0)
			{
				tmpTexture->loadFromImage(*(*it).second);
				tmpTexture->setSmooth(false);

				this->mTexture.insert(pair<string, Texture*>((*it).first, tmpTexture));	
			}
		}
	}
}

void Resource::unloadTextures()
{
	for( map<string, Texture*>::iterator it = this->mTexture.begin() ; it != this->mTexture.end(); it++ )
	{
		if((*it).second != NULL)
		{
			delete (*it).second;
			(*it).second = NULL;
		}
	}
}


//*************************************************************
// Configuration font
//*************************************************************
void Resource::loadFonts()
{
	this->loadFonts(FOLDER_FONT);
}

void Resource::loadFonts( std::string path )
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.data());

	if (dir != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			string file_name = ent->d_name;

			if(file_name[0] != '.' && ent->d_type != DT_DIR)
			{
				Font *tmpFont = new Font();
				if(!tmpFont->loadFromFile(path+file_name))
					cout << "Error while loading font: " << path+file_name << endl;

				this->mFont.insert(pair<string, Font*>(file_name, tmpFont));
			}
		}
		closedir(dir);
	}
	else
	{
		cout << "Enable to find font folder: " << path << endl;
	}
}

void Resource::unloadFonts()
{
	for( map<string, Font*>::iterator it = this->mFont.begin() ; it != this->mFont.end(); it++ )
	{
		if((*it).second != NULL)
		{
			delete (*it).second;
			(*it).second = NULL;
		}
	}
}


//*************************************************************
// Configuration buffer
//*************************************************************
void Resource::loadSoundBuffers()
{
	this->loadSoundBuffers(FOLDER_SOUND);
}

void Resource::loadSoundBuffers( std::string path )
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.data());

	if (dir != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			string file_name = ent->d_name;

			if(file_name[0] != '.' && ent->d_type != DT_DIR)
			{
				SoundBuffer *tmpSoundBuffer = new SoundBuffer();
				if (!tmpSoundBuffer->loadFromFile(path+file_name))						
					cout << "Error while loading sound: " << path+file_name << endl;

				this->mBuffer.insert(pair<string, SoundBuffer*>(file_name, tmpSoundBuffer));
			}
		}
		closedir(dir);
	}
	else
	{
		cout << "Enable to find sound folder: " << path << endl;
	}	
}

void Resource::unloadSoundBuffers()
{
	for( map<string, SoundBuffer*>::iterator it = this->mBuffer.begin() ; it != this->mBuffer.end(); it++ )
	{
		if((*it).second != NULL)
		{
			delete (*it).second;
			(*it).second = NULL;
		}
	}
}


//*************************************************************
// Configuration music
//*************************************************************
void Resource::loadMusic()
{
	this->loadMusic(FOLDER_MUSIC);
}

void Resource::loadMusic( std::string path )
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.data());

	if (dir != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			string file_name = ent->d_name;

			if(file_name[0] != '.' && ent->d_type != DT_DIR)
			{
				Music *tmpMusic = new Music();
				if (!tmpMusic->openFromFile(path+file_name))						
					cout << "Error while loading music: " << path+file_name << endl;

				this->mMusic.insert(pair<string, Music*>(file_name, tmpMusic));
			}
		}
		closedir(dir);
	}
	else
	{
		cout << "Enable to find music folder: " << path << endl;
	}
}

void Resource::unloadMusic()
{
	for( map<string, Music*>::iterator it = this->mMusic.begin() ; it != this->mMusic.end(); it++ )
	{
		if((*it).second != NULL)
		{
			delete (*it).second;
			(*it).second = NULL;
		}
	}
}


//*************************************************************
// Config
//*************************************************************
void Resource::loadConfigs()
{
	this->loadConfigs(FOLDER_CONFIG_ITEMTIER);
	this->loadConfigs(FOLDER_CONFIG_ITEMTYPE);
	this->loadConfigs(FOLDER_CONFIG_SHIPMODEL);
	this->loadConfigs(FOLDER_CONFIG_SHIPTYPE);
	this->loadConfigs(FOLDER_CONFIG_GENERAL);
	this->loadConfigs(FOLDER_CONFIG_GENERAL_DANGERLEVEL);
	this->loadConfigs(FOLDER_CONFIG_GENERAL_CHARACTERLEVEL);
	this->loadConfigs(FOLDER_CONFIG_GENERAL_SHIPLEVEL);
	this->loadConfigs(FOLDER_CONFIG_RACE);
	this->loadConfigs(FOLDER_CONFIG_JOB);
	this->loadConfigs(FOLDER_CONFIG_SKILL);
	this->loadConfigs(FOLDER_CONFIG_AMMOTYPE);
	this->loadConfigs(FOLDER_CONFIG_AMMO);
	this->loadConfigs(FOLDER_CONFIG_WEAPONTYPE);
	this->loadConfigs(FOLDER_CONFIG_WEAPONMODEL);
	this->loadConfigs(FOLDER_CONFIG_NPCTYPE);
	this->loadConfigs(FOLDER_CONFIG_NPCSHIPMODEL);
	this->loadConfigs(FOLDER_CONFIG_ITEM);
	this->loadConfigs(FOLDER_CONFIG_PLANETMODEL);
	this->loadConfigs(FOLDER_CONFIG_PLANETTYPE);
	this->loadConfigs(FOLDER_CONFIG_CLOUDGAZMODEL);
	this->loadConfigs(FOLDER_CONFIG_CLOUDWRECKMODEL);
	this->loadConfigs(FOLDER_CONFIG_LOOTITEMMODEL);
	this->loadConfigs(FOLDER_CONFIG_STATIONMODEL);
	this->loadConfigs(FOLDER_CONFIG_STARMODEL);
	this->loadConfigs(FOLDER_CONFIG_TURRETEFFECTMODEL);
}

void Resource::loadConfigs( std::string path )
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.data());

	if (dir != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			string file_name = ent->d_name;

			if(file_name[0] != '.' && ent->d_type != DT_DIR)
			{
				this->mConfig.insert(pair<string, KeyValueFile>(file_name, KeyValueFile(path+file_name, file_name, true)));
			}
		}
		closedir(dir);
	}
	else
	{
		cout << "Unable to find config folder: " << path << endl;
	}
}








