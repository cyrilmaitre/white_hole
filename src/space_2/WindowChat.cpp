#include "WindowChat.h"

//*************************************************************
// Define
//*************************************************************
#define UIWINDOW_PLAYER_WIDTH		320
#define UIWINDOW_PLAYER_HEIGHT		150
#define MAX_CHAT_LINES				100

#define WINDOW_WIDTH	600
#define WINDOW_HEIGHT	300
#define MRG	5
#define UL_WIDTH		200-(MRG*2)
#define UL_HEIGHT		WINDOW_HEIGHT
#define UL_X			WINDOW_WIDTH-UL_WIDTH+(MRG*3)
#define UL_Y			0
#define TXTBOX_WIDTH	400
#define TXTBOX_HEIGHT	275
#define TXTBOX_X		0
#define TXTBOX_Y		0
#define TXTFIELD_WIDTH	340
#define TXTFIELD_HEIGHT	WINDOW_HEIGHT-TXTBOX_HEIGHT-MRG
#define TXTFIELD_X		0
#define TXTFIELD_Y		TXTBOX_Y+TXTBOX_HEIGHT+MRG
#define BUTTON_WIDTH	TXTBOX_WIDTH-TXTFIELD_WIDTH-(MRG*2)
#define BUTTON_HEIGHT	WINDOW_HEIGHT-TXTBOX_HEIGHT-MRG
#define BUTTON_X		TXTFIELD_WIDTH+MRG+2
#define BUTTON_Y		TXTFIELD_Y


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowChat::WindowChat(void)
{
	this->setWindowTitle("Chat");

	this->setContentWidth(WINDOW_WIDTH); // 320
	this->setContentHeight(WINDOW_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PERSON));

	this->setPositionMiddleScreen();
	
	// txtbox
	this->txtbox.setFontColor(sf::Color(255, 255, 255));
	this->txtbox.setHeight(TXTBOX_HEIGHT);
	this->txtbox.setWidth(TXTBOX_WIDTH);
	this->txtbox.setPosition(getContentX()+TXTBOX_X, getContentY()+TXTBOX_Y);
	this->txtbox.setAutoResizeWidth(false);

	// txtfield -> positionné par rapport à txtbox
	this->txtfield.setPosition(getContentX()+TXTFIELD_X, getContentY()+TXTFIELD_Y);
	this->txtfield.setWidth(TXTFIELD_WIDTH);
	this->txtfield.setHeight(TXTFIELD_HEIGHT);
	this->txtfield.setType(TextField::TextFieldType::TypeText);
	this->txtfield.setEnable(false);

	// button send -> positionné par rapport à txtbox
	this->buttonSend.setTitle("Send");
	this->buttonSend.setWidth(BUTTON_WIDTH);
	this->buttonSend.setHeight(BUTTON_HEIGHT);
	this->buttonSend.setPosition(getContentX()+BUTTON_X, getContentY()+BUTTON_Y);

	// txtbox 2 (userlist) -> positionné par rapport à txtfield
	this->txtboxUL.setFontColor(sf::Color(255, 255, 255));
	this->txtboxUL.setHeight(UL_HEIGHT);
	this->txtboxUL.setBorderColor(sf::Color(150,150,150), true);
	this->txtboxUL.setBorderSize(1, true);
	this->txtboxUL.setPadding(2);
	this->txtboxUL.setWidth(UL_WIDTH);
	this->txtboxUL.setPosition(getContentX()+UL_X, getContentY()+UL_Y);
	this->txtboxUL.setAutoResizeWidth(false);
	this->txtboxUL.setForceScrollBar(true);

}

WindowChat::~WindowChat(void)
{
}


//*************************************************************
// Methods
//*************************************************************

