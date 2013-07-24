#include "Option.h"


//*************************************************************
// Static
//*************************************************************
Option * Option::option;


//*************************************************************
// Constructor - Destructor
//*************************************************************
Option::Option(void) : mOptionFile(OPTION_FILE_NAME)
{
	bool isOptionFileOpened;
	bool isOptionFileEmpty;

	// Load file
	isOptionFileOpened	= this->mOptionFile.loadFromFile();
	isOptionFileEmpty	= (this->mOptionFile.getString(OPTION_VERSION_KEY) != OPTION_VERSION_VALUE);

	// Load option
	if(isOptionFileOpened && !isOptionFileEmpty)
	{
		this->loadOptionFromFile();
	}
	else
	{
		this->loadOptionFromDefault();
		this->saveOptionToFile();
	}

	// Save option
	this->option = this;
}

Option::~Option(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
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

int Option::getAppSoundMusic()
{
	return this->mAppSoundMusic;
}

void Option::setAppSoundMusic( int p_app_sound_music )
{
	if(p_app_sound_music < 0)
		p_app_sound_music = 0;
	else if(p_app_sound_music > 100)
		p_app_sound_music = 100;

	this->mAppSoundMusic = p_app_sound_music;
}

int Option::getAppSoundAmbient()
{
	return this->mAppSoundAmbient;
}

void Option::setAppSoundAmbient( int p_app_sound_ambient )
{
	if(p_app_sound_ambient < 0)
		p_app_sound_ambient = 0;
	else if(p_app_sound_ambient > 100)
		p_app_sound_ambient = 100;

	this->mAppSoundAmbient = p_app_sound_ambient;
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
// Methode
//*************************************************************
bool Option::loadOptionFromFile()
{
	// App screen
	this->setAppScreenWidth(this->mOptionFile.getInt(OPTION_APP_SCREEN_WIDTH_KEY));
	this->setAppScreenHeight(this->mOptionFile.getInt(OPTION_APP_SCREEN_HEIGHT_KEY));
	this->setAppScreenMode(this->mOptionFile.getInt(OPTION_APP_SCREEN_MODE_KEY));
	this->setAppAntiAliasingLevel(this->mOptionFile.getInt(OPTION_APP_ANTIALIASING_LEVEL_KEY));

	// App sound
	this->setAppSoundMusic(this->mOptionFile.getInt(OPTION_APP_SOUND_MUSIC_KEY));
	this->setAppSoundAmbient(this->mOptionFile.getInt(OPTION_APP_SOUND_AMBIENT_KEY));

	// App language
	this->setAppLanguage(this->mOptionFile.getString(OPTION_APP_LANGUAGE_KEY));

	// App controls
	this->setAppControl(OPTION_APP_CONTROL_UP_KEY, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTION_APP_CONTROL_UP_KEY));
	this->setAppControl(OPTION_APP_CONTROL_RIGHT_KEY, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTION_APP_CONTROL_RIGHT_KEY));
	this->setAppControl(OPTION_APP_CONTROL_DOWN_KEY, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTION_APP_CONTROL_DOWN_KEY));
	this->setAppControl(OPTION_APP_CONTROL_LEFT_KEY, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTION_APP_CONTROL_LEFT_KEY));
	this->setAppControl(OPTION_APP_CONTROL_RELOAD_KEY, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTION_APP_CONTROL_RELOAD_KEY));
	this->setAppControl(OPTION_APP_CONTROL_UNSELECT_KEY, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTION_APP_CONTROL_UNSELECT_KEY));
	this->setAppControl(OPTION_APP_CONTROL_HALFSTACKMOVE_KEY, (sf::Keyboard::Key)this->mOptionFile.getInt(OPTION_APP_CONTROL_HALFSTACKMOVE_KEY));

	return true;
}

