#include "Option.h"
#include "Jukebox.h"


//*************************************************************
// Static
//*************************************************************
Option* Option::mInstance = NULL;


//*************************************************************
// Define
//*************************************************************
#define OPTION_FILE_PATHNAME					"option/"
#define OPTION_FILE_FILENAME					"option.cfg"
 
#define OPTION_VERSION_VALUE					"0.1"
#define OPTION_APP_SCREEN_WIDTH_VALUE			1280
#define OPTION_APP_SCREEN_HEIGHT_VALUE			950
#define OPTION_APP_SCREEN_MODE_VALUE			OPTION_APP_SCREEN_MODE_WINDOWED
#define OPTION_APP_ANTIALIASING_LEVEL_VALUE		0
#define OPTION_APP_SOUND_GLOBAL_VALUE			50
#define OPTION_APP_SOUND_MUSIC_VALUE			50
#define OPTION_APP_SOUND_AMBIENT_VALUE			50
#define OPTION_APP_SOUND_EFFECT_VALUE			50
#define OPTION_APP_LANGUAGE_VALUE				OPTION_APP_LANGUAGE_EN
#define OPTION_APP_CONTROL_UP_VALUE				sf::Keyboard::Z
#define OPTION_APP_CONTROL_RIGHT_VALUE			sf::Keyboard::D
#define OPTION_APP_CONTROL_DOWN_VALUE			sf::Keyboard::S
#define OPTION_APP_CONTROL_LEFT_VALUE			sf::Keyboard::Q
#define OPTION_APP_CONTROL_RELOAD_VALUE			sf::Keyboard::R
#define OPTION_APP_CONTROL_UNSELECT_VALUE		sf::Keyboard::Escape
#define OPTION_APP_CONTROL_HALFSTACKMOVE_VALUE	sf::Keyboard::LShift
#define OPTION_APP_SCREEN_MODE_WINDOWED			(sf::Style::Resize | sf::Style::Close)
#define OPTION_APP_SCREEN_MODE_FULLSCREEN		sf::Style::Fullscreen
#define OPTION_APP_LANGUAGE_EN					"en"
#define OPTION_APP_LANGUAGE_FR					"fr"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Option::Option(void) : mOptionFile((OPTION_FILE_PATHNAME OPTION_FILE_FILENAME),  OPTION_FILE_FILENAME)
{
	if(this->mOptionFile.loadFromFile())
	{
		this->loadOptionFromFile();
	}
	else
	{
		this->loadOptionFromDefault();
		this->saveOptionToFile();
	}
}