void WindowChat::update(sf::Event p_event)
{
	// network state
	NetworkState ns = Resource::resource->getChatClient()->getNetworkState();
	AuthResponse ar = Resource::resource->getChatClient()->getAuthResponse();

	// events
	if((ns.code == NetworkStateCode::NS_CONNECTION_OK_AUTHRESPONSE && ar == AuthResponse::AR_OK) && p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::Return)
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

					if(result.size() > 0)
					{
						// the first one is the command
						// /help
						if(result[0].compare("help") == 0) {
							this->pushChat("> Available commands: /help, /afk, /w <user> <message>, /f+ <user>, /f- <user>, /f! <user>, /clear");
						}
						else if(result[0].compare("clear") == 0) {
							this->clearChat();
						}
						// /afk
						else if(result[0].compare("afk") == 0) {
							std::shared_ptr<C2S_Command> c2s_command(new C2S_Command(ClientCommand::C_AFK));
							Resource::resource->getChatClient()->pushInputBuffer(c2s_command);
						}
						// /w
						else if(result[0].compare("w") == 0) {
							if(result.size() >= 3)
							{
								// get message content from vector
								std::string message;
								for(std::vector<std::string>::size_type i = 2; i != result.size(); i++) {
									if (!message.empty()) {
										message.append(" ");
									}
									message.append(result[i]);
								}

								// create & send message
								std::shared_ptr<C2S_Chat> c2s_chat(new C2S_Chat(message, result[1], ChatDstType::USER));
								Resource::resource->getChatClient()->pushInputBuffer(c2s_chat);

							}
							else {
								this->pushChat("> Usage: /w <user> <message>");
							}
						}
						// /f+ : add or confirm friend invitation
						else if(result[0].compare("f+") == 0) {
							if(result.size() == 2)
							{
								// create & send message
								std::shared_ptr<C2S_Command> c2s_cmd(new C2S_Command(ClientCommand::C_FRIEND_ADD, result[1]));
								Resource::resource->getChatClient()->pushInputBuffer(c2s_cmd);
							}
							else {
								this->pushChat("> Usage: /f+ <user>");
							}
						}
						// f- : delete player invitation
						else if(result[0].compare("f-") == 0) {
							if(result.size() == 2)
							{
								// create & send message
								std::shared_ptr<C2S_Command> c2s_cmd(new C2S_Command(ClientCommand::C_FRIEND_DEL, result[1]));
								Resource::resource->getChatClient()->pushInputBuffer(c2s_cmd);
							}
							else {
								this->pushChat("> Usage: /f- <user>");
							}
						}
						// f! : delete and ignore future invitation
						else if(result[0].compare("f!") == 0) {
							if(result.size() == 2)
							{
								// create & send message
								std::shared_ptr<C2S_Command> c2s_cmd(new C2S_Command(ClientCommand::C_FRIEND_IGNORE, result[1]));
								Resource::resource->getChatClient()->pushInputBuffer(c2s_cmd);
							}
							else {
								this->pushChat("> Usage: /f! <user>");
							}
						}
						// unknow command
						else {
							this->pushChat("> Unknow command. Use /help for more informations");
						}

					}
				}
			}
			// else, this is a chat message
			else
			{
				std::shared_ptr<C2S_Chat> c2s_chat(new C2S_Chat(userInput, "INTERNATIONAL", ChatDstType::CHANNEL));
				Resource::resource->getChatClient()->pushInputBuffer(c2s_chat);
			}

			txtfield.setValue("");
		}
	}

	this->txtfield.update(p_event);
	this->txtbox.update(p_event);
	this->txtboxUL.update(p_event);
	this->buttonSend.update(p_event);
	Window::update(p_event);
}

