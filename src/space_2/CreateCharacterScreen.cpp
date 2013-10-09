#include "CreateCharacterScreen.h"
#include "RaceFactory.h"
#include "SpriteParameterFactory.h"
#include "JobFactory.h"
#include "EventManager.h"
#include "Session.h"
#include "FactoryGet.h"
#include "ImageGIFFactory.h"
#include "NetworkDefine.h"
#include "ManagerConfig.h"
#include "PopupManager.h"
#include "CharacterBank.h"
#include "CharacterShip.h"
#include "Weapon.h"

using namespace std;
using namespace sf;


//*************************************************************
// Define
//*************************************************************
#define CREATESCREEN_CHARACTER_SKILLPOINT			15
#define CREATESCREEN_BUTTON_WIDTH					150
#define CREATESCREEN_BUTTON_HEIGHT					25
#define CREATESCREEN_BUTTON_BORDERSIZE				2
#define CREATESCREEN_BUTTONBACK_OFFSETY				10
#define CREATESCREEN_BUTTONRIGHT_OFFSETX			10
#define CREATESCREEN_FIELDSET_CREATE_WIDTH			1000
#define CREATESCREEN_FIELDSET_CREATE_HEIGHT			710
#define CREATESCREEN_FIELDSET_CREATE_BORDSIZE		2
#define CREATESCREEN_FIELDSET_CREATE_BACKCOLOR		sf::Color(128, 128, 128, 75)
#define CREATESCREEN_FIELDSET_CREATE_BORDCOLOR		sf::Color(128, 128, 128, 125)
#define CREATESCREEN_FIELDSET_INFO_OFFSETX			25
#define CREATESCREEN_FIELDSET_INFO_OFFSETY			60
#define CREATESCREEN_FIELDSET_INFO_WIDTH			500
#define CREATESCREEN_FIELDSET_INFO_HEIGHT			250
#define CREATESCREEN_FIELDSET_INFO_BORDSIZE			2
#define CREATESCREEN_FIELDSET_INFO_BORDCOLOR		sf::Color(192, 192, 192, 125)
#define CREATESCREEN_FIELDSET_INFO_BACKCOLOR		sf::Color(192, 192, 192, 75)
#define CREATESCREEN_TB_FIELD_COLOR					sf::Color(255, 106, 0)
#define CREATESCREEN_TB_FIELD_SIZE					ManagerConfig::FontSize::Huge
#define CREATESCREEN_TB_AVATAR_OFFSETX				25
#define CREATESCREEN_TB_AVATAR_OFFSETY				60
#define CREATESCREEN_AVATAR_BUTTON_WIDTH			16
#define CREATESCREEN_AVATAR_BUTTON_HEIGHT			16
#define CREATESCREEN_AVATAR_MAIN_WIDTH				96
#define CREATESCREEN_AVATAR_MAIN_HEIGHT				96
#define CREATESCREEN_AVATAR_SECOND_OFFSETX			20
#define CREATESCREEN_AVATAR_SECOND_SCALE			0.75
#define CREATESCREEN_AVATAR_SECOND_OVERLAY			sf::Color(48, 48, 48, 120)
#define CREATESCREEN_SECTION_AVATAR_OFFSETX			25
#define CREATESCREEN_SECTION_AVATAR_OFFSETY			15
#define CREATESCREEN_SECTION_AVATAR_WIDTH			375
#define CREATESCREEN_SECTION_AVATAR_HEIGHT			CREATESCREEN_AVATAR_MAIN_HEIGHT	
#define CREATESCREEN_NAME_LENGHT_MIN				1
#define CREATESCREEN_NAME_LENGHT_MAX				20
#define CREATESCREEN_TB_NAME_OFFSETX				25
#define CREATESCREEN_TB_NAME_OFFSETY				40
#define CREATESCREEN_TF_NAME_OFFSETX				25
#define CREATESCREEN_TF_NAME_OFFSETY				15
#define CREATESCREEN_TF_NAME_WIDTH					250
#define CREATESCREEN_TF_NAME_HEIGHT					20
#define CREATESCREEN_TB_RACE_OFFSETX				25
#define CREATESCREEN_TB_RACE_OFFSETY				40
#define CREATESCREEN_VIEW_RACE_OFFSETX_FIRST		25
#define CREATESCREEN_VIEW_RACE_OFFSETX				15
#define CREATESCREEN_VIEW_RACE_OFFSETY				15
#define CREATESCREEN_SECTION_JOB_OFFSETX			75
#define CREATESCREEN_VIEW_JOB_OFFSETX				15
#define CREATESCREEN_VIEW_JOB_OFFSETY				15
#define CREATESCREEN_TB_SKILL_OFFSETX				25
#define CREATESCREEN_TB_SKILL_OFFSETY				40
#define CREATESCREEN_TB_SKILLPTSREM_OFFSETX			5
#define CREATESCREEN_TB_SKILLPTSREM_OFFSETY			0
#define CREATESCREEN_TB_SKILLPTSREM_SIZE			ManagerConfig::FontSize::Small
#define CREATESCREEN_VIEW_SKILL_OFFSETX_FIRST		25
#define CREATESCREEN_VIEW_SKILL_OFFSETY_FIRST		15
#define CREATESCREEN_VIEW_SKILL_OFFSETX				15
#define CREATESCREEN_VIEW_SKILL_OFFSETY				15
#define CREATESCREEN_GIF_LOADING_OFFSETX			20
#define BUTTON_BORDERSIZE							2


