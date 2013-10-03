#include "SkillCharacterView.h"
#include "SpriteParameterFactory.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define SKILLVIEW_WIDTH					250
#define SKILLVIEW_HEIGHT				36
#define SKILLVIEW_BACK_COLOR			sf::Color(128, 128, 128, 75)
#define SKILLVIEW_BORD_SIZE				2
#define SKILLVIEW_BORD_COLOR			sf::Color(128, 128, 128, 125)
#define SKILLVIEW_IMG_WIDTH				32
#define SKILLVIEW_IMG_HEIGHT			32
#define SKILLVIEW_IMG_OFFSETX			2
#define SKILLVIEW_TB_NAME_FONTSIZE		ManagerConfig::FontSize::Tiny
#define SKILLVIEW_TB_NAME_FONTCOLOR		sf::Color(195,195,195)
#define SKILLVIEW_TB_NAME_OFFSETX		5
#define SKILLVIEW_BUTTON_WIDTH			28
#define SKILLVIEW_BUTTON_HEiGHT			28
#define SKILLVIEW_BUTTON_OFFSET			4
#define SKILLVIEW_TB_LEVEL_FONTSIZE		ManagerConfig::FontSize::Tiny
#define SKILLVIEW_TB_LEVEL_FONTCOLOR	sf::Color(255, 201, 14)
#define SKILLVIEW_TB_LEVEL_OFFSETX		10
#define SKILLVIEW_PUB_LEVEL_WIDTH		175


//*************************************************************
// Constructor - Destructor
//*************************************************************
SkillCharacterView::SkillCharacterView(void)
{
	this->mSkillCharacter = NULL;
	this->mSkillSprite = NULL;
	this->mTBName = NULL;
	this->mButtonInc = NULL;
	this->mButtonDec = NULL;
	this->mTBLevel = NULL;
	this->mPUBLevel = NULL;

	this->setSize(SKILLVIEW_WIDTH, SKILLVIEW_HEIGHT);
	this->setBackgroundColor(SKILLVIEW_BACK_COLOR, true);
	this->setBorderSize(SKILLVIEW_BORD_SIZE, true);
	this->setBorderColor(SKILLVIEW_BORD_COLOR, true);
	this->setEditable(true);

	this->mButtonInc = new Button();
	this->mButtonInc->setSize(SKILLVIEW_BUTTON_WIDTH, SKILLVIEW_BUTTON_HEiGHT);
	this->mButtonInc->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon16X16(true)->getSpritePtr(IC_16X16_ADD));

	this->mButtonDec = new Button();
	this->mButtonDec->setSize(SKILLVIEW_BUTTON_WIDTH, SKILLVIEW_BUTTON_HEiGHT);
	this->mButtonDec->setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon16X16(true)->getSpritePtr(IC_16X16_SUB));

	this->mTBName = new TextBox();
	this->mTBName->setFontSize(SKILLVIEW_TB_NAME_FONTSIZE);
	this->mTBName->setFontColor(SKILLVIEW_TB_NAME_FONTCOLOR);

	this->mTBLevel = new TextBox();
	this->mTBLevel->setFontSize(SKILLVIEW_TB_LEVEL_FONTSIZE);
	this->mTBLevel->setFontColor(SKILLVIEW_TB_LEVEL_FONTCOLOR);

	this->mPUBLevel = new PopupBubble(this->mTBLevel);
}


SkillCharacterView::~SkillCharacterView(void)
{
	if(this->mSkillSprite != NULL)
		delete this->mSkillSprite;

	if(this->mTBName != NULL)
		delete this->mTBName;

	if(this->mButtonInc != NULL)
		delete this->mButtonInc;

	if(this->mButtonDec != NULL)
		delete this->mButtonDec;

	if(this->mTBLevel != NULL)
		delete this->mTBLevel;

	if(this->mPUBLevel != NULL)
		delete this->mPUBLevel;
}


//*************************************************************
// Getters - Setters
//*************************************************************
SkillCharacter* SkillCharacterView::getSkillCharacter()
{
	return this->mSkillCharacter;
}

void SkillCharacterView::setSkillCharacter( SkillCharacter* p_skill )
{
	if(this->mSkillCharacter != p_skill)
	{
		this->mSkillCharacter = p_skill;
		if(this->mSkillSprite != NULL)
			delete this->mSkillSprite;
		this->mSkillSprite = SpriteParameterFactory::getSpriteParameterSkill(true)->getSpritePtr(this->getSkillCharacter()->getSkill()->getSpriteId(), SKILLVIEW_IMG_WIDTH, SKILLVIEW_IMG_HEIGHT);

		this->notifySkillCharacterChanged();
	}
}

bool SkillCharacterView::isEditable()
{
	return this->mEditable;
}

void SkillCharacterView::setEditable( bool p_editable )
{
	this->mEditable = p_editable;
}


//*************************************************************
// Methods
//*************************************************************
void SkillCharacterView::cancel()
{
	this->getSkillCharacter()->cancelLevelPending();
	this->notifySkillCharacterChanged();
}

