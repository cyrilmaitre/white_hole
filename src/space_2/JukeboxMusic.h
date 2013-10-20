#pragma once
#include "Resource.h"


class JukeboxMusic
{
public:
	// Constructor - Destructor
	JukeboxMusic(long p_id, std::string p_fileName, std::string p_name);
	~JukeboxMusic(void);

	// Getters - Setters
	long getId();
	std::string getFileName();
	std::string getName();


private:
	// Attributs
	long mId;
	std::string mFileName;
	std::string mName;
};

