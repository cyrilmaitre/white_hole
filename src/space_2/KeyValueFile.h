#pragma once
#include <map>
#include <iostream>
#include <sstream>

// Define
#define DEFAULT_KEYVALUEFILE_DELIMETER	"="

class KeyValueFile
{
public:
	// Constructor - Destructor
	KeyValueFile(std::string p_fileName, 
				bool p_loadFromFile = false, 
				bool p_isReadOnly = false,
				std::string p_delimeter = DEFAULT_KEYVALUEFILE_DELIMETER);
	~KeyValueFile(void);

	// Getters - Setters
	std::string getString(std::string p_key);
	bool setString(std::string p_key, std::string p_value);

	long getLong(std::string p_key);
	bool setLong(std::string p_key, long p_value);
	int getInt(std::string p_key);
	bool setInt(std::string p_key, int p_value);

	double getDouble(std::string p_key);
	bool setDouble(std::string p_key, double p_value);
	float getFloat(std::string p_key);
	bool setFloat(std::string p_key, float p_value);

	bool getBool(std::string p_key);
	void setBool(std::string p_key, bool p_value);

	// Methode
	bool has(std::string p_key);
	bool loadFromFile();
	bool saveToFile();


private:
	std::string mFileName;
	bool mReadOnly;
	std::string mDelimeter;
	std::map<std::string, std::string> mKeyValue;
};

