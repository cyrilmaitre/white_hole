#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

class ItemTier
{
public:
	// Constructor - Destructor
	ItemTier(KeyValueFile* p_config);
	~ItemTier(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	std::string getColorString();
	void setColorString(std::string p_color);

	sf::Color getColor();
	void setColor(sf::Color p_color);

	// Methode
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributes
	long mId;
	std::string mName;
	std::string mDescription;
	std::string mColorString;
	sf::Color mColor;
};

