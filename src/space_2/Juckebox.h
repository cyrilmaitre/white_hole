#pragma once
#include "Resource.h"
#include "Clock.h"

// Define
#define JUCKEBOX_TIMEBEFORENEXT_MIN		10
#define JUCKEBOX_TIMEBEFORENEXT_MAX		20
#define JUCKEBOX_SIMULTANEOUS_SOUND		256
#define JUCKEBOX_SOUND_UPDATE_FREQ		1.f

class Juckebox
{
public:
	// Constructor - Destructor
	Juckebox(void);
	~Juckebox(void);
	
	// Getters - Setters
	sf::Music* getCurrentMusic();
	std::string getCurrentMusicName();
	std::string getCurrentMusicTimer();

	int getCurrentMusicIndex();
	void setCurrentMusicIndex(int p_index);

	int getRandomIndex();

	// Methode
	void playlistPlay();
	void playlistPause();
	void playlistStop();
	void playlistNext();
	void playlistPrevious();
	void playlistSetOffset(int p_offsetPercent);
	void playlistLaunch();
	void playlistUpdate();
	void playlistUpdateVolume();

	void soundPlay(std::string p_soundKey, int p_amplifier = 100);
	void soundPlay(sf::SoundBuffer *p_mySoundBuffer, int p_amplifier = 100);
	void soundUpdate();
	bool soundInsert(sf::Sound *mySound);
	bool soundRemove(sf::Sound *mySound);

	void update();


private:
	// Playlist
	std::map<std::string, sf::Music*> mPlaylistMusics;
	std::string *mPlaylist;
	int mCurrentMusicIndex;
	bool mMusicPlayed;
	float mTimeBeforeNextMusic;
	mks::Clock mPlaylistTimer;
	mks::Clock mSoundTimer;

	// Sound
	sf::Sound *mSounds[JUCKEBOX_SIMULTANEOUS_SOUND];
};

