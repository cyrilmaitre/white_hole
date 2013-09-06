#include "WindowMessage.h"


//*************************************************************
// Define
//*************************************************************
#define BUTTON_WIDTH		150
#define BUTTON_HEIGHT		25
#define BUTTON_MARGIN		10


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowMessage::WindowMessage( std::string p_title, std::string p_message, SpriteParameter* p_spriteSheet, std::string p_spriteIndex ) : WindowPopup(p_title, p_message, p_spriteSheet, p_spriteIndex)
{
	this->mButtonOk.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->mButtonOk.setTitle(Resource::resource->getBundle()->getString("ok"));
} 

WindowMessage::~WindowMessage(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void WindowMessage::notifyPositionChanged()
{
	WindowPopup::notifyPositionChanged();
	this->updatePosition();
}

void WindowMessage::notifySizeChanged()
{
	WindowPopup::notifySizeChanged();
	this->updatePosition();
}

void WindowMessage::updateMessageTextBox()
{
	if(this->mMessageIconSprite != NULL)
	{
		this->mMessageTextBox.setSize(	this->getContentWidth() - this->mMessageIconSprite->getSprite().getGlobalBounds().width - WINDOWPOPUP_MARGIN_MESSAGEICON,
										this->getContentHeight() - BUTTON_MARGIN * 2 - this->mButtonOk.getHeight());
	}	
	else
	{
		this->mMessageTextBox.setSize(	this->getContentWidth(),
										this->getContentHeight() - BUTTON_MARGIN * 2 - this->mButtonOk.getHeight());
	}
}

void WindowMessage::updatePosition()
{
	this->mButtonOk.setPosition(this->getContentX() + (this->getContentWidth() + this->mButtonOk.getWidth()) / 2,
								this->getContentY() + this->getContentHeight() - this->mButtonOk.getHeight() - BUTTON_MARGIN);
}

void WindowMessage::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonOk.update(p_event);
		if(this->mButtonOk.isClicked())
			this->setOpen(false);
	}
	WindowPopup::update(p_event);
}

void WindowMessage::drawContent()
{
	WindowPopup::drawContent();
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonOk.draw();
	}
}


