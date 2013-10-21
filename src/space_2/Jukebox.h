#pragma once
#include "Resource.h"
#include "Clock.h"
#include "JukeboxMusic.h"


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

	void playSound(std::string p_sound, float p_volume = 1.0);
	void playSound(std::string p_sound, sf::Vector2f p_position, bool p_relativeToListener = false, float p_volume = 1.0);
	bool addSound(sf::Sound* p_sound);
	void removeSound(sf::Sound* p_sound);

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
	std::vector<sf::Sound*> mSounds;
	mks::Clock mSoundTimer;

	// Static
	static Jukebox* mInstance;

	// Methods
	void loadNewMusicPlaylist();
};

