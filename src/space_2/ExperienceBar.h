#pragma once
#include "ProgressBar.h"
#include "Levelable.h"
#include "PopupBubble.h"


class ExperienceBar : public ProgressBar
{
public:
	// Enum
	enum ExperienceBarType 
	{
		TypeCharacter = 0,
		TypeCharacterShip
	};

	// Constructor - Destructor
	ExperienceBar(void);
	~ExperienceBar(void);

	// Getters - Setters
	Levelable* getLevelable();
	void setLevelable(Levelable* p_levelable);

	ExperienceBarType getType();
	void setType(ExperienceBarType p_type);

	// Methods
	void update(sf::Event myEvent);
	void update();
	void updatePub();

	
private:
	// Attributs
	Levelable* mLevelable;
	ExperienceBarType mType;
	PopupBubble* mPubExperience;
};

