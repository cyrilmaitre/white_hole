#include "StationScreenLeftMenu.h"
#include "CharacterBank.h"
#include "UserInterface.h"
#include "StationScreen.h"
#include "WindowMessageError.h"
#include "WindowChoiceAsk.h"
#include "CharacterUpdate.h"
#include "WindowMessageSuccess.h"
#include "NetworkJobManager.h"
#include "Jukebox.h"


//*************************************************************
// Define
//*************************************************************
#define LEFTMENU_BUTTON_WIDTH				150
#define LEFTMENU_BUTTON_HEIGHT				25
#define LEFTMENU_BUTTON_MARGIN				10
#define LEFTMENU_BUTTON_HANGAR_MARGINTOP	75
#define LEFTMENU_BUTTON_CARGO_MARGINTOP		75
#define LEFTMENU_PADDING					10
#define LEFTMENU_WIDTH						LEFTMENU_PADDING * 2 + LEFTMENU_BUTTON_WIDTH
#define LEFTMENU_BACKCOLOR					sf::Color(128, 128, 128, 200)
#define LEFTMENU_BORDCOLOR					sf::Color(128, 128, 128, 250)
#define LEFTMENU_BORDSIZE					2
#define ACTIONCOMMAND_UNLOCKBANK			"unlockbank"
#define SOUND_MONEY							"windowPurchase.ogg"


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationScreenLeftMenu::StationScreenLeftMenu(Character* p_character, StationScreen* p_screen)
{
	this->mCharacter = NULL;
	this->mStationScreen = NULL;
	this->setCharacter(p_character);
	this->setStationScreen(p_screen);

	this->setBorderSize(LEFTMENU_BORDSIZE, true);
	this->setBorderColor(LEFTMENU_BORDCOLOR, true);
	this->setBackgroundColor(LEFTMENU_BACKCOLOR, true);
	this->setDisplayTitle(false);

	this->mButtonHangar.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonHangar.setTitle(Resource::resource->getBundle()->getString("hangar"));

	this->mButtonMarket.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonMarket.setTitle(Resource::resource->getBundle()->getString("market"));

	this->mButtonCraft.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonCraft.setTitle(Resource::resource->getBundle()->getString("craft"));

	this->mButtonShipCargo.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonShipCargo.setTitle(Resource::resource->getBundle()->getString("shipCargo"));

	this->mButtonCharacterSheet.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonShipSheet.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);

	this->mButtonUndock.setSize(LEFTMENU_BUTTON_WIDTH, LEFTMENU_BUTTON_HEIGHT);
	this->mButtonUndock.setTitle(Resource::resource->getBundle()->getString("undock"));
}

