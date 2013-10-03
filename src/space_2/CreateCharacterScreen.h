#pragma once
#include "BaseScreen.h"
#include "RaceView.h"
#include "JobView.h"
#include "Character.h"
#include "SkillCharacterView.h"
#include "Button.h"
#include "FieldSet.h"
#include "TextBox.h"
#include "ImageGIF.h"
#include "TextField.h"
#include "TextField.h"
#include "SelectableGroup.h"

// Define
#define CREATESCREEN_VIEW_RACE_COUNT				2
#define CREATESCREEN_VIEW_JOB_COUNT					4

class CreateCharacterScreen: public BaseScreen
{
public:
	// Constructor - Destructor
	CreateCharacterScreen(void);
	~CreateCharacterScreen(void);
	void releaseAvatars();

	// Methods
	void reset();
	bool launch();
	void update();
	void updatePosition();
	void update(sf::Event p_event);
	void updateCreateButton();
	void draw();
	void launchBack();
	void launchCreate();
	void createCharacter();
	void notifyRaceSelectedChange();
	void notifyAvatarSelectedChange();
	void notifyJobSelectedChange();
	void selectPreviousAvatar();
	void selectNextAvatar();


private:
	// Attributs
	Character* mCharacter;
	bool mCharacterCreated;
	Button mButtonBack;
	Button mButtonCreate;
	FieldSet mFieldsetCreate;
	FieldSet mFieldsetInfo;
	ImageGIF *mGIFLoading;
	sf::Thread *mCreateCharacterThread;

	// Avatar
	TextBox mTBAvatar;
	Button mButtonAvatarPrevious;
	Button mButtonAvatarNext;
	int mAvatarSelected;
	int mAvatarCount;
	sf::Sprite **mAvatars;
	sf::RectangleShape mAvatarLeftOverlay;
	sf::RectangleShape mAvatarRightOverlay;

	// Name
	TextBox mTBName;
	TextField mTFName;

	// Race
	TextBox mTBRace;
	RaceView *mViewRace[CREATESCREEN_VIEW_RACE_COUNT];
	SelectableGroup mViewRaceGroup;

	// Job
	TextBox mTBJob;
	JobView *mViewJob[CREATESCREEN_VIEW_JOB_COUNT];
	SelectableGroup mViewJobGroup;

	// Skill
	TextBox mTBSkill;
	TextBox mTBSkillPointRemaining;
	SkillCharacterView *mViewSkill[CHARACTER_SKILL_COUNT];

	// Getters - Setters
	int getAvatarSelected();
	void setAvatarSelected(int index);
};

