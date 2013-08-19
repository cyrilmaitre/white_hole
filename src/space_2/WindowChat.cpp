#include "WindowChat.h"


//*************************************************************
// Define
//*************************************************************
#define UIWINDOW_PLAYER_WIDTH		320
#define UIWINDOW_PLAYER_HEIGHT		150


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowChat::WindowChat(void)
{
	this->setContentWidth(UIWINDOW_PLAYER_WIDTH);
	this->setContentHeight(UIWINDOW_PLAYER_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PERSON));

	this->setPositionMiddleScreen();

	
	// txtbox
	this->txtbox.setFontColor(sf::Color(255, 255, 255));
	this->txtbox.setPosition(getContentX(), getContentY());
	this->txtbox.setWidth(getContentWidth());
	this->txtbox.setAutoResizeHeight(false);
	this->txtbox.setAutoResizeWidth(false);
	this->txtbox.setHeight(getContentHeight());
}

WindowChat::~WindowChat(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void WindowChat::drawContent()
{

	std::string chat = txtbox.getText();
	{
		sf::Lock lock(Resource::resource->getChatClient()->getMutex());
		OutputBuffer chatbuffer(Resource::resource->getChatClient()->getOutputBuffer());

		

		// si packet buffer non vide, on envoie tout son contenu
		if(!chatbuffer.empty())
		{
			for(auto it = chatbuffer.begin(); it != chatbuffer.end(); ++it)
			{
				S2C_Chat s2c_chat = *it;
				chat += "<"+s2c_chat.from+"> "+s2c_chat.message+"<br/>";
			}
		}

		
		Resource::resource->getChatClient()->clearOutputBuffer();
	}

	txtbox.setText(chat);
	txtbox.draw();
}

void WindowChat::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->txtbox.setPosition(getContentX(), getContentY());
}