void WindowChat::drawContent()
{
	NetworkState ns = Resource::resource->getChatClient()->getNetworkState();
	if(ns.newState == true)
	{
		switch(ns.code)
		{
		case NetworkStateCode::NS_CONNECTING:
			{
				this->txtfield.setEnable(false);
				this->pushChat("* Connecting to chat server ...");
			}
			break;

		case NetworkStateCode::NS_CONNECTION_FAILED:
			{
				this->txtfield.setEnable(false);
				this->pushChat("* Connection to chat server failed.");
			}
			break;

		case NetworkStateCode::NS_CONNECTION_OK:
			{
				this->txtfield.setEnable(true);
				this->pushChat("* Welcome on White Hole chat server");
			}
			break;

		case NetworkStateCode::NS_DISCONNECTED:
			{
				this->txtfield.setEnable(false);
				this->pushChat("* Disconnected.");
			}
			break;

		case NetworkStateCode::NS_CONNECTION_OK_AUTHRESPONSE:
			{
				AuthResponse ar = Resource::resource->getChatClient()->getAuthResponse();
				if(ar == AuthResponse::AR_OK) {
					this->pushChat("* Authenticated.");
					this->txtfield.setEnable(true);
				}
				else {
					this->pushChat("* Authentication failed: "+Chat::authResponseToString(ar));
					this->txtfield.setEnable(false);
				}
				
			}
			break;
			
		default:
			this->txtfield.setEnable(false);
			break;

		}
		Resource::resource->getChatClient()->notifyNetworkState();
	}

	// txtfield
	this->txtfield.draw();


	// txtboxUL (userlist)
	std::string userListContent = "";
	std::vector<std::string> userList(Resource::resource->getChatClient()->getUserList());
	for(unsigned int i = 0; i < userList.size(); i++)
	{
		userListContent += userList[i]+"<br/>";
	}

	this->txtboxUL.setText(userListContent);
	this->txtboxUL.draw();


	// buttonSend
	this->buttonSend.draw();

	// txtbox = MUST BE DRAWN AFTER ALL COMPONENT
	{
		sf::Lock lock(Resource::resource->getChatClient()->getMutex());
		MessageBuffer outputbuffer(Resource::resource->getChatClient()->getOutputBuffer());

		// si packet buffer non vide, on envoie tout son contenu
		if(!outputbuffer.empty())
		{
			for(auto it = outputbuffer.begin(); it != outputbuffer.end(); ++it)
			{
				// Si c'est un message chat
				if((*it)->packetType == PacketType::CHAT) {
					std::shared_ptr<S2C_Chat> s2c_chat = std::dynamic_pointer_cast<S2C_Chat>(*it);

					if(s2c_chat->dstType == ChatDstType::CHANNEL)
						this->pushChat("<"+s2c_chat->from+"> "+s2c_chat->message);
					else if(s2c_chat->dstType == ChatDstType::USER)
					{
						if(Resource::resource->getChatClient()->getUsername().compare(s2c_chat->from) == 0)
							this->pushChat("(MP) to "+s2c_chat->to+" : "+s2c_chat->message);
						else
							this->pushChat("(MP) from "+s2c_chat->from+" : "+s2c_chat->message);
					}
					

				}
				// Si c'est une commande
				else if((*it)->packetType == PacketType::COMMAND) {
					std::shared_ptr<S2C_Command> s2c_command = std::dynamic_pointer_cast<S2C_Command>(*it);

					this->pushChat("<SERVER CMD> " + Chat::serverCmdToString(s2c_command->command) + " -> " + s2c_command->argument);
				}
			}
		}

		
		Resource::resource->getChatClient()->clearOutputBuffer();
	}

	this->txtbox.draw();
}

void WindowChat::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->txtfield.setPosition(getContentX()+TXTFIELD_X, getContentY()+TXTFIELD_Y);
	this->txtbox.setPosition(getContentX()+TXTBOX_X, getContentY()+TXTBOX_Y);
	this->buttonSend.setPosition(getContentX()+BUTTON_X, getContentY()+BUTTON_Y);
	this->txtboxUL.setPosition(getContentX()+UL_X, getContentY()+UL_Y);
}

void WindowChat::pushChat(std::string p_string)
{
	if(this->chatLines.size() >= MAX_CHAT_LINES) {
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