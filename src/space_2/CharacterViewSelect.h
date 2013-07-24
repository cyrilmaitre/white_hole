#pragma once
#include "Resource.h"
#include "Block.h"
#include "TextBox.h"
#include "Character.h"
#include "View.h"
#include "JobView.h"
#include "RaceView.h"
#include "ShipViewSmall.h"
#include "Image.h"


class CharacterViewSelect: public Block
{
public:
	// Constructor - Destructor
	CharacterViewSelect(Character *p_character);
	~CharacterViewSelect(void);

	// Getters - Setters
	Character* getCharacter();
	void setCharacter(Character *p_character);

	// Methods
	void notifyCharacterChanged();
	void notifyPositionChanged();
	void update();
	void updateText();
	void draw();


private:
	// Attributs
	Character *mCharacter;
	Image mAvatar;
	TextBox mTBNoCharacterSelected;
	TextBox mTBNameLabel;
	TextBox mTBNameText; 
	TextBox mTBLevelLabel;
	TextBox mTBLevelText;
	TextBox mTBCreditLabel;
	TextBox mTBCreditText;
	TextBox mTBJobLabel;
	TextBox mTBRaceLabel;
	TextBox mTBShipNameLabel;
	TextBox mTBShipNameText;
	TextBox mTBShipTypeLabel;
	TextBox mTBShipTypeText;
	TextBox mTBShipLevelLabel;
	TextBox mTBShipLevelText;
	JobView mJobView;
	RaceView mRaceview;
	View mCharacterView;
	ShipViewSmall mShipView;
};

