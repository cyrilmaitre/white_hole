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
#define SOUND_POOL_SIZE						128		// sounds
#define SOUND_UPDATE_TICK					1.f		// sec
#define MUSICFOLDER_PATHNAME				"music/"
#define JUKEBOXCONFIG						"jukebox"
#define JUKEBOXCONFIG_PLAYLIST				"playlist"
#define AMBIANT_THEME_FILENAME				"ambiant-01.ogg"


//*************************************************************
// Init static
//*************************************************************
Jukebox* Jukebox::mInstance = NULL;
int sufflePlaylist(int i) { return Tools::random(0, 1000); }


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

	for(int i = 0; i < this->mSounds.size(); i++)
	{
		if(this->mSounds[i] != NULL)
			delete this->mSounds[i];
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

void Jukebox::playSound( std::string p_sound, float p_volume /*= 1.0*/ )
{
	this->playSound(p_sound, sf::Vector2f(0.0f, 0.0f), true, p_volume);
}

void Jukebox::playSound( std::string p_sound, sf::Vector2f p_position, bool p_relativeToListener /*= false*/, float p_volume /*= 1.0*/ )
{
	if(p_volume < 0.0f)
		p_volume = 0.0f;
	else if(p_volume > 1.0f)
		p_volume = 1.0f;

	sf::Sound* newSound = new sf::Sound();
	newSound->setBuffer(*Resource::resource->getSoundBuffer(p_sound));
	newSound->setVolume(Option::getInstance()->getAppSoundEffect() * p_volume);
	newSound->setRelativeToListener(p_relativeToListener);
	newSound->setPosition(p_position.x, 0.0f, p_position.y);

	if(this->addSound(newSound))
		newSound->play();
	else
		delete newSound;
}

bool Jukebox::addSound( sf::Sound* p_sound )
{
	if(this->mSounds.size() > SOUND_POOL_SIZE)
		return false;

	this->mSounds.push_back(p_sound);
	return true;
}

void Jukebox::removeSound( sf::Sound* p_sound )
{
	if(p_sound == NULL)
		return;

	for(int i = 0; i < this->mSounds.size(); i++)
	{
		if(this->mSounds[i] == p_sound)
		{
			delete this->mSounds[i];
			this->mSounds.erase(this->mSounds.begin() + i);
		}
	}
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
	if(this->mSoundTimer.getElapsedTimeAsSeconds() > SOUND_UPDATE_TICK)
	{
		for(int i = 0; i < this->mSounds.size(); i++)
		{
			if(this->mSounds[i] != NULL && this->mSounds[i]->getStatus() == sf::Sound::Status::Stopped)
			{
				this->removeSound(this->mSounds[i]);
				i--; // Stay on the same index
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



