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
}

WindowChat::~WindowChat(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void WindowChat::drawContent()
{
	TextBox txtbox;
	txtbox.setBackgroundColor(sf::Color(125, 125, 125), true);
	txtbox.setFontColor(sf::Color(255, 255, 255));
	txtbox.setPosition(0,0);

	{
		sf::Lock lock(Resource::resource->getChatClient()->getMutex());
		OutputBuffer chatbuffer(Resource::resource->getChatClient()->getOutputBuffer());

		// si packet buffer non vide, on envoie tout son contenu
		if(!chatbuffer.empty())
		{
			for(auto it = chatbuffer.begin(); it != chatbuffer.end(); ++it)
			{
				
			}
		}

		Resource::resource->getChatClient()->clearOutputBuffer();
	}
}