#include <fstream>
#include <string>
#include <sstream>
#include "Jukebox.h"
#include "Resource.h"
#include "Option.h"


//*************************************************************
// Define
//*************************************************************
#define MUSICFOLDER_PATHNAME		"music/"
#define AMBIANT_THEME_FILENAME		"ambiant-01.ogg"


//*************************************************************
// Init static
//*************************************************************
Jukebox* Jukebox::mInstance = NULL;


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Jukebox::Jukebox(void)
{
	// Load ambiant
	this->mMusicAmbiant = new sf::Music();
	this->mMusicAmbiant->openFromFile(MUSICFOLDER_PATHNAME AMBIANT_THEME_FILENAME);
	this->mMusicAmbiant->setVolume(Option::getInstance()->getAppSoundAmbient());
	this->mMusicAmbiant->setLoop(true);

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

void Jukebox::setListenerPosition( double p_x, double p_y )
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
	this->mMusicAmbiant->play();
}

void Jukebox::pauseMusicAmbiant()
{
	this->mMusicAmbiant->pause();
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

void Jukebox::soundUpdate()
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
	this->soundUpdate();
}