//*************************************************************
// Constructor - Destructor
//*************************************************************
CreateCharacterScreen::CreateCharacterScreen(void)
{
	// Character
	this->mCharacter = NULL;

	// Init ptr
	this->mAvatars = NULL;
	this->mGIFLoading = NULL;
	this->mCreateCharacterThread = NULL;
	for(int i = 0; i < CREATESCREEN_VIEW_RACE_COUNT; i++)
		this->mViewRace[i] = NULL;
	for(int i = 0; i < CREATESCREEN_VIEW_JOB_COUNT; i++)
		this->mViewJob[i] = NULL;
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		this->mViewSkill[i] = NULL;

	// Create Ui
	this->mButtonBack.setSize(CREATESCREEN_BUTTON_WIDTH, CREATESCREEN_BUTTON_HEIGHT);
	this->mButtonBack.setTitle(Resource::resource->getBundle()->getString("back"));
	this->mButtonBack.setBorderSize(BUTTON_BORDERSIZE, true);
	
	this->mButtonCreate.setSize(CREATESCREEN_BUTTON_WIDTH, CREATESCREEN_BUTTON_HEIGHT);
	this->mButtonCreate.setTitle(Resource::resource->getBundle()->getString("createScreenButtonCreate"));
	this->mButtonCreate.setBorderSize(BUTTON_BORDERSIZE, true);
	this->mButtonCreate.setEnable(false);

	this->mButtonAvatarPrevious.setSize(CREATESCREEN_AVATAR_BUTTON_WIDTH, CREATESCREEN_AVATAR_BUTTON_HEIGHT);
	this->mButtonAvatarPrevious.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon16X16(true)->getSpritePtr(IC_16X16_LEFT));

	this->mButtonAvatarNext.setSize(CREATESCREEN_AVATAR_BUTTON_WIDTH, CREATESCREEN_AVATAR_BUTTON_HEIGHT);
	this->mButtonAvatarNext.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon16X16(true)->getSpritePtr(IC_16X16_RIGHT));

	this->mFieldsetCreate.setSize(CREATESCREEN_FIELDSET_CREATE_WIDTH, CREATESCREEN_FIELDSET_CREATE_HEIGHT);
	this->mFieldsetCreate.setTitle(Resource::resource->getBundle()->getString("createScreenTitle"));
	this->mFieldsetCreate.setBackgroundColor(CREATESCREEN_FIELDSET_CREATE_BACKCOLOR, true);
	this->mFieldsetCreate.setBorderColor(CREATESCREEN_FIELDSET_CREATE_BORDCOLOR, true);
	this->mFieldsetCreate.setBorderSize(CREATESCREEN_FIELDSET_CREATE_BORDSIZE, true);

	this->mFieldsetInfo.setSize(CREATESCREEN_FIELDSET_INFO_WIDTH, CREATESCREEN_FIELDSET_INFO_HEIGHT);
	this->mFieldsetInfo.setBackgroundColor(CREATESCREEN_FIELDSET_INFO_BACKCOLOR, true);
	this->mFieldsetInfo.setBorderColor(CREATESCREEN_FIELDSET_INFO_BORDCOLOR, true);
	this->mFieldsetInfo.setBorderSize(CREATESCREEN_FIELDSET_INFO_BORDSIZE, true);
	this->mFieldsetInfo.setVisible(false);

	this->mGIFLoading = ImageGIFFactory::getLoadingSquareCircle();
	this->mGIFLoading->setVisible(false);

	this->mTFName.setSize(CREATESCREEN_TF_NAME_WIDTH, CREATESCREEN_TF_NAME_HEIGHT);

	// Avatar
	this->mAvatarSelected = 0;
	this->mAvatarCount = 0;
	this->mTBAvatar.setFontSize(CREATESCREEN_TB_FIELD_SIZE);
	this->mTBAvatar.setFontColor(CREATESCREEN_TB_FIELD_COLOR);
	this->mTBAvatar.setText(Resource::resource->getBundle()->getString("createScreenAvatar"));

	this->mAvatarLeftOverlay.setFillColor(CREATESCREEN_AVATAR_SECOND_OVERLAY);
	this->mAvatarLeftOverlay.setSize(sf::Vector2f(CREATESCREEN_AVATAR_MAIN_WIDTH * CREATESCREEN_AVATAR_SECOND_SCALE, CREATESCREEN_AVATAR_MAIN_HEIGHT * CREATESCREEN_AVATAR_SECOND_SCALE));
	this->mAvatarRightOverlay.setFillColor(CREATESCREEN_AVATAR_SECOND_OVERLAY);
	this->mAvatarRightOverlay.setSize(sf::Vector2f(CREATESCREEN_AVATAR_MAIN_WIDTH * CREATESCREEN_AVATAR_SECOND_SCALE, CREATESCREEN_AVATAR_MAIN_HEIGHT * CREATESCREEN_AVATAR_SECOND_SCALE));

	// Name
	this->mTBName.setFontSize(CREATESCREEN_TB_FIELD_SIZE);
	this->mTBName.setFontColor(CREATESCREEN_TB_FIELD_COLOR);
	this->mTBName.setText(Resource::resource->getBundle()->getString("createScreenName"));

	// Race
	this->mTBRace.setFontSize(CREATESCREEN_TB_FIELD_SIZE);
	this->mTBRace.setFontColor(CREATESCREEN_TB_FIELD_COLOR);
	this->mTBRace.setText(Resource::resource->getBundle()->getString("createScreenRace"));

	this->mViewRace[0] = new RaceView(FactoryGet::getRaceFactory()->getRaceHuman(), 0, 0);
	this->mViewRace[1] = new RaceView(FactoryGet::getRaceFactory()->getRaceAndroid(), 0, 0);
	for(int i = 0; i < CREATESCREEN_VIEW_RACE_COUNT; i++)
		this->mViewRace[i]->setSelectable(true);
	for(int i = 0; i < CREATESCREEN_VIEW_RACE_COUNT; i++)
		this->mViewRaceGroup.addSelectable(this->mViewRace[i]);
	this->notifyRaceSelectedChange();

	// Job
	this->mTBJob.setFontSize(CREATESCREEN_TB_FIELD_SIZE);
	this->mTBJob.setFontColor(CREATESCREEN_TB_FIELD_COLOR);
	this->mTBJob.setText(Resource::resource->getBundle()->getString("createScreenJob"));
	this->mViewJob[0] = new JobView(FactoryGet::getJobFactory()->getJobMercenary(), 0, 0);
	this->mViewJob[1] = new JobView(FactoryGet::getJobFactory()->getJobIndustrialist(), 0, 0);
	this->mViewJob[2] = new JobView(FactoryGet::getJobFactory()->getJobTrader(), 0, 0);
	this->mViewJob[3] = new JobView(FactoryGet::getJobFactory()->getJobBuilder(), 0, 0);
	for(int i = 0; i < CREATESCREEN_VIEW_JOB_COUNT; i++)
		this->mViewJob[i]->setSelectable(true);
	for(int i = 0; i < CREATESCREEN_VIEW_JOB_COUNT; i++)
		this->mViewJobGroup.addSelectable(this->mViewJob[i]);

	// Skill
	this->mTBSkill.setFontSize(CREATESCREEN_TB_FIELD_SIZE);
	this->mTBSkill.setFontColor(CREATESCREEN_TB_FIELD_COLOR);
	this->mTBSkill.setText(Resource::resource->getBundle()->getString("createScreenSkills"));
	this->mTBSkillPointRemaining.setFontSize(CREATESCREEN_TB_SKILLPTSREM_SIZE);
	this->mTBSkillPointRemaining.setFontColor(CREATESCREEN_TB_FIELD_COLOR);
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		this->mViewSkill[i] = new SkillCharacterView();

	// Set content view
	this->mButtonBack.setView(this->mScreenView);
	this->mButtonCreate.setView(this->mScreenView);
	this->mButtonAvatarPrevious.setView(this->mScreenView);
	this->mButtonAvatarNext.setView(this->mScreenView);
	this->mFieldsetCreate.setView(this->mScreenView);
	this->mFieldsetInfo.setView(this->mScreenView);
	this->mGIFLoading->setView(this->mScreenView);
	this->mTBAvatar.setView(this->mScreenView);
	this->mTBName.setView(this->mScreenView);
	this->mTFName.setView(this->mScreenView);
	this->mTBRace.setView(this->mScreenView);
	for(int i = 0; i < CREATESCREEN_VIEW_RACE_COUNT; i++)
		this->mViewRace[i]->setView(this->mScreenView);
	this->mTBJob.setView(this->mScreenView);
	for(int i = 0; i < CREATESCREEN_VIEW_JOB_COUNT; i++)
		this->mViewJob[i]->setView(this->mScreenView);
	this->mTBSkill.setView(this->mScreenView);
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		this->mViewSkill[i]->setView(this->mScreenView);
}

