#include <fstream>
#include <string>
#include <sstream>
#include "KeyValueFile.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
KeyValueFile::KeyValueFile( std::string p_pathName, std::string p_fileName, bool p_loadFromFile, bool p_isReadOnly, std::string p_delimeter )
{
	// Init with param
	this->mPathName	= p_pathName;
	this->mFileName = p_fileName;
	this->mReadOnly	= p_isReadOnly;
	this->mDelimeter = p_delimeter;

	if(p_loadFromFile)
		this->loadFromFile();
}

KeyValueFile::~KeyValueFile(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string KeyValueFile::getPathName()
{
	return this->mPathName;
}

std::string KeyValueFile::getFileName()
{
	return this->mFileName;
}

std::string KeyValueFile::getString( std::string p_key )
{
	std::map<std::string, std::string>::iterator it;
	it = this->mKeyValue.find(p_key);

	if(it != this->mKeyValue.end())
		return it->second;
	else
		return "";
}

bool KeyValueFile::setString( std::string p_key, std::string p_value )
{
	bool keyExist = false;
	std::map<std::string, std::string>::iterator it;
	it = this->mKeyValue.find(p_key);

	if(it != this->mKeyValue.end())
		keyExist = true;

	if(keyExist)
		it->second = p_value;
	else
		this->mKeyValue.insert(std::pair<std::string, std::string>(p_key, p_value));

	return !keyExist;
}

long KeyValueFile::getLong( std::string p_key )
{
	std::string valueString = this->getString(p_key);

	if(valueString != "")
	{
		char * pEnd;
		return strtol(valueString.data(), &pEnd, 10);
	}
	else
	{
		return -1;
	}	
}

bool KeyValueFile::setLong( std::string p_key, long p_value )
{
	std::stringstream tmpString;
	tmpString << p_value;
	return this->setString(p_key, tmpString.str());
}

int KeyValueFile::getInt( std::string p_key )
{
	return (int)this->getLong(p_key);
}

bool KeyValueFile::setInt( std::string p_key, int p_value )
{
	return this->setLong(p_key, p_value);
}


double KeyValueFile::getDouble( std::string p_key )
{
	std::string valueString = this->getString(p_key);

	if(valueString != "")
	{
		char * pEnd;
		return strtod(valueString.data(), &pEnd);
	}
	else
	{
		return -1;
	}
}

bool KeyValueFile::setDouble( std::string p_key, double p_value )
{
	std::stringstream tmpString;
	tmpString << p_value;
	return this->setString(p_key, tmpString.str());
}

float KeyValueFile::getFloat( std::string p_key )
{
	return (float)this->getDouble(p_key);
}

bool KeyValueFile::setFloat( std::string p_key, float p_value )
{
	return this->setDouble(p_key, p_value);
}

bool KeyValueFile::getBool( std::string p_key )
{
	std::string tmpString = this->getString(p_key);
	if(tmpString == "true")
		return true;
	else
		return false;
}

void KeyValueFile::setBool( std::string p_key, bool p_value )
{
	if(p_value)
		this->setString(p_key, "true");
	else
		this->setString(p_key, "false");
}


//*************************************************************
// Méthode
//*************************************************************
bool KeyValueFile::has( std::string p_key )
{
	std::map<std::string, std::string>::iterator it;
	it = this->mKeyValue.find(p_key);
	return it != this->mKeyValue.end();
}

bool KeyValueFile::loadFromFile()
{
	std::ifstream file(this->mPathName);

	if (file.is_open())
	{
		while( file.good() )
		{
			std::string currentLine;
			std::string currentKey;
			std::string currentValue;
			int keyValueDelimeterIndex;

			// Get line
			getline(file, currentLine);

			// If not comment line
			if(currentLine.substr(0, 1) != "#")
			{
				// Get demimeter index
				keyValueDelimeterIndex = currentLine.find_first_of(this->mDelimeter);

				// Get key and value
				if(keyValueDelimeterIndex != std::string::npos)
				{
					currentKey		= currentLine.substr(0, keyValueDelimeterIndex);
					currentValue	= currentLine.substr(keyValueDelimeterIndex+1, currentLine.length());

					// Process key string
					int spaceIndex = currentKey.find_first_of(' ');
					if(spaceIndex != std::string::npos)
						currentKey.erase(spaceIndex, currentKey.length());

					// Process value string
					int firstCaracterIndex = 0;
					while(currentValue[firstCaracterIndex] == ' ' && firstCaracterIndex <= (int)currentValue.length())
						firstCaracterIndex++;
					currentValue.erase(0, firstCaracterIndex);

					// Save
					this->setString(currentKey, currentValue);
				}		
			}	
		}
		file.close();
		return true;
	}

	return false;
}

bool KeyValueFile::saveToFile()
{
	std::ofstream file(this->mPathName);

	if (file.is_open())
	{
		for( std::map<std::string, std::string>::iterator it = this->mKeyValue.begin() ; it != this->mKeyValue.end(); it++ )
		{
			file << (*it).first << this->mDelimeter << (*it).second << std::endl;
		}
		file.close();
		return true;
	}
	
	return false;
}









