#pragma once
#include "Resource.h"
#include "Clock.h"

// Define
#define JUCKEBOX_SIMULTANEOUS_SOUND		128
#define JUCKEBOX_SOUND_UPDATE_FREQ		1.f

class Jukebox
{
public:
	// Constructor - Destructor
	Jukebox(void);
	~Jukebox(void);
	
	// Getters - Setters
	sf::Music* getMusicAmbiant();

	void setListenerPosition(double p_x, double p_y);

	// Methode
	void playMusicAmbiant();
	void pauseMusicAmbiant();

	void soundPlay(std::string p_soundKey, int p_amplifier = 100);
	void soundPlay(sf::SoundBuffer *p_mySoundBuffer, int p_amplifier = 100);
	void soundUpdate();
	bool soundInsert(sf::Sound *mySound);
	bool soundRemove(sf::Sound *mySound);
	void update();

	static Jukebox* getInstance();
	static void destroyInstance();


private:
	// Ambiant
	sf::Music* mMusicAmbiant;

	// Playlist
	float mTimeBeforeNextMusic;
	mks::Clock mPlaylistTimer;
	mks::Clock mSoundTimer;

	// Sound
	sf::Sound *mSounds[JUCKEBOX_SIMULTANEOUS_SOUND];

	// Static
	static Jukebox* mInstance;
};