Option::~Option(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string Option::getAppVersion()
{
	return this->mAppVersion;
}

void Option::setAppVersion( std::string p_version )
{
	this->mAppVersion = p_version;
}

int Option::getAppScreenWidth()
{
	return this->mAppScreenWidth;
}

void Option::setAppScreenWidth( int p_width )
{
	if(p_width < 0)
		p_width = 0;
	this->mAppScreenWidth = p_width;
}

int Option::getAppScreenHeight()
{
	return this->mAppScreenHeight;
}

void Option::setAppScreenHeight( int p_height )
{
	if(p_height < 0)
		p_height = 0;
	this->mAppScreenHeight = p_height;
}

unsigned int Option::getAppScreenMode()
{
	return this->mAppScreenMode;
}

void Option::setAppScreenMode( unsigned int p_mode )
{
	if(	p_mode != OPTION_APP_SCREEN_MODE_WINDOWED &&
		p_mode != OPTION_APP_SCREEN_MODE_FULLSCREEN)
			p_mode = OPTION_APP_SCREEN_MODE_WINDOWED;
	this->mAppScreenMode = p_mode;
}

int Option::getAppAntiAliasingLevel()
{
	return this->mAntiAliasingLevel;
}

void Option::setAppAntiAliasingLevel( int p_level )
{
	this->mAntiAliasingLevel = p_level;
}

float Option::getAppSoundGlobal()
{
	return this->mAppSoundGlobal;
}

void Option::setAppSoundGlobal( float p_appSoundGlobal )
{
	if(p_appSoundGlobal < 0.0f)
		p_appSoundGlobal = 0.0f;
	else if(p_appSoundGlobal > 100.0f)
		p_appSoundGlobal = 100.0f;

	if(this->mAppSoundGlobal != p_appSoundGlobal)
	{
		this->mAppSoundGlobal = p_appSoundGlobal;
		this->notifyAppSoundGlobalChanged();
	}
}

float Option::getAppSoundAmbient()
{
	return this->mAppSoundAmbient;
}

void Option::setAppSoundAmbient( float p_app_sound_ambient )
{
	if(p_app_sound_ambient < 0.0f)
		p_app_sound_ambient = 0.0f;
	else if(p_app_sound_ambient > 100.0f)
		p_app_sound_ambient = 100.0f;

	this->mAppSoundAmbient = p_app_sound_ambient;
}

float Option::getAppSoundMusic()
{
	return this->mAppSoundMusic;
}

void Option::setAppSoundMusic( float p_app_sound_music )
{
	if(p_app_sound_music < 0.0f)
		p_app_sound_music = 0.0f;
	else if(p_app_sound_music > 100.0f)
		p_app_sound_music = 100.0f;

	this->mAppSoundMusic = p_app_sound_music;
}

float Option::getAppSoundEffect()
{
	return this->mAppSoundEffect;
}

void Option::setAppSoundEffect( float p_appSoundEffect )
{
	if(p_appSoundEffect < 0.0f)
		p_appSoundEffect = 0.0f;
	else if(p_appSoundEffect > 100.0f)
		p_appSoundEffect = 100.0f;

	this->mAppSoundEffect = p_appSoundEffect;
}

std::string Option::getAppLanguage()
{
	return this->mAppLanguage;
}

void Option::setAppLanguage( std::string p_app_language )
{
	if(	p_app_language != OPTION_APP_LANGUAGE_EN &&
		p_app_language != OPTION_APP_LANGUAGE_FR)
			p_app_language = OPTION_APP_LANGUAGE_EN;

	this->mAppLanguage = p_app_language;
}

sf::Keyboard::Key Option::getAppControl( std::string key )
{
	std::map<std::string, sf::Keyboard::Key>::iterator it;
	it = this->mAppControls.find(key);

	if(it != this->mAppControls.end())
	{
		return it->second;
	}

	return sf::Keyboard::Key::KeyCount;
}

void Option::setAppControl( std::string key, sf::Keyboard::Key value )
{
	bool isKeyExist = false;
	std::map<std::string, sf::Keyboard::Key>::iterator it;
	it = this->mAppControls.find(key);

	if(it != this->mAppControls.end())
		isKeyExist = true;

	if(isKeyExist)
		it->second = value;
	else
		this->mAppControls.insert(std::pair<std::string, sf::Keyboard::Key>(key, value));
}


//*************************************************************
// Methods
//*************************************************************
Option* Option::getInstance()
{
	if(Option::mInstance == NULL)
		Option::mInstance = new Option();
	return Option::mInstance;
}

void Option::destroyInstance()
{
	if(Option::mInstance != NULL)
	{
		delete Option::mInstance;
		Option::mInstance = NULL;
	}
}

bool Option::loadOptionFromFile()
{
	// App
	this->setAppVersion(this->mOptionFile.getString(OPTIONKEY_VERSION));

	// App screen
	this->setAppScreenWidth(this->mOptionFile.getInt(OPTIONKEY_SCREEN_WIDTH));
	this->setAppScreenHeight(this->mOptionFile.getInt(OPTIONKEY_SCREEN_HEIGHT));
	this->setAppScreenMode(this->mOptionFile.getInt(OPTIONKEY_SCREEN_MODE));
	this->setAppAntiAliasingLevel(this->mOptionFile.getInt(OPTIONKEY_ANTIALIASING_LEVEL));

	// App sound
	this->setAppSoundGlobal(this->mOptionFile.getFloat(OPTIONKEY_SOUND_GLOBAL));
	this->setAppSoundMusic(this->mOptionFile.getFloat(OPTIONKEY_SOUND_MUSIC));
	this->setAppSoundAmbient(this->mOptionFile.getFloat(OPTIONKEY_SOUND_AMBIENT));
	this->setAppSoundEffect(this->mOptionFile.getFloat(OPTIONKEY_SOUND_EFFECT));

	// App language
	this->setAppLanguage(this->mOptionFile.getString(OPTIONKEY_LANGUAGE));

	// App controls
	this->setAppControl(OPTIONKEY_CONTROL_UP, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTIONKEY_CONTROL_UP));
	this->setAppControl(OPTIONKEY_CONTROL_RIGHT, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTIONKEY_CONTROL_RIGHT));
	this->setAppControl(OPTIONKEY_CONTROL_DOWN, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTIONKEY_CONTROL_DOWN));
	this->setAppControl(OPTIONKEY_CONTROL_LEFT, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTIONKEY_CONTROL_LEFT));
	this->setAppControl(OPTIONKEY_CONTROL_RELOAD, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTIONKEY_CONTROL_RELOAD));
	this->setAppControl(OPTIONKEY_CONTROL_UNSELECT, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTIONKEY_CONTROL_UNSELECT));
	this->setAppControl(OPTIONKEY_CONTROL_HALFSTACKMOVE, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTIONKEY_CONTROL_HALFSTACKMOVE));

	return true;
}