CreateCharacterScreen::~CreateCharacterScreen(void)
{
	if(this->mGIFLoading != NULL)
		delete this->mGIFLoading;

	for(int i = 0; i < CREATESCREEN_VIEW_RACE_COUNT; i++)
	{
		if(this->mViewRace[i] != NULL)
			delete this->mViewRace[i];
	}

	this->releaseAvatars();

	for(int i = 0; i < CREATESCREEN_VIEW_JOB_COUNT; i++)
	{
		if(this->mViewJob[i] != NULL)
			delete this->mViewJob[i];
	}

	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		if(this->mViewSkill[i] != NULL)
			delete this->mViewSkill[i];

	if(this->mCreateCharacterThread != NULL)
		delete this->mCreateCharacterThread;

	if(this->mCharacter != NULL)
		delete this->mCharacter;
}

void CreateCharacterScreen::releaseAvatars()
{
	if(this->mAvatars != NULL)
	{
		for(int i = 0; i < this->mAvatarCount; i++)
		{
			if(this->mAvatars[i] != NULL)
				delete this->mAvatars[i];
		}
		delete this->mAvatars;
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
int CreateCharacterScreen::getAvatarSelected()
{
	return this->mAvatarSelected;
}

void CreateCharacterScreen::setAvatarSelected( int index )
{
	if(index < 0)
		index = 0;
	else if(index >= this->mAvatarCount)
		index = this->mAvatarCount - 1;

	this->mAvatarSelected = index;
	this->notifyAvatarSelectedChange();
}


//*************************************************************
// Methods
//*************************************************************
void CreateCharacterScreen::reset()
{
	if(this->mCharacter != NULL)
		delete this->mCharacter;

	this->mCharacter = new Character();
	this->mCharacter->createBase();
	this->mCharacter->setRace(((RaceView*)this->mViewRaceGroup.getSelection())->getRace());
	this->mCharacter->setJob(((JobView*)this->mViewJobGroup.getSelection())->getJob());
	this->mCharacter->setSkillPoints(CREATESCREEN_CHARACTER_SKILLPOINT);
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		this->mViewSkill[i]->setSkillCharacter(this->mCharacter->getSkillCharacterByIndex(i));

	this->mTFName.setValue("");
	this->setAvatarSelected(0);
	this->mViewRaceGroup.selectFirst();
	this->mViewJobGroup.selectFirst();

}

bool CreateCharacterScreen::launch()
{
	this->reset();
	this->mRunning = true;
	this->mCharacterCreated = false;
	this->notifyAppSizeChanged();
	while(Resource::resource->getApp()->isOpen() && Resource::resource->isAppRunning() && this->mRunning)
	{
		// Update
		this->update();

		// Update event
		if(Resource::resource->getApp()->pollEvent(this->mEvent))
		{
			if( this->mEvent.type == Event::Closed)
				Resource::resource->setAppRunning(false);

			if( this->mEvent.type == sf::Event::Resized)
			{
				Resource::resource->resizeAllView();
				this->notifyAppSizeChanged();
			}

			this->update(this->mEvent);
		}

		// Draw
		this->draw();
	}
	return this->mCharacterCreated;
}

void CreateCharacterScreen::update()
{
	BaseScreen::update();
	this->mGIFLoading->update();
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		this->mViewSkill[i]->update();

	this->updateCreateButton();
	this->mTBSkillPointRemaining.setText("(" + Resource::resource->getBundle()->getString("createScreenSkillsPtsRemaining") + " : " + Tools::buildStringWithInt(this->mCharacter->getSkillPoints()) + ")");
}

void CreateCharacterScreen::updatePosition()
{
	BaseScreen::updatePosition();

	// Update fieldset Create
	this->mFieldsetCreate.setX((int)((Resource::resource->getViewUi()->getSize().x - this->mFieldsetCreate.getWidth()) / 2));
	this->mFieldsetCreate.setY((int)((Resource::resource->getViewUi()->getSize().y - BASESCREEN_OVERLAY_HEIGHT - this->mFieldsetCreate.getHeight()) / 2));

	// Fieldset info
	this->mFieldsetInfo.setX((int)(this->mFieldsetCreate.getWidth() - this->mFieldsetInfo.getWidth() - CREATESCREEN_FIELDSET_INFO_OFFSETX), &this->mFieldsetCreate);
	this->mFieldsetInfo.setY(CREATESCREEN_FIELDSET_INFO_OFFSETY, &this->mFieldsetCreate);

	// Avatar
	this->mTBAvatar.setX(CREATESCREEN_TB_AVATAR_OFFSETX, &this->mFieldsetCreate);
	this->mTBAvatar.setY(CREATESCREEN_TB_AVATAR_OFFSETY, &this->mFieldsetCreate);
	this->mButtonAvatarPrevious.setX(CREATESCREEN_SECTION_AVATAR_OFFSETX, &this->mFieldsetCreate);
	this->mButtonAvatarPrevious.setY(this->mTBAvatar.getY(&this->mFieldsetCreate) + this->mTBAvatar.getHeight() + CREATESCREEN_SECTION_AVATAR_OFFSETY + CREATESCREEN_SECTION_AVATAR_HEIGHT / 2 - this->mButtonAvatarPrevious.getHeight() / 2, &this->mFieldsetCreate);
	this->mButtonAvatarNext.setX(CREATESCREEN_SECTION_AVATAR_OFFSETX + CREATESCREEN_SECTION_AVATAR_WIDTH - this->mButtonAvatarNext.getWidth(), &this->mFieldsetCreate);
	this->mButtonAvatarNext.setY(this->mTBAvatar.getY(&this->mFieldsetCreate) + this->mTBAvatar.getHeight() + CREATESCREEN_SECTION_AVATAR_OFFSETY + CREATESCREEN_SECTION_AVATAR_HEIGHT / 2 - this->mButtonAvatarNext.getHeight() / 2, &this->mFieldsetCreate);
	this->notifyAvatarSelectedChange();

	// Name
	this->mTBName.setX(CREATESCREEN_TB_NAME_OFFSETX, &this->mFieldsetCreate);
	this->mTBName.setY(this->mTBAvatar.getY(&this->mFieldsetCreate) + this->mTBAvatar.getHeight() + CREATESCREEN_SECTION_AVATAR_OFFSETY + CREATESCREEN_SECTION_AVATAR_HEIGHT + CREATESCREEN_TB_NAME_OFFSETY, &this->mFieldsetCreate);
	this->mTFName.setX(CREATESCREEN_TF_NAME_OFFSETX, &this->mFieldsetCreate);
	this->mTFName.setY(this->mTBName.getY(&this->mFieldsetCreate) + this->mTBName.getHeight() + CREATESCREEN_TF_NAME_OFFSETY, &this->mFieldsetCreate);

	// Race
	this->mTBRace.setX(CREATESCREEN_TB_RACE_OFFSETX, &this->mFieldsetCreate);
	this->mTBRace.setY(this->mTFName.getY(&this->mFieldsetCreate) + this->mTFName.getHeight() + CREATESCREEN_TB_RACE_OFFSETY, &this->mFieldsetCreate);

	int viewRaceY = this->mTBRace.getY(&this->mFieldsetCreate) + this->mTBRace.getHeight() + CREATESCREEN_VIEW_RACE_OFFSETY;
	this->mViewRace[0]->setX(CREATESCREEN_VIEW_RACE_OFFSETX_FIRST, &this->mFieldsetCreate);
	this->mViewRace[0]->setY(viewRaceY, &this->mFieldsetCreate);
	for(int i = 1; i < CREATESCREEN_VIEW_RACE_COUNT; i++)
	{
		this->mViewRace[i]->setX(this->mViewRace[i-1]->getX(&this->mFieldsetCreate) + this->mViewRace[i-1]->getWidth() + CREATESCREEN_VIEW_RACE_OFFSETX, &this->mFieldsetCreate);
		this->mViewRace[i]->setY(viewRaceY, &this->mFieldsetCreate);
	}

	// Job
	int jobOffsetX = this->mViewRace[CREATESCREEN_VIEW_RACE_COUNT - 1]->getX() + this->mViewRace[CREATESCREEN_VIEW_RACE_COUNT - 1]->getWidth() + CREATESCREEN_SECTION_JOB_OFFSETX;
	this->mTBJob.setX(jobOffsetX);
	this->mTBJob.setY(this->mTBRace.getY());

	int viewJobY = this->mTBJob.getY(&this->mFieldsetCreate) + this->mTBJob.getHeight() + CREATESCREEN_VIEW_JOB_OFFSETY;
	this->mViewJob[0]->setX(this->mTBJob.getX());
	this->mViewJob[0]->setY(viewJobY, &this->mFieldsetCreate);
	for(int i = 1; i < CREATESCREEN_VIEW_JOB_COUNT; i++)
	{
		this->mViewJob[i]->setX(this->mViewJob[i-1]->getX(&this->mFieldsetCreate) + this->mViewJob[i-1]->getWidth() + CREATESCREEN_VIEW_JOB_OFFSETX, &this->mFieldsetCreate);
		this->mViewJob[i]->setY(viewJobY, &this->mFieldsetCreate);
	}

	// Skill
	this->mTBSkill.setX(CREATESCREEN_TB_SKILL_OFFSETX, &this->mFieldsetCreate);
	this->mTBSkill.setY(this->mViewRace[0]->getY() + this->mViewRace[0]->getHeight() + CREATESCREEN_TB_SKILL_OFFSETY );
		
	this->mTBSkillPointRemaining.setX(this->mTBSkill.getX() + this->mTBSkill.getWidth() + CREATESCREEN_TB_SKILLPTSREM_OFFSETX);
	this->mTBSkillPointRemaining.setY(this->mTBSkill.getY() + this->mTBSkill.getHeight() - this->mTBSkillPointRemaining.getHeight() + CREATESCREEN_TB_SKILLPTSREM_OFFSETY);
	int viewSkillWidth = this->mViewSkill[0]->getWidth();
	int viewSkillHeight = this->mViewSkill[0]->getHeight();
	for(int i = 0; i < CHARACTER_SKILL_COUNT / 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			int index = i * 3 + j;
			int positionX = CREATESCREEN_VIEW_SKILL_OFFSETX_FIRST + (viewSkillWidth + CREATESCREEN_VIEW_SKILL_OFFSETX) * i;
			int positionY = this->mTBSkill.getY() + this->mTBSkill.getHeight() + CREATESCREEN_VIEW_SKILL_OFFSETY_FIRST + (viewSkillHeight + CREATESCREEN_VIEW_SKILL_OFFSETY) * j;
			this->mViewSkill[index]->setX(positionX, &this->mFieldsetCreate);
			this->mViewSkill[index]->setY(positionY);
		}
	}

	// Button
	this->mButtonCreate.setX((int)(Resource::resource->getViewUi()->getSize().x / 2 - this->mButtonCreate.getWidth() / 2 - this->mButtonCreate.getHeight()));
	this->mButtonCreate.setY((int)(Resource::resource->getViewUi()->getSize().y - (BASESCREEN_OVERLAY_HEIGHT / 2)));
	this->mButtonBack.setX((int)Resource::resource->getViewUi()->getSize().x - this->mButtonBack.getWidth() - CREATESCREEN_BUTTONRIGHT_OFFSETX);
	this->mButtonBack.setY((int)Resource::resource->getViewUi()->getSize().y - this->mButtonBack.getHeight() - CREATESCREEN_BUTTONBACK_OFFSETY);

	// Gif loading
	this->mGIFLoading->setX(this->mButtonCreate.getX() + this->mButtonCreate.getWidth() + CREATESCREEN_GIF_LOADING_OFFSETX);
	this->mGIFLoading->setY(this->mButtonCreate.getY() - (15 - (this->mButtonCreate.getHeight() / 2)));
}

void CreateCharacterScreen::update( sf::Event p_event )
{
	this->mButtonBack.update(p_event);
	this->mButtonCreate.update(p_event);
	this->mButtonAvatarNext.update(p_event);
	this->mButtonAvatarPrevious.update(p_event);
	this->mTFName.update(p_event);

	// Update Race
	for(int i = 0; i < CREATESCREEN_VIEW_RACE_COUNT; i++)
		this->mViewRace[i]->update(p_event);

	// Update Job
	for(int i = 0; i < CREATESCREEN_VIEW_JOB_COUNT; i++)
		this->mViewJob[i]->update(p_event);

	// Update Skills
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		this->mViewSkill[i]->update(p_event);

	// Actions
	if(this->mButtonCreate.isClicked())
		this->launchCreate();

	if(this->mButtonBack.isClicked())
		this->launchBack();

	if(this->mButtonAvatarPrevious.isClicked())
		this->selectPreviousAvatar();

	if(this->mButtonAvatarNext.isClicked())
		this->selectNextAvatar();

	if(this->mViewRaceGroup.isSelectionChanged())
		this->notifyRaceSelectedChange();

	if(this->mViewJobGroup.isSelectionChanged())
		this->notifyJobSelectedChange();
}

void CreateCharacterScreen::updateCreateButton()
{
	bool nameValid = this->mTFName.getValue().size() >= CREATESCREEN_NAME_LENGHT_MIN && this->mTFName.getValue().size() <= CREATESCREEN_NAME_LENGHT_MAX;
	bool skillValid = this->mCharacter->getSkillPoints() == 0;

	if(nameValid && skillValid)
		this->mButtonCreate.setEnable(true);
	else
		this->mButtonCreate.setEnable(false);
}

void CreateCharacterScreen::draw()
{
	// Draw base
	BaseScreen::draw();

	// Draw fieldset
	this->mFieldsetCreate.draw();
	this->mFieldsetInfo.draw();

	// Draw Avatar
	this->mTBAvatar.draw();
	this->mButtonAvatarPrevious.draw();
	this->mButtonAvatarNext.draw();
	Resource::resource->getApp()->draw(*this->mAvatars[this->mAvatarSelected]);
	if(this->mAvatarSelected > 0)
	{
		Resource::resource->getApp()->draw(*this->mAvatars[this->mAvatarSelected-1]);
		Resource::resource->getApp()->draw(this->mAvatarLeftOverlay);
	}

	if(this->mAvatarSelected < this->mAvatarCount - 1)
	{
		Resource::resource->getApp()->draw(*this->mAvatars[this->mAvatarSelected + 1]);
		Resource::resource->getApp()->draw(this->mAvatarRightOverlay);
	}
	
	// Draw Name
	this->mTBName.draw();
	this->mTFName.draw();
	
	// Draw Race
	this->mTBRace.draw();
	for(int i = 0; i < CREATESCREEN_VIEW_RACE_COUNT; i++)
		this->mViewRace[i]->draw();

	// Draw Job
	this->mTBJob.draw();
	for(int i = 0; i < CREATESCREEN_VIEW_JOB_COUNT; i++)
		this->mViewJob[i]->draw();

	// Draw Skills 
	this->mTBSkill.draw();
	this->mTBSkillPointRemaining.draw();
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		this->mViewSkill[i]->draw();

	// Draw button
	this->mButtonBack.draw();
	this->mButtonCreate.draw();

	// Draw Gif load
	this->mGIFLoading->draw();

	// Draw PopUp
	PopupManager::getInstance()->draw();

	Resource::resource->getApp()->display();
}

void CreateCharacterScreen::launchBack()
{
	this->mRunning = false;
}

void CreateCharacterScreen::launchCreate()
{
	if(this->mCreateCharacterThread != NULL)
		delete this->mCreateCharacterThread;

	this->mCreateCharacterThread = new Thread(&CreateCharacterScreen::createCharacter, this);
	this->mCreateCharacterThread->launch();
}

void CreateCharacterScreen::createCharacter()
{
	// Init
	this->mGIFLoading->setVisible(true);

	// Validate all skills pending points
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
	{
		this->mCharacter->getSkillCharacterByIndex(i)->validateLevelPending();
	}

	// Set AvatartId, Name...
	this->mCharacter->setAvatarId(((RaceView*)this->mViewRaceGroup.getSelection())->getRace()->getAvatarIndex(this->getAvatarSelected()));
	this->mCharacter->setName(this->mTFName.getValue());
	this->mCharacter->setUser(Session::getUser());

	// Send new character to server
	Json::StyledWriter writer;
	std::string jsonString = writer.write(this->mCharacter->saveToJson());
	sf::Http::Response response = Network::sendJsonRequest(Http::Request::Method::Post, NETWORK_HTTP_URI_CHARACTER_CREATE, jsonString);
	
	// Response
	Json::Reader reader;
	Json::Value responseJson;
	bool parseSuccessfull = reader.parse(response.getBody(), responseJson);
	if(parseSuccessfull && responseJson.get("created", "false").asString() == "true")
	{
		Character* newCharacter = new Character(Session::getUser(), responseJson.get("character", NULL));
		Session::getUser()->addCharacter(newCharacter);
		this->mCharacterCreated = true;
		this->launchBack();
	}
	else
	{
		// Display error message 
	}

	this->mGIFLoading->setVisible(false);
}

void CreateCharacterScreen::notifyRaceSelectedChange()
{
	if(this->mCharacter != NULL)
		this->mCharacter->setRace(((RaceView*)this->mViewRaceGroup.getSelection())->getRace());

	this->releaseAvatars();
	this->mAvatarCount = ((RaceView*)this->mViewRaceGroup.getSelection())->getRace()->getAvatarCount();
	this->mAvatars = new sf::Sprite*[this->mAvatarCount];
	for(int i = 0; i < this->mAvatarCount; i++)
	{
		this->mAvatars[i] = SpriteParameterFactory::getSpriteParameterAvatar(true)->getSpritePtr(((RaceView*)this->mViewRaceGroup.getSelection())->getRace()->getAvatarIndex(i), CREATESCREEN_AVATAR_MAIN_WIDTH, CREATESCREEN_AVATAR_MAIN_HEIGHT);
	}
	this->setAvatarSelected(0);

	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
	{
		if(this->mViewSkill[i] != NULL)
			this->mViewSkill[i]->notifySkillCharacterChanged();
	}
}

void CreateCharacterScreen::notifyJobSelectedChange()
{
	if(this->mCharacter != NULL)
		this->mCharacter->setJob(((JobView*)this->mViewJobGroup.getSelection())->getJob());

	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
	{
		if(this->mViewSkill[i] != NULL)
			this->mViewSkill[i]->notifySkillCharacterChanged();
	}
}

void CreateCharacterScreen::notifyAvatarSelectedChange()
{
	float avatarMainX = (float)(this->mFieldsetCreate.getX() + CREATESCREEN_SECTION_AVATAR_OFFSETX + (CREATESCREEN_SECTION_AVATAR_WIDTH - CREATESCREEN_AVATAR_MAIN_WIDTH) / 2);
	float avatarMainY = (float)(this->mTBAvatar.getY() + this->mTBAvatar.getHeight() + CREATESCREEN_SECTION_AVATAR_OFFSETY + (CREATESCREEN_SECTION_AVATAR_HEIGHT - CREATESCREEN_AVATAR_MAIN_WIDTH) / 2);
	float scaleMain = CREATESCREEN_AVATAR_MAIN_WIDTH / this->mAvatars[this->mAvatarSelected]->getLocalBounds().width;
	float scaleSecond = scaleMain * CREATESCREEN_AVATAR_SECOND_SCALE;
	this->mAvatars[this->mAvatarSelected]->setPosition(avatarMainX, avatarMainY);
	this->mAvatars[this->mAvatarSelected]->setScale(scaleMain, scaleMain);

	if(this->mAvatarSelected > 0)
	{
		float avatarLeftX = avatarMainX - CREATESCREEN_AVATAR_MAIN_WIDTH * CREATESCREEN_AVATAR_SECOND_SCALE - CREATESCREEN_AVATAR_SECOND_OFFSETX;
		float avatarLeftY = avatarMainY + (CREATESCREEN_AVATAR_MAIN_HEIGHT - CREATESCREEN_AVATAR_MAIN_HEIGHT * CREATESCREEN_AVATAR_SECOND_SCALE) / 2;
		this->mAvatars[this->mAvatarSelected - 1]->setPosition(avatarLeftX, avatarLeftY);
		this->mAvatars[this->mAvatarSelected - 1]->setScale(scaleSecond, scaleSecond);
		this->mAvatarLeftOverlay.setPosition(sf::Vector2f(avatarLeftX, avatarLeftY));
	}
	
	if(this->mAvatarSelected < this->mAvatarCount - 1)
	{
		float avatarRightX = avatarMainX + CREATESCREEN_AVATAR_MAIN_WIDTH + CREATESCREEN_AVATAR_SECOND_OFFSETX;
		float avatarRightY = avatarMainY + (CREATESCREEN_AVATAR_MAIN_HEIGHT - CREATESCREEN_AVATAR_MAIN_HEIGHT * CREATESCREEN_AVATAR_SECOND_SCALE) / 2;
		this->mAvatars[this->mAvatarSelected + 1]->setPosition(avatarRightX, avatarRightY);
		this->mAvatars[this->mAvatarSelected + 1]->setScale(scaleSecond, scaleSecond);
		this->mAvatarRightOverlay.setPosition(sf::Vector2f(avatarRightX, avatarRightY));
	}
}

void CreateCharacterScreen::selectPreviousAvatar()
{
	this->setAvatarSelected(this->getAvatarSelected() - 1);
	this->notifyAvatarSelectedChange();
}

void CreateCharacterScreen::selectNextAvatar()
{
	this->setAvatarSelected(this->getAvatarSelected() + 1);
	this->notifyAvatarSelectedChange();
}




