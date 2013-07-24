#pragma once
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <sstream>
#include <list>
#include <time.h>
#include <json/json.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "ResourceDefine.h"
#include "Internationalisation.h"
#include "Tools.h"
#include "Network.h"

// Define divers
#define RESOURCE_APP_FRAME_LIMIT			500
#define RESOURCE_APP_INITIAL_POSITION_X		0
#define RESOURCE_APP_INITIAL_POSITION_Y		0
#define RESOURCE_PI							3.14159265
#define RESOURCE_ID_VIEW_UI					0
#define RESOURCE_ID_VIEW_MAP				1
#define RESOURCE_ID_VIEW_DEFAULT			RESOURCE_ID_VIEW_UI

class Juckebox;

class Resource
{
public:
	// Constructeur - Destructeur
	Resource();
	~Resource();

	// Getters - Setters
	sf::RenderWindow* getApp();
	sf::View* getViewUi();
	sf::View* getViewMap(int p_plane);
	
	sf::Image* getImage(std::string p_name);
	sf::Texture* getTexture(std::string p_name);
	sf::Font* getFont(std::string p_name);
	sf::Font* getFontDefault();
	sf::Font* getFontUi();
	sf::Font* getFontUiTheme();
	sf::SoundBuffer* getBuffer(std::string p_name);
	sf::Music* getMusic(std::string p_name);
	KeyValueFile* getConfig(std::string p_name);
	Internationalisation* getBundle();
	Juckebox* getJuckebox();

	bool isAppRunning();
	void setAppRunning(bool p_isAppRunning);

	// Methode
	void updateViewMap();

	void initBeforeLoad();
	void initAfterLoad();
	void uninit();

	void loadAsync();
	void loadSync();
	void loadImages();
	void loadImages(std::string path);
	void loadTextures();
	void loadFonts();
	void loadFonts(std::string path);
	void loadSoundBuffers();
	void loadSoundBuffers(std::string path);
	void loadMusic();
	void loadMusic(std::string path);
	void loadConfigs();
	void loadConfigs(std::string path);

	void unload();
	void unloadImages();
	void unloadTextures();
	void unloadFonts();
	void unloadSoundBuffers();
	void unloadMusic();

	void resizeAllView();
	void selectView(int id_view, int p_plane = 0);

	// Statics
	static Resource *resource;


private:
	// Attributs
	sf::RenderWindow mApp;
	sf::View mViewUi;	
	std::vector<sf::View*> mViewMap;

	std::map<std::string, sf::Image*> mImage;
	std::map<std::string, sf::Texture*> mTexture;
	std::map<std::string, sf::Font*> mFont;
	std::map<std::string, sf::SoundBuffer*> mBuffer;
	std::map<std::string, sf::Music*> mMusic;
	std::map<std::string, KeyValueFile> mConfig;
	Internationalisation *mBundle;
	Juckebox *mJuckebox;
	
	bool mAppRunning;
};

