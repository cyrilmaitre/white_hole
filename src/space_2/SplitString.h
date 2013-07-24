#pragma once
#include <iostream>
#include <sstream>

class SplitString
{
public:
	// Constructor - Destructor
	SplitString(std::string p_originalString, std::string p_delimeter);
	~SplitString(void);

	// Getters - Setters
	std::string getDelimeter();
	std::string getOriginalString();
	std::string getSplitString(int p_index);
	int getSplitCount();


private:
	// Atrributs
	std::string mDelimeter;
	std::string mOriginalString;
	std::string *mExplodedString;
	int mExplodedStringCount;

	// Methods
	void computeSplitCount();
	void splitOriginalString();
};

