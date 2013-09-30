#include "CharacterViewSelect.h"
#include "SpriteParameterFactory.h"
#include "CharacterShip.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define CHARACTERVIEW_SELECT_WIDTH							751			
#define CHARACTERVIEW_SELECT_HEIGHT							576	
#define CHARACTERVIEW_SELECT_BACK_COLOR						sf::Color(128, 128, 128, 75)
#define CHARACTERVIEW_SELECT_BORD_COLOR						sf::Color(128, 128, 128, 125)
#define CHARACTERVIEW_SELECT_BORD_SIZE						2
#define CHARACTERVIEW_SELECT_AVATAR_WIDTH					128
#define CHARACTERVIEW_SELECT_AVATAR_HEIGHT					128
#define CHARACTERVIEW_SELECT_AVATAR_OFFSETX					20
#define CHARACTERVIEW_SELECT_AVATAR_OFFSETY					20	
#define CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR				sf::Color(255, 106, 0)
#define CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE				ManagerConfig::FontSize::Large
#define CHARACTERVIEW_SELECT_TB_NAME_LABEL_OFFSETX			20
#define CHARACTERVIEW_SELECT_TB_NAME_LABEL_OFFSETY			20
#define CHARACTERVIEW_SELECT_TB_LEVEL_LABEL_OFFSETX			20	
#define CHARACTERVIEW_SELECT_TB_LEVEL_LABEL_OFFSETY			15
#define CHARACTERVIEW_SELECT_TB_CREDIT_LABEL_OFFSETX		20	
#define CHARACTERVIEW_SELECT_TB_CREDIT_LABEL_OFFSETY		15
#define CHARACTERVIEW_SELECT_TB_TEXT_OFFSETX				10
#define CHARACTERVIEW_SELECT_TB_TEXT_FONTCOLOR				sf::Color(195,195,195)
#define CHARACTERVIEW_SELECT_TB_TEXT_FONTSIZE				ManagerConfig::FontSize::Small
#define RACE_LABEL_OFFSETY									15
#define RACEVIEW_OFFSETY									10
#define JOB_LABEL_OFFSETX									80
#define JOB_LABEL_OFFSETY									15
#define JOBVIEW_OFFSETY										10
#define SHIPVIEW_OFFSETX									370
#define SHIPVIEW_OFFSETY									20
#define TBSHIP_NAMELABEL_OFFSETX							20
#define TBSHIP_NAMELABEL_OFFSETY							20
#define TBSHIP_TYPELABEL_OFFSETX							20
#define TBSHIP_TYPELABEL_OFFSETY							15
#define TBSHIP_LEVELLABEL_OFFSETX							20
#define TBSHIP_LEVELLABEL_OFFSETY							15
#define AVATAR_BACKGROUND_COLOR								sf::Color(128, 128, 128, 75)
#define AVATAR_BORDER_COLOR									sf::Color(128, 128, 128, 125)
#define AVATAR_BORDER_SIZE									2


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterViewSelect::CharacterViewSelect( Character *p_character )
{
	this->mCharacter = p_character;

	this->setSize(CHARACTERVIEW_SELECT_WIDTH, CHARACTERVIEW_SELECT_HEIGHT);
	this->setBackgroundColor(CHARACTERVIEW_SELECT_BACK_COLOR, true);
	this->setBorderColor(CHARACTERVIEW_SELECT_BORD_COLOR, true);
	this->setBorderSize(CHARACTERVIEW_SELECT_BORD_SIZE, true);

	this->mTBNameLabel.setFontColor(CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR);
	this->mTBNameLabel.setFontSize(CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE);
	this->mTBNameLabel.setText(Resource::resource->getBundle()->getString("characterNameLabel")+":");
	this->mTBLevelLabel.setFontColor(CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR);
	this->mTBLevelLabel.setFontSize(CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE);
	this->mTBLevelLabel.setText(Resource::resource->getBundle()->getString("characterLevelLabel")+":");
	this->mTBCreditLabel.setFontColor(CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR);
	this->mTBCreditLabel.setFontSize(CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE);
	this->mTBCreditLabel.setText(Resource::resource->getBundle()->getString("credit")+":");
	this->mTBRaceLabel.setFontColor(CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR);
	this->mTBRaceLabel.setFontSize(CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE);
	this->mTBRaceLabel.setText(Resource::resource->getBundle()->getString("race")+":");
	this->mTBJobLabel.setFontColor(CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR);
	this->mTBJobLabel.setFontSize(CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE);
	this->mTBJobLabel.setText(Resource::resource->getBundle()->getString("job")+":");
	this->mTBShipNameLabel.setFontColor(CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR);
	this->mTBShipNameLabel.setFontSize(CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE);
	this->mTBShipNameLabel.setText(Resource::resource->getBundle()->getString("name")+":");
	this->mTBShipTypeLabel.setFontColor(CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR);
	this->mTBShipTypeLabel.setFontSize(CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE);
	this->mTBShipTypeLabel.setText(Resource::resource->getBundle()->getString("type")+":");
	this->mTBShipLevelLabel.setFontColor(CHARACTERVIEW_SELECT_TB_LABEL_FONTCOLOR);
	this->mTBShipLevelLabel.setFontSize(CHARACTERVIEW_SELECT_TB_LABEL_FONTSIZE);
	this->mTBShipLevelLabel.setText(Resource::resource->getBundle()->getString("level")+":");

	this->mTBNameText.setFontColor(CHARACTERVIEW_SELECT_TB_TEXT_FONTCOLOR);
	this->mTBNameText.setFontSize(CHARACTERVIEW_SELECT_TB_TEXT_FONTSIZE);
	this->mTBLevelText.setFontColor(CHARACTERVIEW_SELECT_TB_TEXT_FONTCOLOR);
	this->mTBLevelText.setFontSize(CHARACTERVIEW_SELECT_TB_TEXT_FONTSIZE);
	this->mTBCreditText.setFontColor(CHARACTERVIEW_SELECT_TB_TEXT_FONTCOLOR);
	this->mTBCreditText.setFontSize(CHARACTERVIEW_SELECT_TB_TEXT_FONTSIZE);
	this->mTBShipNameText.setFontColor(CHARACTERVIEW_SELECT_TB_TEXT_FONTCOLOR);
	this->mTBShipNameText.setFontSize(CHARACTERVIEW_SELECT_TB_TEXT_FONTSIZE);
	this->mTBShipTypeText.setFontColor(CHARACTERVIEW_SELECT_TB_TEXT_FONTCOLOR);
	this->mTBShipTypeText.setFontSize(CHARACTERVIEW_SELECT_TB_TEXT_FONTSIZE);
	this->mTBShipLevelText.setFontColor(CHARACTERVIEW_SELECT_TB_TEXT_FONTCOLOR);
	this->mTBShipLevelText.setFontSize(CHARACTERVIEW_SELECT_TB_TEXT_FONTSIZE);

	this->mAvatar.setWidth(CHARACTERVIEW_SELECT_AVATAR_WIDTH);
	this->mAvatar.setHeight(CHARACTERVIEW_SELECT_AVATAR_HEIGHT);
	this->mAvatar.setBackgroundColor(AVATAR_BACKGROUND_COLOR, true);
	this->mAvatar.setBorderColor(AVATAR_BORDER_COLOR, true);
	this->mAvatar.setBorderSize(AVATAR_BORDER_SIZE, true);

	this->mTBNoCharacterSelected.setFontColor(CHARACTERVIEW_SELECT_TB_TEXT_FONTCOLOR);
	this->mTBNoCharacterSelected.setFontSize(CHARACTERVIEW_SELECT_TB_TEXT_FONTSIZE);
	this->mTBNoCharacterSelected.setText(Resource::resource->getBundle()->getString("selectScreenNoCharacterSelected"));

	this->mTBNameLabel.setView(&this->mCharacterView);
	this->mTBNameText.setView(&this->mCharacterView);
	this->mTBLevelLabel.setView(&this->mCharacterView);
	this->mTBLevelText.setView(&this->mCharacterView);

	this->notifyCharacterChanged();
	this->notifyPositionChanged();
}

