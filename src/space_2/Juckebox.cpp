#include <fstream>
#include <string>
#include <sstream>
#include "Juckebox.h"
#include "Resource.h"
#include "Option.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Juckebox::Juckebox(void)
{
	// Load music into juckebox
	this->mPlaylistMusics.insert((std::pair<std::string, sf::Music*>(THEME_1_NAME, Resource::resource->getMusic(MUSIC_THEME_1))));
	this->mPlaylistMusics.insert((std::pair<std::string, sf::Music*>(THEME_2_NAME, Resource::resource->getMusic(MUSIC_THEME_2))));
	this->mPlaylistMusics.insert((std::pair<std::string, sf::Music*>(THEME_3_NAME, Resource::resource->getMusic(MUSIC_THEME_3))));
	this->mPlaylistMusics.insert((std::pair<std::string, sf::Music*>(THEME_4_NAME, Resource::resource->getMusic(MUSIC_THEME_4))));

	// Init with default
	this->mPlaylist		= NULL;
	this->mMusicPlayed	= false;

	for(int i = 0; i < JUCKEBOX_SIMULTANEOUS_SOUND; i++)
	{
		this->mSounds[i] = NULL;
	}
}

Juckebox::~Juckebox(void)
{
	// Remove playlist
	if(this->mPlaylist != NULL)
	{
		this->playlistStop();
		delete this->mPlaylist;
	}

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
sf::Music* Juckebox::getCurrentMusic()
{
	std::map<std::string, sf::Music*>::iterator it;
	it = this->mPlaylistMusics.find(this->mPlaylist[this->mCurrentMusicIndex]);

	return it->second;
}

std::string Juckebox::getCurrentMusicName()
{
	return this->mPlaylist[this->mCurrentMusicIndex];
}

std::string Juckebox::getCurrentMusicTimer()
{
	sf::Music *currentMusic;
	std::stringstream musicTimer;
	int musicOffset;
	int musicOffsetSecond;
	int musicOffsetMinute;
	int musicLenght;
	int musicLenghtSecond;
	int musicLenghtMinute;

	// Get current music infos
	currentMusic		= this->getCurrentMusic();
	musicOffset			= (int)currentMusic->getPlayingOffset().asSeconds();
	musicLenght			= (int)currentMusic->getDuration().asSeconds();

	musicOffsetMinute	= musicOffset / 60;
	musicOffsetSecond	= musicOffset - (musicOffsetMinute * 60);

	musicLenghtMinute	= musicLenght / 60;
	musicLenghtSecond	= musicLenght - (musicLenghtMinute * 60);
	
	// Set string
	musicTimer << musicOffsetMinute << ":";
	if(musicOffsetSecond < 10) musicTimer << "0";
	musicTimer << musicOffsetSecond;

	musicTimer << " / ";

	musicTimer << musicLenghtMinute << ":";
	if(musicLenghtSecond < 10) musicTimer << "0";
	musicTimer << musicLenghtSecond;

	// Return
	return musicTimer.str();
}

int Juckebox::getCurrentMusicIndex()
{
	return this->mCurrentMusicIndex;
}

void Juckebox::setCurrentMusicIndex( int p_index )
{
	// Check param
	if(p_index < 0)											// Go to last music if the user want the music befor first music
		p_index = this->mPlaylistMusics.size() - 1;
	else if(p_index >= (int)this->mPlaylistMusics.size())	// Go to first music when playlist arrive at end
		p_index = 0;

	// Set
	this->mCurrentMusicIndex = p_index;
}

int Juckebox::getRandomIndex()
{
	return rand() % this->mPlaylistMusics.size();
}


//*************************************************************
// Methode
//*************************************************************
void Juckebox::playlistPlay()
{
	this->getCurrentMusic()->play();
	this->mMusicPlayed = true;
}

void Juckebox::playlistPause()
{
	this->getCurrentMusic()->pause();
	this->mMusicPlayed = false;
}

void Juckebox::playlistStop()
{
	this->getCurrentMusic()->stop();
	this->mMusicPlayed = false;
}

void Juckebox::playlistNext()
{
	this->playlistStop();
	this->setCurrentMusicIndex(this->getCurrentMusicIndex() + 1);
	this->playlistPlay();
}

void Juckebox::playlistPrevious()
{
	this->playlistStop();
	this->setCurrentMusicIndex(this->getCurrentMusicIndex() - 1);
	this->playlistPlay();
}

void Juckebox::playlistSetOffset( int p_offsetPercent )
{
	// Calculate offset
	float offset		= this->getCurrentMusic()->getDuration().asMilliseconds() * ((float)p_offsetPercent / 100.f);
	sf::Time offsetTime = sf::milliseconds(offset);

	// Set offset
	this->getCurrentMusic()->setPlayingOffset(offsetTime);
}

void Juckebox::playlistLaunch()
{
	// Delete playlist if exist
	if(this->mPlaylist != NULL)
		delete this->mPlaylist;

	// Set playlist
	this->mPlaylist = new std::string[this->mPlaylistMusics.size()];

	for(unsigned int i = 0; i < this->mPlaylistMusics.size(); i++)
	{
		this->mPlaylist[i] = "";
	}

	for( std::map<std::string, sf::Music*>::iterator it = this->mPlaylistMusics.begin() ; it != this->mPlaylistMusics.end(); it++ )
	{
		int index;

		do 
		{
			index = this->getRandomIndex();
		} while (this->mPlaylist[index] != "");

		this->mPlaylist[index] = it->first;
	}

	// Init currentMusic
	this->setCurrentMusicIndex(0);

	// Set volume
	this->playlistUpdateVolume();

	// Play
	this->playlistPlay();
}

void Juckebox::playlistUpdate()
{
	// Manage Event

	// Manage playlist
	if(mMusicPlayed)
	{
		if(this->getCurrentMusic()->getStatus() == sf::Music::Status::Stopped)
		{
			this->mTimeBeforeNextMusic = rand() % (JUCKEBOX_TIMEBEFORENEXT_MAX - JUCKEBOX_TIMEBEFORENEXT_MIN) + JUCKEBOX_TIMEBEFORENEXT_MIN;
			this->mPlaylistTimer.restart();
			this->playlistStop();
		}
	}
	else
	{
		if(this->mPlaylistTimer.getElapsedTimeAsSeconds() > this->mTimeBeforeNextMusic)	
		{
			this->playlistNext();
		}
	}	
}

void Juckebox::playlistUpdateVolume()
{
	// Set new volume on each music
	for( std::map<std::string, sf::Music*>::iterator it = this->mPlaylistMusics.begin() ; it != this->mPlaylistMusics.end(); it++ )
	{
		(*it).second->setVolume((float)Option::option->getAppSoundMusic());
	}
}

void Juckebox::soundPlay( sf::SoundBuffer *p_mySoundBuffer, int p_amplifier )
{
	sf::Sound *mySound = new sf::Sound;	

	mySound->setBuffer(*p_mySoundBuffer);
	mySound->setVolume(Option::option->getAppSoundAmbient() * ((float)p_amplifier / 100.f));
	
	if(this->soundInsert(mySound))
		mySound->play();
	else
		delete mySound;
}

void Juckebox::soundPlay( std::string p_soundKey, int p_amplifier )
{
	this->soundPlay(Resource::resource->getBuffer(p_soundKey), p_amplifier);
}

void Juckebox::soundUpdate()
{
	if(this->mSoundTimer.getElapsedTimeAsSeconds() > (1.f / JUCKEBOX_SOUND_UPDATE_FREQ))
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

bool Juckebox::soundInsert( sf::Sound *mySound )
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

bool Juckebox::soundRemove( sf::Sound *mySound )
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

void Juckebox::update()
{
	this->playlistUpdate();
	this->soundUpdate();
}

