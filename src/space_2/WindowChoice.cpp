#include "WindowChoice.h"


//*************************************************************
// Define
//*************************************************************
#define BUTTON_WIDTH		150
#define BUTTON_HEIGHT		25
#define BUTTON_MARGIN		10


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowChoice::WindowChoice( std::string p_title, std::string p_message, SpriteParameter* p_spriteSheet, std::string p_spriteIndex, std::string p_windowIconIdex, std::string p_buttonTrueTitle, std::string p_buttonFalseTitle, WindowChoiceAction* p_actions, std::string p_actionCommand )
	 : WindowPopup(p_title, p_message, p_spriteSheet, p_spriteIndex, p_windowIconIdex)
{
	this->mAction = NULL;
	this->setAction(p_actions);
	this->setActionCommand(p_actionCommand);

	this->mButtonTrue.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->setButtonTrueTitle(p_buttonTrueTitle);

	this->mButtonFalse.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->setButtonFalseTitle(p_buttonFalseTitle);

	this->updatePosition();
	this->updateMessageTextBox();
}


WindowChoice::~WindowChoice(void)
{
	this->deleteAction();	
}

void WindowChoice::deleteAction()
{
	if(this->mAction != NULL)
	{
		delete this->mAction;
		this->mAction = NULL;
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
void WindowChoice::setButtonTrueTitle(std::string p_title)
{
	this->mButtonTrue.setTitle(p_title);
}

void WindowChoice::setButtonFalseTitle(std::string p_title)
{
	this->mButtonFalse.setTitle(p_title);
}

bool WindowChoice::hasAction()
{
	return this->mAction != NULL;
}

WindowChoiceAction* WindowChoice::getAction()
{
	return this->mAction;
}

void WindowChoice::setAction( WindowChoiceAction* p_action )
{
	if(this->mAction != p_action)
	{
		this->deleteAction();
		this->mAction = p_action;
	}
}

std::string WindowChoice::getActionCommand()
{
	return this->mActionCommand;
}

void WindowChoice::setActionCommand( std::string p_command )
{
	this->mActionCommand = p_command;
}


//*************************************************************
// Methods
//*************************************************************
void WindowChoice::notifyPositionChanged()
{
	WindowPopup::notifyPositionChanged();
	this->updatePosition();
}

void WindowChoice::notifySizeChanged()
{
	WindowPopup::notifySizeChanged();
	this->updatePosition();
}

void WindowChoice::updateMessageTextBox()
{
	if(this->mMessageIconSprite != NULL)
	{
		this->mMessageTextBox.setSize(	this->getContentWidth() - this->mMessageIconSprite->getSprite().getLocalBounds().width - WINDOWPOPUP_MARGIN_MESSAGEICON,
										this->getContentHeight() - BUTTON_MARGIN * 2 - this->mButtonTrue.getHeight());
		this->WindowPopup::updatePosition();
	}	
	else
	{
		this->mMessageTextBox.setSize(	this->getContentWidth(),
										this->getContentHeight() - BUTTON_MARGIN * 2 - this->mButtonTrue.getHeight());
	}
}

void WindowChoice::updatePosition()
{
	this->mButtonTrue.setPosition(	this->getContentX() + (this->getContentWidth() / 2) - this->mButtonTrue.getWidth() - BUTTON_MARGIN / 2,
									this->getContentY() + this->getContentHeight() - this->mButtonTrue.getHeight() - BUTTON_MARGIN);
	this->mButtonFalse.setPosition(	this->mButtonTrue.getRightX() + BUTTON_MARGIN,
									this->getContentY() + this->getContentHeight() - this->mButtonFalse.getHeight() - BUTTON_MARGIN);
}

void WindowChoice::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonTrue.update(p_event);
		this->mButtonFalse.update(p_event);

		if(this->mButtonTrue.isClicked())
		{
			if(this->hasAction())
				this->getAction()->onButtonTrueClicked(this->getActionCommand());
			this->setOpen(false);
		}

		if(this->mButtonFalse.isClicked())
		{
			if(this->hasAction())
				this->getAction()->onButtonFalseClicked(this->getActionCommand());
			this->setOpen(false);
		}
	}
	WindowPopup::update(p_event);
}

void WindowChoice::drawContent()
{
	WindowPopup::drawContent();
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonTrue.draw();
		this->mButtonFalse.draw();
	}
}