CharacterViewSelect::~CharacterViewSelect(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* CharacterViewSelect::getCharacter()
{
	return this->mCharacter;
}

void CharacterViewSelect::setCharacter( Character *p_character )
{
	this->mCharacter = p_character;
	this->notifyCharacterChanged();
}


//*************************************************************
// Methods
//*************************************************************
void CharacterViewSelect::notifyCharacterChanged()
{
	if(this->getCharacter() != NULL)
	{
		this->mCharacterView.setVisible(true);
		this->mTBNoCharacterSelected.setVisible(false);

		this->mAvatar.setBackgroundImage(SpriteParameterFactory::getSpriteParameterAvatar()->getSpritePtr(this->mCharacter->getAvatarId(), CHARACTERVIEW_SELECT_AVATAR_WIDTH, CHARACTERVIEW_SELECT_AVATAR_HEIGHT));
		this->mJobView.setJob(this->getCharacter()->getJob());
		this->mRaceview.setRace(this->getCharacter()->getRace());
		this->mShipView.setShip((Ship*)this->getCharacter()->getShipPiloted());
		this->updateText();
	}
	else
	{
		this->mCharacterView.setVisible(false);
		this->mTBNoCharacterSelected.setVisible(true);
	}
	this->notifyPositionChanged();
}

void CharacterViewSelect::notifyPositionChanged()
{
	Block::notifyPositionChanged();

	if(this->mCharacter != NULL)
	{
		// Avatar
		this->mAvatar.setPosition(this->getX() + CHARACTERVIEW_SELECT_AVATAR_OFFSETX, this->getY() + CHARACTERVIEW_SELECT_AVATAR_OFFSETY);

		// Name
		this->mTBNameLabel.setX(this->mAvatar.getX() + this->mAvatar.getWidth() + CHARACTERVIEW_SELECT_TB_NAME_LABEL_OFFSETX);
		this->mTBNameLabel.setY(this->getY() + CHARACTERVIEW_SELECT_TB_NAME_LABEL_OFFSETY);
		this->mTBNameText.setX(this->mTBNameLabel.getX() + this->mTBNameLabel.getWidth() + CHARACTERVIEW_SELECT_TB_TEXT_OFFSETX);
		this->mTBNameText.setY(this->mTBNameLabel.getY() + (this->mTBNameLabel.getHeight() - this->mTBNameText.getHeight()));

		// Level
		this->mTBLevelLabel.setX(this->mAvatar.getX() + this->mAvatar.getWidth() + CHARACTERVIEW_SELECT_TB_LEVEL_LABEL_OFFSETX);
		this->mTBLevelLabel.setY(this->mTBNameLabel.getY() + this->mTBNameLabel.getHeight() + CHARACTERVIEW_SELECT_TB_LEVEL_LABEL_OFFSETY);
		this->mTBLevelText.setX(this->mTBLevelLabel.getX() + this->mTBLevelLabel.getWidth() + CHARACTERVIEW_SELECT_TB_TEXT_OFFSETX);
		this->mTBLevelText.setY(this->mTBLevelLabel.getY() + (this->mTBLevelLabel.getHeight() - this->mTBLevelText.getHeight()));

		// Credit
		this->mTBCreditLabel.setX(this->mAvatar.getX() + this->mAvatar.getWidth() + CHARACTERVIEW_SELECT_TB_CREDIT_LABEL_OFFSETX);
		this->mTBCreditLabel.setY(this->mTBLevelLabel.getY() + this->mTBCreditLabel.getHeight() + CHARACTERVIEW_SELECT_TB_CREDIT_LABEL_OFFSETY);
		this->mTBCreditText.setX(this->mTBCreditLabel.getX() + this->mTBCreditLabel.getWidth() + CHARACTERVIEW_SELECT_TB_TEXT_OFFSETX);
		this->mTBCreditText.setY(this->mTBCreditLabel.getY() + (this->mTBCreditLabel.getHeight() - this->mTBCreditText.getHeight()));

		// Race
		this->mTBRaceLabel.setX(this->mAvatar.getX());
		this->mTBRaceLabel.setY(this->mAvatar.getY() + this->mAvatar.getHeight() + RACE_LABEL_OFFSETY);
		this->mRaceview.setX(this->mTBRaceLabel.getX());
		this->mRaceview.setY(this->mTBRaceLabel.getY() + this->mTBRaceLabel.getHeight() + RACEVIEW_OFFSETY);

		// Job
		this->mTBJobLabel.setX(this->mTBRaceLabel.getX() + this->mTBRaceLabel.getWidth() + JOB_LABEL_OFFSETX);
		this->mTBJobLabel.setY(this->mAvatar.getY() + this->mAvatar.getHeight() + JOB_LABEL_OFFSETY);
		this->mJobView.setX(this->mTBJobLabel.getX());
		this->mJobView.setY(this->mTBJobLabel.getY() + this->mTBJobLabel.getHeight() + JOBVIEW_OFFSETY);

		// Ship
		this->mShipView.setPosition(this->getX() + SHIPVIEW_OFFSETX, this->getY() + SHIPVIEW_OFFSETY);

		this->mTBShipNameLabel.setPosition(	this->mShipView.getX() + this->mShipView.getWidth() + TBSHIP_NAMELABEL_OFFSETX, 
											this->getY() + TBSHIP_NAMELABEL_OFFSETY);
		this->mTBShipNameText.setPosition(	this->mTBShipNameLabel.getX() + this->mTBShipNameLabel.getWidth() + CHARACTERVIEW_SELECT_TB_TEXT_OFFSETX, 
											this->mTBShipNameLabel.getY() + (this->mTBShipNameLabel.getHeight() - this->mTBShipNameText.getHeight()));

		this->mTBShipTypeLabel.setPosition(	this->mShipView.getX() + this->mShipView.getWidth() + TBSHIP_TYPELABEL_OFFSETX, 
											this->mTBShipNameLabel.getY() + this->mTBShipNameLabel.getHeight() + TBSHIP_TYPELABEL_OFFSETY);
		this->mTBShipTypeText.setPosition(	this->mTBShipTypeLabel.getX() + this->mTBShipTypeLabel.getWidth() + CHARACTERVIEW_SELECT_TB_TEXT_OFFSETX,
											this->mTBShipTypeLabel.getY() + (this->mTBShipTypeLabel.getHeight() - this->mTBShipTypeText.getHeight()));

		this->mTBShipLevelLabel.setPosition(this->mShipView.getX() + this->mShipView.getWidth() + TBSHIP_LEVELLABEL_OFFSETX, 
											this->mTBShipTypeLabel.getY() + this->mTBShipTypeLabel.getHeight() + TBSHIP_LEVELLABEL_OFFSETY);
		this->mTBShipLevelText.setPosition(	this->mTBShipLevelLabel.getX() + this->mTBShipLevelLabel.getWidth() + CHARACTERVIEW_SELECT_TB_TEXT_OFFSETX,
											this->mTBShipLevelLabel.getY() + (this->mTBShipLevelLabel.getHeight() - this->mTBShipLevelText.getHeight()));
	}

	// No selected
	this->mTBNoCharacterSelected.setX(this->getX() + (this->getWidth() - this->mTBNoCharacterSelected.getWidth()) / 2);
	this->mTBNoCharacterSelected.setY(this->getY() + (this->getHeight() - this->mTBNoCharacterSelected.getHeight()) / 2);
}

void CharacterViewSelect::update()
{
	this->mShipView.update();
}

void CharacterViewSelect::updateText()
{
	if(this->getCharacter() != NULL)
	{
		this->mTBNameText.setText(this->getCharacter()->getName());
		this->mTBLevelText.setText(Tools::buildStringWithInt(this->getCharacter()->getLevel()));
		this->mTBCreditText.setText(Tools::formatNumber(this->getCharacter()->getCredit()));
		this->mTBShipNameText.setText(this->getCharacter()->getShipPiloted()->getShipModel()->getName());
		this->mTBShipTypeText.setText(this->getCharacter()->getShipPiloted()->getShipModel()->getItemType()->getName());
		this->mTBShipLevelText.setText(Tools::buildStringWithInt(this->getCharacter()->getShipPiloted()->getLevel()));
	}
}

void CharacterViewSelect::draw()
{
	// Draw UiBlock
	Block::draw();

	// Draw object
	if(this->getCharacter() != NULL)
	{
		this->mTBNameLabel.draw();
		this->mTBNameText.draw();
		this->mTBLevelLabel.draw();
		this->mTBLevelText.draw();
		this->mTBCreditLabel.draw();
		this->mTBCreditText.draw();
		this->mTBRaceLabel.draw();
		this->mTBJobLabel.draw();
		this->mJobView.draw();
		this->mRaceview.draw();
		this->mShipView.draw();

		this->mTBShipNameLabel.draw();
		this->mTBShipNameText.draw();
		this->mTBShipTypeLabel.draw();
		this->mTBShipTypeText.draw();
		this->mTBShipLevelLabel.draw();
		this->mTBShipLevelText.draw();

		this->mAvatar.draw();
	}
	else
	{
		this->mTBNoCharacterSelected.draw();
	}
}
