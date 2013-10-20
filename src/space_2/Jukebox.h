#pragma once
#include "Resource.h"
#include "Clock.h"
#include "JukeboxMusic.h"

// Define
#define JUCKEBOX_SIMULTANEOUS_SOUND		128
#define JUCKEBOX_SOUND_UPDATE_TICK		1.f

class Jukebox
{
public:
	// Enum
	enum PlaylistState
	{
		Played,
		Paused,
		Stopped
	};

	// Constructor - Destructor
	Jukebox(void);
	~Jukebox(void);
	
	// Getters - Setters
	sf::Music* getMusicAmbiant();
	sf::Music* getMusicPlaylist();

	sf::Time getPlaylistCurrentDuration();
	sf::Time getPlaylistCurrentOffset();

	PlaylistState getPlaylistState();
	void setListenerPosition(float p_x, float p_y);

	// Methode
	void playMusicAmbiant();
	void pauseMusicAmbiant();

	void playPlaylist();
	void pausePlaylist();
	void stopPlaylist();
	void playlistNext();
	void playlistPrevious();

	void soundPlay(std::string p_soundKey, int p_amplifier = 100);
	void soundPlay(sf::SoundBuffer *p_mySoundBuffer, int p_amplifier = 100);
	bool soundInsert(sf::Sound *mySound);
	bool soundRemove(sf::Sound *mySound);

	void update();
	void updatePlaylist();
	void updateSound();

	static Jukebox* getInstance();
	static void destroyInstance();


private:
	// Ambiant
	sf::Music* mMusicAmbiant;

	// Playlist
	sf::Music* mMusicPlaylist;
	int mMusicPlaylistIndex;
	std::vector<JukeboxMusic*> mPlaylist;
	PlaylistState mPlaylistState;

	// Sound
	sf::Sound *mSounds[JUCKEBOX_SIMULTANEOUS_SOUND];
	mks::Clock mSoundTimer;

	// Static
	static Jukebox* mInstance;

	// Methods
	void loadNewMusicPlaylist();
};