StationScreenLeftMenu::~StationScreenLeftMenu(void)
{
	for(int i = 0; i < this->mButtonBanks.size(); i++)
	{
		if(this->mButtonBanks[i] != NULL)
			delete this->mButtonBanks[i];
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* StationScreenLeftMenu::getCharacter()
{
	return this->mCharacter;
}

void StationScreenLeftMenu::setCharacter( Character* p_character )
{
	if(this->mCharacter != p_character)
	{
		this->mCharacter = p_character;
		this->notifyCharacterChanged();
	}
}

StationScreen* StationScreenLeftMenu::getStationScreen()
{
	return this->mStationScreen;
}

void StationScreenLeftMenu::setStationScreen( StationScreen* p_screen )
{
	this->mStationScreen = p_screen;
}

int StationScreenLeftMenu::getWidth()
{
	return LEFTMENU_WIDTH;
}


//*************************************************************
// Methods
//*************************************************************
void StationScreenLeftMenu::update()
{

}

void StationScreenLeftMenu::updateButtonBank()
{
	for(int i = 0; i < this->mButtonBanks.size(); i++)
	{
		CharacterBank* currentBank = this->getCharacter()->getBank(i);
		if(!currentBank->isUnlock())
		{
			if(!currentBank->canBeUnlock())
			{
				this->mButtonBanks[i]->setEnable(false);
				this->mButtonBanks[i]->setTitle(Resource::resource->getBundle()->getString("locked"));
			}
			else
			{
				this->mButtonBanks[i]->setEnable(true);
				this->mButtonBanks[i]->setTitle(Tools::formatNumber(currentBank->getPrice()) + " " + Resource::resource->getBundle()->getString("creditAb"));
			}
		}
		else
		{
			this->mButtonBanks[i]->setEnable(true);
			this->mButtonBanks[i]->setTitle(Resource::resource->getBundle()->getString("bankCargo") + Tools::buildStringWithInt(currentBank->getNumber()));
		}
	}
}

void StationScreenLeftMenu::updateButtonSheet()
{
	if(this->mCharacter != NULL)
	{
		this->mButtonCharacterSheet.setTitle(this->mCharacter->getName());
		this->mButtonShipSheet.setTitle(this->mCharacter->getShipPiloted()->getName());
	}
}

void StationScreenLeftMenu::updatePosition()
{
	this->mButtonCharacterSheet.setPosition(this->getLeftX() + LEFTMENU_PADDING, this->getTopY() + LEFTMENU_PADDING);
	this->mButtonShipSheet.setPosition(this->mButtonCharacterSheet.getLeftX(), this->mButtonCharacterSheet.getBottomY() + LEFTMENU_BUTTON_MARGIN);
	
	this->mButtonHangar.setPosition(this->mButtonShipSheet.getLeftX(), this->mButtonShipSheet.getBottomY() + LEFTMENU_BUTTON_HANGAR_MARGINTOP);
	this->mButtonMarket.setPosition(this->mButtonHangar.getLeftX(), this->mButtonHangar.getBottomY() + LEFTMENU_BUTTON_MARGIN);
	this->mButtonCraft.setPosition(this->mButtonMarket.getLeftX(), this->mButtonMarket.getBottomY() + LEFTMENU_BUTTON_MARGIN);

	this->mButtonShipCargo.setPosition(this->mButtonCraft.getLeftX(), this->mButtonCraft.getBottomY() + LEFTMENU_BUTTON_CARGO_MARGINTOP);
	for(int i = 0; i < this->mButtonBanks.size(); i++)
	{
		if(i == 0)
			this->mButtonBanks[i]->setPosition(this->mButtonShipCargo.getLeftX(), this->mButtonShipCargo.getBottomY() + LEFTMENU_BUTTON_MARGIN);
		else
			this->mButtonBanks[i]->setPosition(this->mButtonShipCargo.getLeftX(), this->mButtonBanks[i-1]->getBottomY() + LEFTMENU_BUTTON_MARGIN);			
	}

	this->mButtonUndock.setPosition(this->getLeftX() + LEFTMENU_BUTTON_MARGIN, this->getBottomY() - LEFTMENU_BUTTON_MARGIN - this->mButtonUndock.getHeight());
}

void StationScreenLeftMenu::update( sf::Event p_event )
{
	this->mButtonCharacterSheet.update(p_event);
	if(this->mButtonCharacterSheet.isClicked())
		UserInterface::mUserInterface->getWindowCharacter()->setOpenSwitch();

	this->mButtonShipSheet.update(p_event);
	if(this->mButtonShipSheet.isClicked())
		UserInterface::mUserInterface->getWindowShip()->setOpenSwitch();

	this->mButtonHangar.update(p_event);
	if(this->mButtonHangar.isClicked())
		this->getStationScreen()->loadPanelHangar();

	this->mButtonMarket.update(p_event);
	if(this->mButtonMarket.isClicked())
		this->getStationScreen()->loadPanelMarket();

	this->mButtonCraft.update(p_event);
	if(this->mButtonCraft.isClicked())
		this->getStationScreen()->loadPanelCraft();

	this->mButtonShipCargo.update(p_event);
	if(this->mButtonShipCargo.isClicked())
		UserInterface::mUserInterface->getWindowCargoStationShip()->setOpenSwitch();

	for(int i = 0; i < this->mButtonBanks.size(); i++)
	{
		this->mButtonBanks[i]->update(p_event);
		if(this->mButtonBanks[i]->isClicked())
			this->buttonBankClicked(i);
	}

	this->mButtonUndock.update(p_event);
	if(this->mButtonUndock.isClicked())
		this->getStationScreen()->undock();

	FieldSet::update(p_event);
}

void StationScreenLeftMenu::draw()
{
	FieldSet::draw();
	this->mButtonCharacterSheet.draw();
	this->mButtonShipSheet.draw();
	this->mButtonHangar.draw();
	this->mButtonMarket.draw();
	this->mButtonCraft.draw();
	this->mButtonShipCargo.draw();
	for(int i = 0; i < this->mButtonBanks.size(); i++)
		this->mButtonBanks[i]->draw();
	this->mButtonUndock.draw();
}

void StationScreenLeftMenu::notifyCharacterChanged()
{
	// Clear button bank
	for(int i = 0; i < this->mButtonBanks.size(); i++)
	{
		if(this->mButtonBanks[i] != NULL)
			delete this->mButtonBanks[i];
	}
	this->mButtonBanks.clear();

	// Add news
	if(this->getCharacter() != NULL)
	{
		for(int i = 0; i < this->getCharacter()->getBankCount(); i++)
			this->mButtonBanks.push_back(new Button());
	}

	this->updateButtonSheet();
	this->updateButtonBank();
	this->updatePosition();
}

void StationScreenLeftMenu::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}

void StationScreenLeftMenu::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->updatePosition();
}

void StationScreenLeftMenu::buttonBankClicked( int p_index )
{
	CharacterBank* currentBank = this->getCharacter()->getBank(p_index);

	if(currentBank->isUnlock())
	{
		// If Unlock
		UserInterface::mUserInterface->getWindowCargoStationBank(p_index)->setOpenSwitch();
	}
	else
	{
		if(this->getCharacter()->hasEnoughCredit(currentBank->getPrice()))
		{
			// Ask if user want to unlock
			UserInterface::mUserInterface->addWindowPopup(new WindowChoiceAsk(	Resource::resource->getBundle()->getString("windowAskBankTitle"), 
																				Resource::resource->getBundle()->getString("windowAskBankMessage") + " " + Tools::formatNumber(currentBank->getPrice()) + " " + Resource::resource->getBundle()->getString("creditAb") + "?", 
																				this, currentBank, ACTIONCOMMAND_UNLOCKBANK));
		}
		else
		{
			// Error: not enough money
			UserInterface::mUserInterface->addWindowPopup(new WindowMessageError(	Resource::resource->getBundle()->getString("error"), 
																					Resource::resource->getBundle()->getString("windowErrorBank")));
		}
	}
}

void StationScreenLeftMenu::onButtonTrueClicked( WindowChoiceActionObject* p_object, std::string p_actionCommand )
{
	if(p_actionCommand == ACTIONCOMMAND_UNLOCKBANK)
	{
		if(p_object != NULL)
		{
			// Unlock selected bank
			CharacterBank* currentBank = (CharacterBank*) p_object;
			currentBank->unlock();
			this->updateButtonBank();
			UserInterface::mUserInterface->addWindowPopup(new WindowMessageSuccess(	Resource::resource->getBundle()->getString("success"), 
																					Resource::resource->getBundle()->getString("windowSuccessBank")));
			Jukebox::getInstance()->playSound(SOUND_MONEY);
		}
	}
}

void StationScreenLeftMenu::onButtonFalseClicked( WindowChoiceActionObject* p_object, std::string p_actionCommand )
{

}

