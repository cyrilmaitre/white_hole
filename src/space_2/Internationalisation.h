#pragma once
#include <iostream>

class KeyValueFile;

class Internationalisation
{
public:
	// Constructor - Destructor
	Internationalisation(void);
	~Internationalisation(void);

	// Methods
	std::string getString(std::string key);


private:
	// Attributs
	KeyValueFile *mBundle;
};


