#pragma once
#include "Resource.h"
#include "KeyValueFile.h"
#include "FlashingLightEffect.h"


class NpcType
{
public:
	// Enum 
	enum NpcTypeAlignment 
	{
		AlignmenGood = 0,
		AlignmenNeutral,
		AlignmenEvil
	};

	enum NpcTypeAggro
	{
		AggroAggressive = 0,
		AggroNeutral,
		AggroPassive
	};

	// Constructor - Destructor
	NpcType(KeyValueFile *p_config);
	~NpcType(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	sf::Color getColor();
	void setColor(sf::Color p_color);

	std::string getColorString();
	void setColorString(std::string p_color);

	FlashingLightEffect::LightColor getLightColor();
	void setLightColor(FlashingLightEffect::LightColor p_color);

	NpcTypeAlignment getAlignment();
	void setAlignment(NpcTypeAlignment p_alignment);

	NpcTypeAggro getAggro();
	void setAggro(NpcTypeAggro p_aggro);

	bool canAggro(NpcType* p_type);
	bool canRespond(NpcType* p_type);
	bool isAgressive();
	bool isPassive();

	// Methods
	void loadFromConfig(KeyValueFile *p_config);


private:
	// Attributs
	long mId;
	std::string mName;
	sf::Color mColor;
	std::string mColorString;
	FlashingLightEffect::LightColor mLightColor;

	NpcTypeAlignment mAlignment;
	NpcTypeAggro mAggro;
};