bool Option::loadOptionFromDefault()
{
	// App screen
	this->setAppScreenWidth(OPTION_APP_SCREEN_WIDTH_VALUE);
	this->setAppScreenHeight(OPTION_APP_SCREEN_HEIGHT_VALUE);
	this->setAppScreenMode(OPTION_APP_SCREEN_MODE_VALUE);
	this->setAppAntiAliasingLevel(OPTION_APP_ANTIALIASING_LEVEL_VALUE);

	// App sound
	this->setAppSoundMusic(OPTION_APP_SOUND_MUSIC_VALUE);
	this->setAppSoundAmbient(OPTION_APP_SOUND_AMBIENT_VALUE);

	// App language
	this->setAppLanguage(OPTION_APP_LANGUAGE_VALUE);

	// App controls
	this->setAppControl(OPTION_APP_CONTROL_UP_KEY, OPTION_APP_CONTROL_UP_VALUE);
	this->setAppControl(OPTION_APP_CONTROL_RIGHT_KEY, OPTION_APP_CONTROL_RIGHT_VALUE);
	this->setAppControl(OPTION_APP_CONTROL_DOWN_KEY, OPTION_APP_CONTROL_DOWN_VALUE);
	this->setAppControl(OPTION_APP_CONTROL_LEFT_KEY, OPTION_APP_CONTROL_LEFT_VALUE);
	this->setAppControl(OPTION_APP_CONTROL_RELOAD_KEY, OPTION_APP_CONTROL_RELOAD_VALUE);
	this->setAppControl(OPTION_APP_CONTROL_UNSELECT_KEY, OPTION_APP_CONTROL_UNSELECT_VALUE);
	this->setAppControl(OPTION_APP_CONTROL_HALFSTACKMOVE_KEY, OPTION_APP_CONTROL_HALFSTACKMOVE_VALUE);

	return true;
}

bool Option::saveOptionToFile()
{
	// Configure option version
	this->mOptionFile.setString(OPTION_VERSION_KEY, OPTION_VERSION_VALUE);

	// App screen
	this->mOptionFile.setInt(OPTION_APP_SCREEN_WIDTH_KEY, this->getAppScreenWidth());
	this->mOptionFile.setInt(OPTION_APP_SCREEN_HEIGHT_KEY, this->getAppScreenHeight());
	this->mOptionFile.setInt(OPTION_APP_SCREEN_MODE_KEY, this->getAppScreenMode());
	this->mOptionFile.setInt(OPTION_APP_ANTIALIASING_LEVEL_KEY, this->getAppAntiAliasingLevel());

	// App sound
	this->mOptionFile.setInt(OPTION_APP_SOUND_MUSIC_KEY, this->getAppSoundMusic());
	this->mOptionFile.setInt(OPTION_APP_SOUND_AMBIENT_KEY, this->getAppSoundAmbient());

	// App language
	this->mOptionFile.setString(OPTION_APP_LANGUAGE_KEY, this->getAppLanguage());

	// App controls
	this->mOptionFile.setInt(OPTION_APP_CONTROL_UP_KEY, this->getAppControl(OPTION_APP_CONTROL_UP_KEY));
	this->mOptionFile.setInt(OPTION_APP_CONTROL_RIGHT_KEY, this->getAppControl(OPTION_APP_CONTROL_RIGHT_KEY));
	this->mOptionFile.setInt(OPTION_APP_CONTROL_DOWN_KEY, this->getAppControl(OPTION_APP_CONTROL_DOWN_KEY));
	this->mOptionFile.setInt(OPTION_APP_CONTROL_LEFT_KEY, this->getAppControl(OPTION_APP_CONTROL_LEFT_KEY));
	this->mOptionFile.setInt(OPTION_APP_CONTROL_RELOAD_KEY, this->getAppControl(OPTION_APP_CONTROL_RELOAD_KEY));
	this->mOptionFile.setInt(OPTION_APP_CONTROL_UNSELECT_KEY, this->getAppControl(OPTION_APP_CONTROL_UNSELECT_KEY));
	this->mOptionFile.setInt(OPTION_APP_CONTROL_HALFSTACKMOVE_KEY, this->getAppControl(OPTION_APP_CONTROL_HALFSTACKMOVE_KEY));

	// Save to file
	return this->mOptionFile.saveToFile();
}
