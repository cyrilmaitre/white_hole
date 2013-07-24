#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define OPTION_FILE_NAME						"option/option.cfg"
#define OPTION_VERSION_KEY						"option_version"
#define OPTION_VERSION_VALUE					"1.0.41"
#define OPTION_APP_SCREEN_WIDTH_KEY				"app_screen_width"
#define OPTION_APP_SCREEN_WIDTH_VALUE			1280
#define OPTION_APP_SCREEN_HEIGHT_KEY			"app_screen_height"
#define OPTION_APP_SCREEN_HEIGHT_VALUE			950
#define OPTION_APP_SCREEN_MODE_KEY				"app_screen_mode"
#define OPTION_APP_SCREEN_MODE_VALUE			OPTION_APP_SCREEN_MODE_WINDOWED
#define OPTION_APP_ANTIALIASING_LEVEL_KEY		"app_antialiasing_level"
#define OPTION_APP_ANTIALIASING_LEVEL_VALUE		0
#define OPTION_APP_SOUND_MUSIC_KEY				"app_sound_music"
#define OPTION_APP_SOUND_MUSIC_VALUE			0
#define OPTION_APP_SOUND_AMBIENT_KEY			"app_sound_ambient"
#define OPTION_APP_SOUND_AMBIENT_VALUE			0
#define OPTION_APP_LANGUAGE_KEY					"app_language"
#define OPTION_APP_LANGUAGE_VALUE				OPTION_APP_LANGUAGE_EN
#define OPTION_APP_CONTROL_UP_KEY				"app_control_up"
#define OPTION_APP_CONTROL_UP_VALUE				sf::Keyboard::Z
#define OPTION_APP_CONTROL_RIGHT_KEY			"app_control_right"
#define OPTION_APP_CONTROL_RIGHT_VALUE			sf::Keyboard::D
#define OPTION_APP_CONTROL_DOWN_KEY				"app_control_down"
#define OPTION_APP_CONTROL_DOWN_VALUE			sf::Keyboard::S
#define OPTION_APP_CONTROL_LEFT_KEY				"app_control_left"
#define OPTION_APP_CONTROL_LEFT_VALUE			sf::Keyboard::Q
#define OPTION_APP_CONTROL_FIRE_KEY				"app_control_fire"			// Not used for the moment (mouse)
#define OPTION_APP_CONTROL_FIRE_VALUE			sf::Mouse::Button::Right	// Not used for the moment (mouse)
#define OPTION_APP_CONTROL_RELOAD_KEY			"app_control_reload"
#define OPTION_APP_CONTROL_RELOAD_VALUE			sf::Keyboard::R
#define OPTION_APP_CONTROL_UNSELECT_KEY			"app_control_unselect"
#define OPTION_APP_CONTROL_UNSELECT_VALUE		sf::Keyboard::Escape
#define OPTION_APP_CONTROL_HALFSTACKMOVE_KEY	"half_stack_move"
#define OPTION_APP_CONTROL_HALFSTACKMOVE_VALUE	sf::Keyboard::LShift
#define OPTION_APP_SCREEN_MODE_WINDOWED			(sf::Style::Resize | sf::Style::Close)
#define OPTION_APP_SCREEN_MODE_FULLSCREEN		sf::Style::Fullscreen
#define OPTION_APP_LANGUAGE_EN					"en"
#define OPTION_APP_LANGUAGE_FR					"fr"

class Option
{
public:
	// Constructor - Destructor
	Option(void);
	~Option(void);

	// Getters - Setters
	int getAppScreenWidth();
	void setAppScreenWidth(int p_width);

	int getAppScreenHeight();
	void setAppScreenHeight(int p_height);

	unsigned int getAppScreenMode();
	void setAppScreenMode(unsigned int p_mode);

	int getAppAntiAliasingLevel();
	void setAppAntiAliasingLevel(int p_level);

	int getAppSoundMusic();
	void setAppSoundMusic(int p_app_sound_music);

	int getAppSoundAmbient();
	void setAppSoundAmbient(int p_app_sound_ambient);

	std::string getAppLanguage();
	void setAppLanguage(std::string p_app_language);

	sf::Keyboard::Key getAppControl(std::string key);
	void setAppControl(std::string key, sf::Keyboard::Key value);

	// Methods
	bool loadOptionFromFile();
	bool loadOptionFromDefault();
	bool saveOptionToFile();

	// Static
	static Option *option;


private:
	// Option info
	KeyValueFile mOptionFile;

	// Screen
	int mAppScreenWidth;
	int mAppScreenHeight;
	unsigned int mAppScreenMode;
	int mAntiAliasingLevel;

	// Sound
	int mAppSoundMusic;
	int mAppSoundAmbient;

	// Internationalisation
	std::string mAppLanguage;

	// Controls
	std::map<std::string, sf::Keyboard::Key> mAppControls;
};

