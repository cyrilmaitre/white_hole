#include "WindowPopup.h"


//*************************************************************
// Define
//*************************************************************
#define CONTENT_WIDTH				400
#define CONTENT_HEIGHT				175


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowPopup::WindowPopup( std::string p_title, std::string p_message, SpriteParameter* p_spriteIconSheet, std::string p_spriteIconIndex, std::string p_windowIconIdex )
{
	this->mMessageIconSprite = NULL;
	this->mMessageIconSprite = p_spriteIconSheet;

	this->mMessageTextBox.setAutoResizeHeight(false);
	this->mMessageTextBox.setAutoResizeWidth(false);

	this->setContentSize(CONTENT_WIDTH, CONTENT_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(true);
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(p_windowIconIdex));

	this->setMessageIconIndex(p_spriteIconIndex);
	this->setWindowTitle(p_title);
	this->setMessage(p_message);

	this->setPositionMiddleScreen();
}


WindowPopup::~WindowPopup(void)
{
	if(this->mMessageIconSprite != NULL)
		delete this->mMessageIconSprite;
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string WindowPopup::getMessage()
{
	return this->mMessage;
}

void WindowPopup::setMessage( std::string p_message )
{
	if(this->mMessage != p_message)
	{
		this->mMessage = p_message;
		this->notifyMessageChanged();
	}
}

std::string WindowPopup::getMessageIconIndex()
{
	return this->mMessageIconIndex;
}

void WindowPopup::setMessageIconIndex( std::string p_icon )
{
	if(this->mMessageIconIndex != p_icon)
	{
		this->mMessageIconIndex = p_icon;
		this->notifyMessageIconIndexChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void WindowPopup::notifyMessageChanged()
{
	this->mMessageTextBox.setText(this->getMessage());		
}

void WindowPopup::notifyMessageIconIndexChanged()
{
	if(this->mMessageIconIndex != "" && this->mMessageIconSprite != NULL)
	{
		this->mMessageIconSprite->selectSprite(this->mMessageIconIndex);
		this->updatePosition();
		this->updateMessageTextBox();
	}
}

void WindowPopup::notifySizeChanged()
{
	Window::notifySizeChanged();
	this->updateMessageTextBox();
}

void WindowPopup::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->updatePosition();
}

void WindowPopup::updatePosition()
{
	if(this->mMessageIconSprite != NULL)
	{
		this->mMessageIconSprite->getSprite().setPosition(	this->getContentX(), 
															this->getContentY() + (this->getContentHeight() - this->mMessageIconSprite->getSprite().getLocalBounds().height) / 2);
		this->mMessageTextBox.setPosition(	this->mMessageIconSprite->getSprite().getPosition().x + this->mMessageIconSprite->getSprite().getLocalBounds().width + WINDOWPOPUP_MARGIN_MESSAGEICON,
											this->getContentY());
	}
	else
	{
		this->mMessageTextBox.setPosition(this->getContentX(), this->getContentY());
	}
}

void WindowPopup::updateMessageTextBox()
{
	if(this->mMessageIconSprite != NULL)
	{
		this->mMessageTextBox.setSize(	this->getContentWidth() - this->mMessageIconSprite->getSprite().getLocalBounds().width - WINDOWPOPUP_MARGIN_MESSAGEICON,
										this->getContentHeight());
	}
	else
	{
		this->mMessageTextBox.setSize(this->getContentWidth(), this->getContentHeight());
	}
}

void WindowPopup::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mMessageTextBox.update(p_event);
	}
	Window::update(p_event);
}

void WindowPopup::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		if(this->mMessageIconSprite != NULL)
			Resource::resource->getApp()->draw(this->mMessageIconSprite->getSprite());
		this->mMessageTextBox.draw();
	}
}
