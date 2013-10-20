#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define OPTIONKEY_VERSION					"option_version"
#define OPTIONKEY_SCREEN_WIDTH				"app_screen_width"
#define OPTIONKEY_SCREEN_HEIGHT				"app_screen_height"
#define OPTIONKEY_SCREEN_MODE				"app_screen_mode"
#define OPTIONKEY_ANTIALIASING_LEVEL		"app_antialiasing_level"
#define OPTIONKEY_SOUND_GLOBAL				"app_sound_global"
#define OPTIONKEY_SOUND_MUSIC				"app_sound_music"
#define OPTIONKEY_SOUND_AMBIENT				"app_sound_ambient"
#define OPTIONKEY_SOUND_EFFECT				"app_sound_effect"
#define OPTIONKEY_LANGUAGE					"app_language"
#define OPTIONKEY_CONTROL_UP				"app_control_up"
#define OPTIONKEY_CONTROL_RIGHT				"app_control_right"
#define OPTIONKEY_CONTROL_DOWN				"app_control_down"
#define OPTIONKEY_CONTROL_LEFT				"app_control_left"
#define OPTIONKEY_CONTROL_RELOAD			"app_control_reload"
#define OPTIONKEY_CONTROL_UNSELECT			"app_control_unselect"
#define OPTIONKEY_CONTROL_HALFSTACKMOVE		"half_stack_move"


class Option
{
public:
	// Constructor - Destructor
	Option(void);
	~Option(void);

	// Getters - Setters
	std::string getAppVersion();
	void setAppVersion(std::string p_version);

	int getAppScreenWidth();
	void setAppScreenWidth(int p_width);

	int getAppScreenHeight();
	void setAppScreenHeight(int p_height);

	unsigned int getAppScreenMode();
	void setAppScreenMode(unsigned int p_mode);

	int getAppAntiAliasingLevel();
	void setAppAntiAliasingLevel(int p_level);

	float getAppSoundGlobal();
	void setAppSoundGlobal(float p_appSoundGlobal);

	float getAppSoundAmbient();
	void setAppSoundAmbient(float p_app_sound_ambient);

	float getAppSoundMusic();
	void setAppSoundMusic(float p_app_sound_music);

	float getAppSoundEffect();
	void setAppSoundEffect(float p_appSoundEffect);

	std::string getAppLanguage();
	void setAppLanguage(std::string p_app_language);

	sf::Keyboard::Key getAppControl(std::string key);
	void setAppControl(std::string key, sf::Keyboard::Key value);

	// Methods
	bool loadOptionFromFile();
	bool loadOptionFromDefault();
	bool saveOptionToFile();

	void notifyAppSoundGlobalChanged();
	void notifyAppSoundAmbiantChanged();
	void notifyAppSoundMusicChanged();

	static Option* getInstance();
	static void destroyInstance();

	
private:
	// Option info
	KeyValueFile mOptionFile;

	// App
	std::string mAppVersion;

	// Screen
	int mAppScreenWidth;
	int mAppScreenHeight;
	unsigned int mAppScreenMode;
	int mAntiAliasingLevel;

	// Sound
	float mAppSoundGlobal;
	float mAppSoundAmbient;
	float mAppSoundMusic;
	float mAppSoundEffect;

	// Internationalisation
	std::string mAppLanguage;

	// Controls
	std::map<std::string, sf::Keyboard::Key> mAppControls;

	// Static
	static Option* mInstance;
};

