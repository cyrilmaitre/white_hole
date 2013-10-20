#include "JukeboxMusic.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
JukeboxMusic::JukeboxMusic( long p_id, std::string p_fileName, std::string p_name )
{
	this->mId = p_id;
	this->mFileName = p_fileName;
	this->mName = p_name;
}

JukeboxMusic::~JukeboxMusic(void)
{
}


//*************************************************************
// Methods
//*************************************************************
long JukeboxMusic::getId()
{
	return this->mId;
}

std::string JukeboxMusic::getFileName()
{
	return this->mFileName;
}

std::string JukeboxMusic::getName()
{
	return this->mName;
}