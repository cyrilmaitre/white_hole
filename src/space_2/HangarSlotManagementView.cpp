#include "HangarSlotManagementView.h"
#include "UserInterface.h"
#include "WindowMessageError.h"
#include "WindowMessageSuccess.h"
#include "WindowChoiceAsk.h"
#include "Jukebox.h"


//*************************************************************
// Define
//*************************************************************
#define WIDTH							250
#define BACKGROUNDCOLOR					sf::Color(25, 26, 28)
#define BORDERCOLOR						sf::Color(194, 194, 194)
#define BORDERSIZE						1
#define PADDING							10
#define SLOT_FONTSIZE					18
#define BUTTONADD_MARGINTOP				20
#define BUTTONADD_MARGINBOTTOM			10
#define SLOTPRICE_FONTSIZE				14
#define SLOTPRICE						50000	// cred
#define ACTIONCOMMAND_BUYSLOT			"actioncommand_buyslot"
#define SOUND_MONEY						"soundMoney.ogg"


//*************************************************************
// Constructor - Destructor
//*************************************************************
HangarSlotManagementView::HangarSlotManagementView(void)
{
	this->mCharacter = NULL;

	this->setWidth(WIDTH);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);
	this->setDisplayTitle(false);

	this->mTBSlots.setFontSize(SLOT_FONTSIZE);
	this->mButtonAddSlot.setTitle(Resource::resource->getBundle()->getString("hangarSlotAdd"));
	this->mTBSlotPrice.setFontSize(SLOTPRICE_FONTSIZE);
	this->mTBSlotPrice.setText(Resource::resource->getBundle()->getString("hangarSlotPrice") + Tools::getSpaceAfterColon() + Tools::formatNumber(SLOTPRICE) + " " + Resource::resource->getBundle()->getString("creditAb"));

	this->setHeight(PADDING * 2 + this->mTBSlots.getHeight() + this->mButtonAddSlot.getHeight() + this->mTBSlotPrice.getHeight() + BUTTONADD_MARGINTOP + BUTTONADD_MARGINBOTTOM);
}

HangarSlotManagementView::~HangarSlotManagementView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* HangarSlotManagementView::getCharacter()
{
	return this->mCharacter;
}

void HangarSlotManagementView::setCharacter( Character* p_character )
{
	if(this->mCharacter != p_character)
	{
		this->mCharacter = p_character;
		this->notifyCharacterChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void HangarSlotManagementView::addSlot()
{
	// Check money
	if(this->getCharacter()->hasEnoughCredit(SLOTPRICE))
	{
		this->getCharacter()->decCredit(SLOTPRICE);
		this->getCharacter()->incHangarSpace();
		UserInterface::mUserInterface->addWindowPopup(new WindowMessageSuccess(	Resource::resource->getBundle()->getString("success"), 
																				Resource::resource->getBundle()->getString("windowSuccessSlot")));
		Jukebox::getInstance()->playSound(SOUND_MONEY);
		this->updateTBSlots();
	}
	else
	{
		UserInterface::mUserInterface->addWindowPopup(new WindowMessageError(	Resource::resource->getBundle()->getString("error"), 
																				Resource::resource->getBundle()->getString("windowErrorSlot")));
	}
}


void HangarSlotManagementView::addSlotConfirmation()
{
	UserInterface::mUserInterface->addWindowPopup(new WindowChoiceAsk(
		Resource::resource->getBundle()->getString("windowAskSlotTitle"), 
		Resource::resource->getBundle()->getString("windowAskSlotMessage") + " " + Tools::formatNumber(SLOTPRICE) + " " + Resource::resource->getBundle()->getString("creditAb") + "?", 
		this, NULL, ACTIONCOMMAND_BUYSLOT));
}

void HangarSlotManagementView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mButtonAddSlot.update(p_event);
		if(this->mButtonAddSlot.isClicked())
			this->addSlotConfirmation();
	}
	FieldSet::update(p_event);
}

void HangarSlotManagementView::updateTBSlots()
{
	this->mTBSlots.setText(Resource::resource->getBundle()->getString("hangarSlots") + Tools::getSpaceAfterColon() + Tools::formatNumber(this->getCharacter()->getHangarSpaceOccuped()) + "/" + Tools::formatNumber(this->getCharacter()->getHangarSpace()));
	this->updateTBSlotsPosition();
}

void HangarSlotManagementView::updatePosition()
{
	this->updateTBSlotsPosition();
	this->mButtonAddSlot.setPosition(this->getContentX() + (this->getContentWidth() - this->mButtonAddSlot.getWidth()) / 2, this->mTBSlots.getBottomY() + BUTTONADD_MARGINTOP);
	this->mTBSlotPrice.setPosition(this->getContentX() + (this->getContentWidth() - this->mTBSlotPrice.getWidth()) / 2, this->mButtonAddSlot.getBottomY() + BUTTONADD_MARGINBOTTOM);
}

void HangarSlotManagementView::updateTBSlotsPosition()
{
	this->mTBSlots.setPosition(this->getContentX() + (this->getContentWidth() - this->mTBSlots.getWidth()) / 2, this->getContentY());
}

void HangarSlotManagementView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTBSlots.draw();
		this->mButtonAddSlot.draw();
		this->mTBSlotPrice.draw();
	}
}

void HangarSlotManagementView::notifyCharacterChanged()
{
	this->updateTBSlots();
}

void HangarSlotManagementView::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}

void HangarSlotManagementView::onButtonTrueClicked( WindowChoiceActionObject* p_object, std::string p_actionCommand )
{
	this->addSlot();
}

void HangarSlotManagementView::onButtonFalseClicked( WindowChoiceActionObject* p_object, std::string p_actionCommand )
{

}
