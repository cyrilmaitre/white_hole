#include "CharacterViewSelectSmall.h"
#include "SpriteParameterFactory.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define AVATAR_BACKGROUND_COLOR							sf::Color(128, 128, 128, 75)
#define AVATAR_BORDER_COLOR								sf::Color(128, 128, 128, 125)
#define AVATAR_BORDER_SIZE								2
#define CHARACTERVIEW_SELECTSMALL_HEIGHT				72
#define CHARACTERVIEW_SELECTSMALL_BACK_COLOR			sf::Color(128, 128, 128, 75)
#define CHARACTERVIEW_SELECTSMALL_BORD_COLOR			sf::Color(128, 128, 128, 125)
#define CHARACTERVIEW_SELECTSMALL_BORD_COLORSELECTED	sf::Color(224, 224, 224, 125)
#define CHARACTERVIEW_SELECTSMALL_BORD_SIZE				2
#define CHARACTERVIEW_SELECTSMALL_AVATAR_WIDTH			64
#define CHARACTERVIEW_SELECTSMALL_AVATAR_HEIGHT			64
#define CHARACTERVIEW_SELECTSMALL_TB_LABEL_OFFSETX		10
#define CHARACTERVIEW_SELECTSMALL_TB_LABEL_FONTSIZE		ManagerConfig::FontSize::Large
#define CHARACTERVIEW_SELECTSMALL_TB_LABEL_FONTCOLOR	sf::Color(255, 106, 0)
#define CHARACTERVIEW_SELECTSMALL_TB_TEXT_OFFSETX		10
#define CHARACTERVIEW_SELECTSMALL_TB_TEXT_FONTSIZE		ManagerConfig::FontSize::Small
#define CHARACTERVIEW_SELECTSMALL_TB_TEXT_FONTCOLOR		sf::Color(195,195,195)


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterViewSelectSmall::CharacterViewSelectSmall(Character *p_character)
{
	this->mTBLabelName = NULL;
	this->mTBTextName = NULL;
	this->mTBLabelLevel = NULL;
	this->mTBTextLevel = NULL;

	this->mCharacter = p_character;

	this->setSize(CHARACTERVIEW_SELECTSMALL_WIDTH, CHARACTERVIEW_SELECTSMALL_HEIGHT);

	this->setBackgroundColor(CHARACTERVIEW_SELECTSMALL_BACK_COLOR, true);
	this->setBorderColor(CHARACTERVIEW_SELECTSMALL_BORD_COLOR, true);
	this->setBorderSize(CHARACTERVIEW_SELECTSMALL_BORD_SIZE, true);

	this->mTBLabelName = new TextBox();
	this->mTBTextName = new TextBox();
	this->mTBLabelLevel = new TextBox();
	this->mTBTextLevel = new TextBox();

	this->mAvatar.setWidth(CHARACTERVIEW_SELECTSMALL_AVATAR_WIDTH);
	this->mAvatar.setHeight(CHARACTERVIEW_SELECTSMALL_AVATAR_HEIGHT);
	this->mAvatar.setBackgroundColor(AVATAR_BACKGROUND_COLOR, true);
	this->mAvatar.setBorderColor(AVATAR_BORDER_COLOR, true);
	this->mAvatar.setBorderSize(AVATAR_BORDER_SIZE, true);

	this->mTBLabelName->setFontColor(CHARACTERVIEW_SELECTSMALL_TB_LABEL_FONTCOLOR);
	this->mTBLabelName->setFontSize(CHARACTERVIEW_SELECTSMALL_TB_LABEL_FONTSIZE);
	this->mTBLabelName->setText(Resource::resource->getBundle()->getString("characterNameLabel") + ":");
	this->mTBLabelLevel->setFontColor(CHARACTERVIEW_SELECTSMALL_TB_LABEL_FONTCOLOR);
	this->mTBLabelLevel->setFontSize(CHARACTERVIEW_SELECTSMALL_TB_LABEL_FONTSIZE);
	this->mTBLabelLevel->setText(Resource::resource->getBundle()->getString("characterLevelLabel") + ":");

	this->mTBTextName->setFontColor(CHARACTERVIEW_SELECTSMALL_TB_TEXT_FONTCOLOR);
	this->mTBTextName->setFontSize(CHARACTERVIEW_SELECTSMALL_TB_TEXT_FONTSIZE);
	this->mTBTextLevel->setFontColor(CHARACTERVIEW_SELECTSMALL_TB_TEXT_FONTCOLOR);
	this->mTBTextLevel->setFontSize(CHARACTERVIEW_SELECTSMALL_TB_TEXT_FONTSIZE);

	this->notifyCharacterChanged();
	this->notifyPositionChanged();
}

