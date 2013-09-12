#include "Internationalisation.h"
#include "KeyValueFile.h"
#include "Option.h"
#include "Tools.h"

//*************************************************************
// Define
//*************************************************************
#define FILE_PATH			"string/"
#define FILE_BASE_NAME		"string"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Internationalisation::Internationalisation(void)
{
	std::string nameFile = FILE_BASE_NAME;
	nameFile.append("-");
	nameFile.append(Option::option->getAppLanguage());

	if(Tools::isFileExist(nameFile))
		this->mBundle = new KeyValueFile(FILE_PATH + nameFile, nameFile, true);
	else
		this->mBundle = new KeyValueFile((FILE_PATH FILE_BASE_NAME), FILE_BASE_NAME, true);
}

Internationalisation::~Internationalisation(void)
{
	delete this->mBundle;
}


//*************************************************************
// Methode
//*************************************************************
std::string Internationalisation::getString( std::string key )
{
	return this->mBundle->getString(key);
}

