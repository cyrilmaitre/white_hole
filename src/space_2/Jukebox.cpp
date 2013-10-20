#include <fstream>
#include <string>
#include <sstream>
#include "Jukebox.h"
#include "Resource.h"
#include "Option.h"
#include "SplitString.h"


//*************************************************************
// Define
//*************************************************************
#define MUSICFOLDER_PATHNAME				"music/"
#define JUKEBOXCONFIG						"jukebox"
#define JUKEBOXCONFIG_PLAYLIST				"playlist"
#define AMBIANT_THEME_FILENAME				"ambiant-01.ogg"
#define PLAYLIST_NEXTPLAY_TICJMIN			15.0f	// sec
#define PLAYLIST_NEXTPLAY_TICJMAX			45.0f	// sec


//*************************************************************
// Init static
//*************************************************************
Jukebox* Jukebox::mInstance = NULL;
int sufflePlaylist (int i) { return Tools::random(0, 1000); }


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Jukebox::Jukebox(void)
{
	// Load ambiant
	this->mMusicAmbiant = new sf::Music();
	this->mMusicAmbiant->openFromFile(MUSICFOLDER_PATHNAME AMBIANT_THEME_FILENAME);
	this->mMusicAmbiant->setLoop(true);

	// Load playlist
	KeyValueFile jukeboxConfig((MUSICFOLDER_PATHNAME JUKEBOXCONFIG), JUKEBOXCONFIG, true);
	std::string playlist = jukeboxConfig.getString(JUKEBOXCONFIG_PLAYLIST);
	SplitString playlistSplit(playlist, ";");
	for(int i = 0; i < playlistSplit.getSplitCount(); i++)
	{
		std::string currentSplit = playlistSplit.getSplitString(i);
		int startDelimeter = currentSplit.find("(");
		int endDemimeter = currentSplit.find(")");

		long id = i;
		std::string fileName = currentSplit.substr(0, startDelimeter);
		std::string name = currentSplit.substr(startDelimeter+1, endDemimeter-startDelimeter-1);

		this->mPlaylist.push_back(new JukeboxMusic(id, fileName, name));
	}

	this->mMusicPlaylist = new sf::Music();
	this->mMusicPlaylistIndex = -1;
	this->mPlaylistState = PlaylistState::Stopped;
	std::random_shuffle(this->mPlaylist.begin(), this->mPlaylist.end(), sufflePlaylist);

	// Init with default
	for(int i = 0; i < JUCKEBOX_SIMULTANEOUS_SOUND; i++)
	{
		this->mSounds[i] = NULL;
	}
}