void SkillCharacterView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mTBLevel->update(p_event);
		this->mButtonInc->update(p_event);
		this->mButtonDec->update(p_event);
		this->mPUBLevel->update(p_event);
		Block::update(p_event);

		// Update button
		if(this->isEditable())
		{
			if(this->mButtonInc->isClicked())
			{
				this->getSkillCharacter()->levelUp();
				this->notifySkillCharacterChanged();
			}

			if(this->mButtonDec->isClicked())
			{
				this->getSkillCharacter()->levelDown();
				this->notifySkillCharacterChanged();
			}
		}
	}
}

void SkillCharacterView::updatePosition()
{
	// Update skill sprite
	int skillSpriteOffsetY = (this->getHeight() - SKILLVIEW_IMG_HEIGHT) / 2;
	this->mSkillSprite->setPosition(this->getX() + SKILLVIEW_IMG_OFFSETX, this->getY() + skillSpriteOffsetY);

	// Update skill name
	this->mTBName->setX(this->mSkillSprite->getPosition().x + this->mSkillSprite->getGlobalBounds().width + SKILLVIEW_IMG_OFFSETX + SKILLVIEW_TB_NAME_OFFSETX);
	this->mTBName->setY(this->getY() + (this->getHeight() - this->mTBName->getHeight()) / 2);

	// Update button
	if(this->isEditable())
	{
		this->mButtonInc->setX(this->getX() + this->getWidth() - this->mButtonInc->getWidth() - SKILLVIEW_BUTTON_OFFSET);
		this->mButtonInc->setY(this->getY() + SKILLVIEW_BUTTON_OFFSET);
		this->mButtonDec->setX(this->mButtonInc->getX() - this->mButtonDec->getWidth() - SKILLVIEW_BUTTON_OFFSET);
		this->mButtonDec->setY(this->getY() + SKILLVIEW_BUTTON_OFFSET);
	}

	// Update Level
	if(this->isEditable())
		this->mTBLevel->setX(this->mButtonDec->getX() - this->mTBLevel->getWidth() - SKILLVIEW_TB_LEVEL_OFFSETX);
	else
		this->mTBLevel->setX(this->getX() + this->getWidth() - this->mTBLevel->getWidth() - SKILLVIEW_TB_LEVEL_OFFSETX);
	this->mTBLevel->setY(this->getY() + (this->getHeight() - this->mTBLevel->getHeight()) / 2);
}

void SkillCharacterView::update()
{
	if(this->isVisible())
	{
		// Update button
		if(this->getSkillCharacter()->canBeLevelUp())
			this->mButtonInc->setEnable(true);
		else
			this->mButtonInc->setEnable(false);

		if(this->getSkillCharacter()->canBeLevelDown())
			this->mButtonDec->setEnable(true);
		else
			this->mButtonDec->setEnable(false);

		// Update PUB
		this->mPUBLevel->update();
	}
}

void SkillCharacterView::updateLevelDetail()
{
	std::string detail = Resource::resource->getBundle()->getString("level") + ":" + Tools::getSpaceAfterColon() + Tools::buildStringWithInt(this->getSkillCharacter()->getLevel() + this->getSkillCharacter()->getLevelPending()) + "%";

	if(this->getSkillCharacter()->getCharacter()->hasRace())
	{
		int bonusRace = this->getSkillCharacter()->getCharacter()->getRace()->getBonusSkill(this->getSkillCharacter()->getSkill()->getIdSkill());
		if(bonusRace > 0)
			detail += "<br/>" + this->getSkillCharacter()->getCharacter()->getRace()->getName() + ":" + Tools::getSpaceAfterColon() + Tools::buildStringWithInt(bonusRace) + "%";
	}

	if(this->getSkillCharacter()->getCharacter()->hasJob())
	{
		int bonusJob = this->getSkillCharacter()->getCharacter()->getJob()->getBonusSkill(this->getSkillCharacter()->getSkill()->getIdSkill());
		if(bonusJob > 0)
			detail += "<br/>" + this->getSkillCharacter()->getCharacter()->getJob()->getName() + ":" + Tools::getSpaceAfterColon() + Tools::buildStringWithInt(bonusJob) + "%";
	};

	this->mPUBLevel->setText(detail);
}

void SkillCharacterView::draw()
{
	if(this->isVisible())
	{
		// Draw block
		Block::draw();

		// Draw skill sprite
		Resource::resource->getApp()->draw(*this->mSkillSprite);

		// Draw skill name
		this->mTBName->draw();

		// Draw button
		if(this->isEditable())
		{
			this->mButtonInc->draw();
			this->mButtonDec->draw();
		}

		// Draw level
		this->mTBLevel->draw();
	}
}

void SkillCharacterView::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updatePosition();
}

void SkillCharacterView::notifySkillCharacterChanged()
{
	if(this->mSkillCharacter != NULL)
	{
		this->mTBName->setText(this->getSkillCharacter()->getSkill()->getName());
		this->mTBLevel->setText(Tools::formatNumber(this->getSkillCharacter()->getTotalLevel())+'%');
		this->updateLevelDetail();
		this->updatePosition();
	}
}