bool Option::loadOptionFromDefault()
{
	// App
	this->setAppVersion(OPTION_VERSION_VALUE);

	// App screen
	this->setAppScreenWidth(OPTION_APP_SCREEN_WIDTH_VALUE);
	this->setAppScreenHeight(OPTION_APP_SCREEN_HEIGHT_VALUE);
	this->setAppScreenMode(OPTION_APP_SCREEN_MODE_VALUE);
	this->setAppAntiAliasingLevel(OPTION_APP_ANTIALIASING_LEVEL_VALUE);

	// App sound
	this->setAppSoundGlobal(OPTION_APP_SOUND_GLOBAL_VALUE);
	this->setAppSoundMusic(OPTION_APP_SOUND_MUSIC_VALUE);
	this->setAppSoundAmbient(OPTION_APP_SOUND_AMBIENT_VALUE);
	this->setAppSoundEffect(OPTION_APP_SOUND_EFFECT_VALUE);

	// App language
	this->setAppLanguage(OPTION_APP_LANGUAGE_VALUE);

	// App controls
	this->setAppControl(OPTIONKEY_CONTROL_UP, OPTION_APP_CONTROL_UP_VALUE);
	this->setAppControl(OPTIONKEY_CONTROL_RIGHT, OPTION_APP_CONTROL_RIGHT_VALUE);
	this->setAppControl(OPTIONKEY_CONTROL_DOWN, OPTION_APP_CONTROL_DOWN_VALUE);
	this->setAppControl(OPTIONKEY_CONTROL_LEFT, OPTION_APP_CONTROL_LEFT_VALUE);
	this->setAppControl(OPTIONKEY_CONTROL_RELOAD, OPTION_APP_CONTROL_RELOAD_VALUE);
	this->setAppControl(OPTIONKEY_CONTROL_UNSELECT, OPTION_APP_CONTROL_UNSELECT_VALUE);
	this->setAppControl(OPTIONKEY_CONTROL_HALFSTACKMOVE, OPTION_APP_CONTROL_HALFSTACKMOVE_VALUE);

	return true;
}

bool Option::saveOptionToFile()
{
	// Configure option version
	this->mOptionFile.setString(OPTIONKEY_VERSION, OPTION_VERSION_VALUE);

	// App screen
	this->mOptionFile.setInt(OPTIONKEY_SCREEN_WIDTH, this->getAppScreenWidth());
	this->mOptionFile.setInt(OPTIONKEY_SCREEN_HEIGHT, this->getAppScreenHeight());
	this->mOptionFile.setInt(OPTIONKEY_SCREEN_MODE, this->getAppScreenMode());
	this->mOptionFile.setInt(OPTIONKEY_ANTIALIASING_LEVEL, this->getAppAntiAliasingLevel());

	// App sound
	this->mOptionFile.setFloat(OPTIONKEY_SOUND_GLOBAL, this->getAppSoundGlobal());
	this->mOptionFile.setFloat(OPTIONKEY_SOUND_MUSIC, this->getAppSoundMusic());
	this->mOptionFile.setFloat(OPTIONKEY_SOUND_AMBIENT, this->getAppSoundAmbient());
	this->mOptionFile.setFloat(OPTIONKEY_SOUND_EFFECT, this->getAppSoundEffect());

	// App language
	this->mOptionFile.setString(OPTIONKEY_LANGUAGE, this->getAppLanguage());

	// App controls
	this->mOptionFile.setInt(OPTIONKEY_CONTROL_UP, this->getAppControl(OPTIONKEY_CONTROL_UP));
	this->mOptionFile.setInt(OPTIONKEY_CONTROL_RIGHT, this->getAppControl(OPTIONKEY_CONTROL_RIGHT));
	this->mOptionFile.setInt(OPTIONKEY_CONTROL_DOWN, this->getAppControl(OPTIONKEY_CONTROL_DOWN));
	this->mOptionFile.setInt(OPTIONKEY_CONTROL_LEFT, this->getAppControl(OPTIONKEY_CONTROL_LEFT));
	this->mOptionFile.setInt(OPTIONKEY_CONTROL_RELOAD, this->getAppControl(OPTIONKEY_CONTROL_RELOAD));
	this->mOptionFile.setInt(OPTIONKEY_CONTROL_UNSELECT, this->getAppControl(OPTIONKEY_CONTROL_UNSELECT));
	this->mOptionFile.setInt(OPTIONKEY_CONTROL_HALFSTACKMOVE, this->getAppControl(OPTIONKEY_CONTROL_HALFSTACKMOVE));

	// Save to file
	return this->mOptionFile.saveToFile();
}

void Option::notifyAppSoundGlobalChanged()
{
	sf::Listener::setGlobalVolume(this->getAppSoundGlobal());
}

void Option::notifyAppSoundAmbiantChanged()
{
	Jukebox::getInstance()->getMusicAmbiant()->setVolume(this->mAppSoundAmbient);
}


