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
		OutputBuffer outputbuffer(Resource::resource->getChatClient()->getOutputBuffer());

		

		// si packet buffer non vide, on envoie tout son contenu
		if(!outputbuffer.empty())
		{
			for(auto it = outputbuffer.begin(); it != outputbuffer.end(); ++it)
			{

				std::shared_ptr<Message> message = *it;
				// Si c'est un message chat
				if(message->packetType == PacketType::CHAT) {
					S2C_Chat* s2c_chat = dynamic_cast<S2C_Chat *>(message.get());
					chat += "<"+s2c_chat->from+"> "+s2c_chat->message+"<br/>";
				}
				// Si c'est une commande
				else if(message->packetType == PacketType::COMMAND) {
					S2C_Command* s2c_command = dynamic_cast<S2C_Command *>(message.get());
					chat += "<SERVER CMD> ";
					chat += Chat::serverCmdToString(s2c_command->command);
					chat += " -> "+s2c_command->argument+"<br/>";
				}
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