CharacterViewSelectSmall::~CharacterViewSelectSmall(void)
{
	if(this->mTBLabelName != NULL)
		delete this->mTBLabelName;

	if(this->mTBLabelLevel != NULL)
		delete this->mTBLabelLevel;

	if(this->mTBTextLevel != NULL)
		delete this->mTBTextLevel;
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* CharacterViewSelectSmall::getCharacter()
{
	return this->mCharacter;
}

void CharacterViewSelectSmall::setCharacter( Character *p_character )
{
	this->mCharacter = p_character;
	this->notifyCharacterChanged();
}


//*************************************************************
// Methods
//*************************************************************
void CharacterViewSelectSmall::notifyCharacterChanged()
{
	this->mAvatar.setBackgroundImage(SpriteParameterFactory::getSpriteParameterAvatar()->getSpritePtr(this->mCharacter->getAvatarId(), CHARACTERVIEW_SELECTSMALL_AVATAR_WIDTH, CHARACTERVIEW_SELECTSMALL_AVATAR_HEIGHT), true);
	this->updateText();
}

void CharacterViewSelectSmall::notifyPositionChanged()
{
	Listable::notifyPositionChanged();

	// Avatar
	int avatarOffset = (this->getHeight() - this->mAvatar.getHeight()) / 2; 
	this->mAvatar.setPosition(this->getX() + avatarOffset, this->getY() + avatarOffset);

	// TB
	int tbLabelOffsetY = (this->getHeight() - this->mTBLabelLevel->getHeight() - this->mTBLabelName->getHeight()) / 3; 
	int tbLabelOffsetX = this->mAvatar.getX() + this->mAvatar.getWidth() + CHARACTERVIEW_SELECTSMALL_TB_LABEL_OFFSETX;
	this->mTBLabelName->setX(tbLabelOffsetX);
	this->mTBLabelName->setY(this->getY() + tbLabelOffsetY);
	this->mTBLabelLevel->setX(tbLabelOffsetX);
	this->mTBLabelLevel->setY(this->mTBLabelName->getY() + this->mTBLabelName->getHeight() + tbLabelOffsetY);

	this->mTBTextName->setX(this->mTBLabelName->getX() + this->mTBLabelName->getWidth() + CHARACTERVIEW_SELECTSMALL_TB_TEXT_OFFSETX);
	this->mTBTextName->setY(this->mTBLabelName->getY() + (this->mTBLabelName->getHeight() - this->mTBTextName->getHeight()));
	this->mTBTextLevel->setX(this->mTBLabelLevel->getX() + this->mTBLabelLevel->getWidth() + CHARACTERVIEW_SELECTSMALL_TB_TEXT_OFFSETX);
	this->mTBTextLevel->setY(this->mTBLabelLevel->getY() + (this->mTBLabelLevel->getHeight() - this->mTBTextLevel->getHeight()));
}

void CharacterViewSelectSmall::update( sf::Event p_event )
{
	// Update UiSelectable
	Listable::update(p_event);
}

void CharacterViewSelectSmall::updateText()
{
	if(this->mCharacter != NULL)
	{
		this->mTBTextName->setText(this->mCharacter->getName());
		this->mTBTextLevel->setText(Tools::buildStringWithInt(this->mCharacter->getLevel()));
	}
}

void CharacterViewSelectSmall::draw()
{
	// Draw UiSelectable
	if(this->isSelected())
		this->setBorderColor(CHARACTERVIEW_SELECTSMALL_BORD_COLORSELECTED, true);
	else
		this->setBorderColor(CHARACTERVIEW_SELECTSMALL_BORD_COLOR, true);
	Listable::draw();

	// Draw Avatar
	this->mAvatar.draw();
	
	// Draw TB
	this->mTBLabelName->draw();
	this->mTBTextName->draw();
	this->mTBLabelLevel->draw();
	this->mTBTextLevel->draw();
}
