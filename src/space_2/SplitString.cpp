#include "SplitString.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
SplitString::SplitString( std::string p_originalString, std::string p_delimeter )
{
	this->mOriginalString = p_originalString;
	this->mDelimeter = p_delimeter;

	if(this->mOriginalString.size() > this->mDelimeter.size() && this->mOriginalString.substr(0, p_delimeter.size()) == p_delimeter)
		this->mOriginalString = this->mOriginalString.substr(p_delimeter.size(), this->mOriginalString.size() - p_delimeter.size());

	if(this->mOriginalString.size() > this->mDelimeter.size() && this->mOriginalString.substr(this->mOriginalString.length() - p_delimeter.size(), p_delimeter.size()) == p_delimeter)
		this->mOriginalString = this->mOriginalString.substr(0, this->mOriginalString.size() - p_delimeter.size());

	this->computeSplitCount();
	this->splitOriginalString();
}

SplitString::~SplitString(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string SplitString::getDelimeter()
{
	return this->mDelimeter;
}

std::string SplitString::getOriginalString()
{
	return this->mOriginalString;
}

std::string SplitString::getSplitString( int p_index )
{
	if(p_index >= this->getSplitCount())
		p_index = this->getSplitCount() - 1;

	return this->mExplodedString[p_index];
}

int SplitString::getSplitCount()
{
	return this->mExplodedStringCount;
}


//*************************************************************
// Methods
//*************************************************************
void SplitString::computeSplitCount()
{
	int count = 0;
	int lastIndexSeparator = 0;
	int indexSperator = -this->getDelimeter().size();
	do
	{
		indexSperator = this->getOriginalString().find(this->getDelimeter(), lastIndexSeparator + this->getDelimeter().size());
		lastIndexSeparator = indexSperator;
		count++;
	}while( indexSperator != std::string::npos);
	this->mExplodedStringCount = count;
}	

void SplitString::splitOriginalString()
{
	this->mExplodedString = new std::string[this->getSplitCount()];
	for(int i = 0; i < this->getSplitCount(); i++)
		this->mExplodedString[i] = "";

	int lastIndexSeparator = -1;
	for(int i = 0; i < this->getSplitCount(); i++)
	{
		int indexSperator = this->getOriginalString().find(this->getDelimeter(), lastIndexSeparator + 1);
		if(indexSperator != std::string::npos)
		{
			if(i == 0)
				this->mExplodedString[i] = this->getOriginalString().substr(lastIndexSeparator + 1, indexSperator - lastIndexSeparator - 1);	
			else
				this->mExplodedString[i] = this->getOriginalString().substr(lastIndexSeparator + this->getDelimeter().size(), indexSperator - lastIndexSeparator - this->getDelimeter().size());
			lastIndexSeparator = indexSperator;
		}
		else if(i == 0)
		{
			this->mExplodedString[i] = this->getOriginalString();
		}
		else if(i == this->getSplitCount() - 1)
		{		
			this->mExplodedString[i] = this->getOriginalString().substr(lastIndexSeparator + this->getDelimeter().size(), this->getOriginalString().size() - lastIndexSeparator + this->getDelimeter().size());
		}
	}
}	