Jukebox::~Jukebox(void)
{
	// Delete
	if(this->mMusicAmbiant != NULL)
	{
		if(this->mMusicAmbiant->getStatus() != sf::Music::Status::Stopped)
			this->mMusicAmbiant->stop();
		delete this->mMusicAmbiant;
	}

	if(this->mMusicPlaylist != NULL)
	{
		if(this->mMusicPlaylist->getStatus() != sf::Music::Status::Stopped)
			this->mMusicPlaylist->stop();
		delete this->mMusicPlaylist;
	}

	for(int i = 0; i < this->mPlaylist.size(); i++)
		delete this->mPlaylist[i];

	// Remove sound
	for(int i = 0; i < JUCKEBOX_SIMULTANEOUS_SOUND; i++)
	{
		if(this->mSounds[i] != NULL)
		{
			this->mSounds[i]->stop();
			delete this->mSounds[i];
		}
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::Music* Jukebox::getMusicAmbiant()
{
	return this->mMusicAmbiant;
}

sf::Music* Jukebox::getMusicPlaylist()
{
	return this->mMusicPlaylist;
}

sf::Time Jukebox::getPlaylistCurrentDuration()
{
	if(this->mMusicPlaylist != NULL)
		this->mMusicPlaylist->getDuration();
	else
		return sf::Time();
}

sf::Time Jukebox::getPlaylistCurrentOffset()
{
	if(this->mMusicPlaylist != NULL)
		this->mMusicPlaylist->getPlayingOffset();
	else
		return sf::Time();
}

Jukebox::PlaylistState Jukebox::getPlaylistState()
{
	return this->mPlaylistState;
}

void Jukebox::setListenerPosition( float p_x, float p_y )
{
	sf::Listener::setPosition(p_x, 0.f, p_y);
}


//*************************************************************
// Methode
//*************************************************************
Jukebox* Jukebox::getInstance()
{
	if(Jukebox::mInstance == NULL)
		Jukebox::mInstance = new Jukebox();
	return Jukebox::mInstance;
}

void Jukebox::destroyInstance()
{
	if(Jukebox::mInstance != NULL)
	{
		delete Jukebox::mInstance;
		Jukebox::mInstance = NULL;
	}
}

void Jukebox::playMusicAmbiant()
{
	if(this->mMusicAmbiant != NULL)
		this->mMusicAmbiant->play();
}

void Jukebox::pauseMusicAmbiant()
{
	if(this->mMusicAmbiant != NULL)
		this->mMusicAmbiant->pause();
}

void Jukebox::playPlaylist()
{
	if(this->mMusicPlaylist != NULL)
	{
		this->mMusicPlaylist->play();
		this->mPlaylistState = PlaylistState::Played;
	}
}

void Jukebox::pausePlaylist()
{
	if(this->mMusicPlaylist != NULL)
	{
		this->mMusicPlaylist->pause();
		this->mPlaylistState = PlaylistState::Paused;
	}
}

void Jukebox::stopPlaylist()
{
	if(this->mMusicPlaylist != NULL)
	{
		this->mMusicPlaylist->stop();
		this->mPlaylistState = PlaylistState::Stopped;
	}
}

void Jukebox::playlistNext()
{
	int newIndex = this->mMusicPlaylistIndex + 1;
	if(newIndex < 0 || newIndex >= this->mPlaylist.size())
		newIndex = 0;
	this->mMusicPlaylistIndex = newIndex;

	this->loadNewMusicPlaylist();
	this->playPlaylist();
}

void Jukebox::playlistPrevious()
{
	int newIndex = this->mMusicPlaylistIndex - 1;
	if(newIndex < 0 || newIndex >= this->mPlaylist.size())
		newIndex = this->mPlaylist.size() - 1;
	this->mMusicPlaylistIndex = newIndex;

	this->loadNewMusicPlaylist();
	this->playPlaylist();
}

void Jukebox::soundPlay( sf::SoundBuffer *p_mySoundBuffer, int p_amplifier )
{
	sf::Sound *mySound = new sf::Sound;	

	mySound->setBuffer(*p_mySoundBuffer);
	mySound->setVolume(Option::getInstance()->getAppSoundAmbient() * ((float)p_amplifier / 100.f));
	
	if(this->soundInsert(mySound))
		mySound->play();
	else
		delete mySound;
}

void Jukebox::soundPlay( std::string p_soundKey, int p_amplifier )
{
	this->soundPlay(Resource::resource->getSoundBuffer(p_soundKey), p_amplifier);
}

bool Jukebox::soundInsert( sf::Sound *mySound )
{
	int index = 0;

	while(this->mSounds[index] != NULL && index < JUCKEBOX_SIMULTANEOUS_SOUND)
		index ++;

	if(this->mSounds[index] == NULL)
	{
		this->mSounds[index] = mySound;

		return true;
	}
	else
	{
		return false;
	}
}

bool Jukebox::soundRemove( sf::Sound *mySound )
{
	int index = 0;

	while(this->mSounds[index] != mySound && index < JUCKEBOX_SIMULTANEOUS_SOUND)
		index++;

	if(this->mSounds[index] == mySound)
	{
		delete this->mSounds[index];
		this->mSounds[index] = NULL;

		return true;
	}

	return false;
}

void Jukebox::update()
{
	this->updatePlaylist();
	this->updateSound();
}

void Jukebox::updatePlaylist()
{
	if(this->mMusicPlaylist->getStatus() == sf::Music::Status::Stopped && this->mPlaylistState == Played)
		this->playlistNext();
}

void Jukebox::updateSound()
{
	if(this->mSoundTimer.getElapsedTimeAsSeconds() > JUCKEBOX_SOUND_UPDATE_TICK)
	{
		for(int i = 0; i < JUCKEBOX_SIMULTANEOUS_SOUND; i++)
		{
			if(this->mSounds[i] != NULL)
			{
				if(this->mSounds[i]->getStatus() == sf::Sound::Status::Stopped)
				{
					this->soundRemove(this->mSounds[i]);
				}
			}
		}

		this->mSoundTimer.restart();
	}
}

void Jukebox::loadNewMusicPlaylist()
{
	if(this->mMusicPlaylist->getStatus() != sf::Music::Status::Stopped)
		this->mMusicPlaylist->stop();
	this->mMusicPlaylist->openFromFile(MUSICFOLDER_PATHNAME + this->mPlaylist[this->mMusicPlaylistIndex]->getFileName());
}


