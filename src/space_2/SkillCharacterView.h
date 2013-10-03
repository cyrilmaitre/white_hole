#pragma once
#include "Resource.h"
#include "SkillCharacter.h"
#include "Block.h"
#include "TextBox.h"
#include "Button.h"
#include "PopupBubble.h"


class SkillCharacterView: public Block
{
public:
	// Constructor - Destructor
	SkillCharacterView(void);
	~SkillCharacterView(void);

	// Getters - Setter
	SkillCharacter* getSkillCharacter();
	void setSkillCharacter(SkillCharacter* p_skill);

	bool isEditable();
	void setEditable(bool p_editable);

	// Methods
	void notifyPositionChanged();
	void notifySkillCharacterChanged();

	void cancel();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void updateLevelDetail();
	void draw();


private:
	// Attributes
	SkillCharacter *mSkillCharacter;
	sf::Sprite *mSkillSprite;
	TextBox *mTBName;
	TextBox *mTBLevel;
	Button *mButtonInc;
	Button *mButtonDec;
	PopupBubble *mPUBLevel;
	bool mEditable;
};

