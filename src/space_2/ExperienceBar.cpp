#include "ExperienceBar.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define VALUE_MIN			0
#define PUB_WIDTH			200
#define FONTSIZE			ManagerConfig::FontSize::Tiny


//*************************************************************
// Constructor - Destructor
//*************************************************************
ExperienceBar::ExperienceBar(void)
{
	this->mLevelable = NULL;
	this->mPubExperience = NULL;

	this->mPubExperience = new PopupBubble(this);

	this->setFontSize(FONTSIZE);
	this->setMode(ProgressBar::UiProgressBarMode::ModeValueMax);
	this->setType(TypeCharacter);
	this->setValueMin(VALUE_MIN);
}

ExperienceBar::~ExperienceBar(void)
{
	if(this->mPubExperience != NULL)
		delete this->mPubExperience;
}


//*************************************************************
// Getters - Setters
//*************************************************************
Levelable* ExperienceBar::getLevelable()
{
	return this->mLevelable;
}

void ExperienceBar::setLevelable( Levelable* p_levelable )
{
	this->mLevelable = p_levelable;

	if(this->getLevelable() != NULL)
	{
		this->setValueMax(this->getLevelable()->getExperienceCurrentLevel());
		this->setValue(this->getLevelable()->getExperience());
		this->updatePub();
	}
}

ExperienceBar::ExperienceBarType ExperienceBar::getType()
{
	return this->mType;
}

void ExperienceBar::setType( ExperienceBarType p_type )
{
	this->mType = p_type;
}


//*************************************************************
// Methods
//*************************************************************
void ExperienceBar::update( sf::Event myEvent )
{
	ProgressBar::update(myEvent);

	this->mPubExperience->update(myEvent);

	if(this->isClicked())
	{
		if(this->getMode() == ProgressBar::UiProgressBarMode::ModeNone)
			this->setMode(ProgressBar::UiProgressBarMode::ModeValueMax);
		else if(this->getMode() == ProgressBar::UiProgressBarMode::ModeValueMax)
			this->setMode(ProgressBar::UiProgressBarMode::ModePercent);
		else if(this->getMode() == ProgressBar::UiProgressBarMode::ModePercent)
			this->setMode(ProgressBar::UiProgressBarMode::ModeNone);
	}
}

void ExperienceBar::update()
{
	this->mPubExperience->update();

	if(this->getLevelable() != NULL && (this->getLevelable()->isExperienceChanged() || this->getLevelable()->isLevelChanged()))
	{
		this->setValueMax(this->getLevelable()->getExperienceCurrentLevel());
		this->setValue(this->getLevelable()->getExperience());
		this->updatePub();
	}
}

void ExperienceBar::updatePub()
{
	if(this->getLevelable() != NULL)
	{
		// Clear
		this->mPubExperience->clear();

		// Set new text
		if(this->mType == ExperienceBarType::TypeCharacter)
			this->mPubExperience->addLine(	Resource::resource->getBundle()->getString("experienceBarYourLevel") + 
											Tools::getSpaceAfterColon() + Tools::buildStringWithInt(this->getLevelable()->getLevel()), false);
		else
			this->mPubExperience->addLine(	Resource::resource->getBundle()->getString("experienceBarYourShipLevel") + 
											Tools::getSpaceAfterColon() + Tools::buildStringWithInt(this->getLevelable()->getLevel()), false);

		this->mPubExperience->addLine(	Resource::resource->getBundle()->getString("experienceBarExperience") + 
										Tools::getSpaceAfterColon() + Tools::buildStringWithLong(this->getLevelable()->getExperience()) + " / " + Tools::buildStringWithLong(this->getLevelable()->getExperienceCurrentLevel()), false);
		this->mPubExperience->addLine(	Resource::resource->getBundle()->getString("experienceBarLevelProgression") + 
										Tools::getSpaceAfterColon() + Tools::buildStringWithInt(this->getValuePercent() * 100) + " %", false);

		// Notify
		this->mPubExperience->notifyDataSetChanged();
	}
}
