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

	// txtfield
	this->txtfield.setPosition(getContentX(), getContentY());
	this->txtbox.setWidth(getContentWidth());
	this->txtfield.setType(TextField::TextFieldType::TypeText);
	this->txtfield.setEnable(true);
	
	// txtbox
	this->txtbox.setFontColor(sf::Color(255, 255, 255));
	this->txtbox.setPosition(getContentX(), getContentY()+txtfield.getHeight());
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

void WindowChat::update(sf::Event p_event)
{
	if(p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::Return)
	{
		if(txtfield.getValue().size() > 0)
		{
			std::string userInput(txtfield.getValue());

			// if this is a command
			if(userInput[0] == '/')
			{
				if(userInput.size() > 1)
				{
					// get all arguments
					std::vector<std::string> result;
					std::istringstream iss(userInput.substr(1)); // userInput without first character

					for (std::string token; std::getline(iss, token, ' '); )
					{
						result.push_back(std::move(token));
					}

					// the first one is the command
					// /help
					if(result[0].compare("help") == 0) {
						this->pushChat("> Available commands: /help, /afk, /w <user> <message>, /f+ <user>, /f- <user>");
					}
					// /afk
					else if(result[0].compare("afk") == 0) {
						std::shared_ptr<C2S_Command> c2s_command(new C2S_Command(ClientCommand::C_AFK));
						Resource::resource->getChatClient()->pushInputBuffer(c2s_command);
					}
					// /w
					else if(result[0].compare("w") == 0) {
					}
					// /f+
					else if(result[0].compare("f+") == 0) {
					}
					// f-
					else if(result[0].compare("f-") == 0) {
					}
					// unknow command
					else {
						this->pushChat("> Unknow command. Use /help for more informations");
					}
				}
			}
			// else, this is a chat message
			else
			{
				this->pushChat("<ME> "+userInput);
				std::shared_ptr<C2S_Chat> c2s_chat(new C2S_Chat(userInput, "INTERNATIONAL", ChatDstType::CHANNEL));
				Resource::resource->getChatClient()->pushInputBuffer(c2s_chat);
			}

			txtfield.setValue("");
		}
	}

	this->txtfield.update(p_event);
	Window::update(p_event);
}

void WindowChat::drawContent()
{
	// txtfield
	txtfield.draw();

	// txtbox
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
					this->pushChat("<"+s2c_chat->from+"> "+s2c_chat->message);
				}
				// Si c'est une commande
				else if(message->packetType == PacketType::COMMAND) {
					S2C_Command* s2c_command = dynamic_cast<S2C_Command *>(message.get());
					this->pushChat("<SERVER CMD> " + Chat::serverCmdToString(s2c_command->command) + " -> " + s2c_command->argument);
				}
			}
		}

		
		Resource::resource->getChatClient()->clearOutputBuffer();
	}
	txtbox.draw();
}

void WindowChat::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->txtfield.setPosition(getContentX(), getContentY());
	this->txtbox.setPosition(getContentX(), getContentY()+txtfield.getHeight());
}

void WindowChat::pushChat(std::string p_string)
{
	if(this->chatLines.size() >= 10) {
		this->chatLines.pop_front();
	}

	this->chatLines.push_back(p_string);

	std::string content = "";
	for(unsigned int i = 0; i < chatLines.size(); i++)
	{
		content += chatLines[i]+"<br/>";
	}

	this->txtbox.setText(content);
}

void WindowChat::clearChat()
{
	this->chatLines.clear();
	this->txtbox.setText("");
}