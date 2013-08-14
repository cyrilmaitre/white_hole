#include "ChatClient.h"
#include "signal.h"

sf::Mutex	ChatClient::mutex;
ChatBuffer	ChatClient::chatBuffer;

// ----------------------------------------------------------------------
// operator overloads for sf::Packet
// ----------------------------------------------------------------------
// * CLIENT to SERVER (send) *
// -- Chat
sf::Packet& operator << (sf::Packet& packet, const C2S_Chat c2s_chat)
{
	return packet << (sf::Uint16) PacketType::CHAT << c2s_chat.message << c2s_chat.to << c2s_chat.dstType;
}
// -- Commad
sf::Packet& operator << (sf::Packet& packet, const C2S_Command c2s_command)
{
	return packet << (sf::Uint16) PacketType::COMMAND << c2s_command.command << c2s_command.argument;
}

// * CLIENT to SERVER (receive) *
// -- Commad
sf::Packet& operator >> (sf::Packet& packet, S2C_Command& s2c_command)
{
	return packet >> s2c_command.command >> s2c_command.argument;
}

// -- Chat
sf::Packet& operator >> (sf::Packet& packet, S2C_Chat& s2c_chat)
{
	return packet >> s2c_chat.from >> s2c_chat.message >> s2c_chat.to >> s2c_chat.dstType; 
}



// ----------------------------------------------------------------------
// (con/de)structor
// ----------------------------------------------------------------------
ChatClient::ChatClient(void) : mServerPort(CHAT_SERVER_PORT), mServerIP(CHAT_SERVER_HOST), mRunning(false)
{
}


ChatClient::~ChatClient(void)
{
}

// ----------------------------------------------------------------------
// methods
// ----------------------------------------------------------------------
// <chatbuffer>
ChatBuffer& ChatClient::getChatBuffer()
{
	sf::Lock lock(ChatClient::mutex);
	return ChatClient::chatBuffer;
}

void ChatClient::pushChatBuffer(C2S_Chat& c2s_chat)
{
	sf::Lock lock(ChatClient::mutex);
	ChatClient::chatBuffer.push_back(c2s_chat);
}

void ChatClient::clearChatBuffer()
{
	sf::Lock lock(ChatClient::mutex);
	ChatClient::chatBuffer.clear();
	ChatClient::chatBuffer.shrink_to_fit();
}
// </chatbuffer>


void ChatClient::connect(void)
{
	mRunning = true;
	mRunClient();
}

bool ChatClient::sendPacket(sf::Packet& p_packet)
{
    bool packetSent = false;

	for(int i = 0; i < MAX_C_PACKETSEND_RETRY; i++)
    {
        // Si le packet a été envoyé
		if(mSocket.send(p_packet) == sf::Socket::Status::Done)
        {
            packetSent = true;
			{ std::ostringstream msg; msg << "[SEND] Packet sent - size=" << p_packet.getDataSize() << ""; Debug::msg(msg); }
            break;
        }
    }
    
    // Si on n'arrive à pas envoyer, on drop le client
    if(!packetSent) {
		{ std::ostringstream msg; msg << "[SEND] Error: Packet NOT sent ! - size=" << p_packet.getDataSize() << ""; Debug::msg(msg); }
    }

	return packetSent;
}


void ChatClient::handlePacket(sf::Packet& p_packet)
{	

	sf::Uint16 packetType;
	// Message type ? (command, chat?)
	if(p_packet >> packetType)
	{
		{ std::ostringstream msg; msg << "[RECV] Received data - ptype:" << packetType << " size:" << p_packet.getDataSize() << ""; Debug::msg(msg); }

		// Chat
		if(packetType == PacketType::CHAT)
		{
			S2C_Chat s2c_chat;
			if(p_packet >> s2c_chat)
			{
				{ std::ostringstream msg; msg << "[CHAT] FROM <" << s2c_chat.from << "> TO <" << s2c_chat.to << "("<< s2c_chat.dstType <<")> : " << s2c_chat.message << ""; Debug::msg(msg); }
			}
		}
		else if(packetType == PacketType::COMMAND)
		{
			S2C_Command s2c_command;
			if(p_packet >> s2c_command)
			{
				{ std::ostringstream msg; msg << "[CMD] #" << s2c_command.command << ":" << s2c_command.argument << ""; Debug::msg(msg); }
			}
		}
		else if(packetType == PacketType::AUTHENTICATION)
		{
		}
	}
	else
	{
		{ std::ostringstream msg; msg << "Error, can't retrieve packetType" << ""; Debug::msg(msg); }
	}
}

void ChatClient::mRunClient(void)
{
	{ std::ostringstream msg; msg << "Connecting to " << mServerIP.toString() << ":" << mServerPort << ""; Debug::msg(msg); }
	sf::Socket::Status status = mSocket.connect(mServerIP, mServerPort);

	if(status == sf::Socket::Status::Done)
	{
		{ std::ostringstream msg; msg << "Connection OK !" << ""; Debug::msg(msg); }

		// adding some messages to the buffer
		C2S_Chat c2s_chat;
		c2s_chat.dstType = ChatDstType::CHANNEL;
		c2s_chat.message = "Coucou";
		c2s_chat.to = "trololo";
		this->pushChatBuffer(c2s_chat);
		c2s_chat.message = "wésh";
		this->pushChatBuffer(c2s_chat);
		c2s_chat.message = "message 3";
		this->pushChatBuffer(c2s_chat);

		sf::Packet packet;
		while(mRunning)
		{
			// ------------------- Envoi --------------------------------------------------------------------------------
			// <Thread safe>
			{
				sf::Lock lock(ChatClient::mutex);
				ChatBuffer chatbuffer(ChatClient::getChatBuffer());

				// si packet buffer non vide, on envoie tout son contenu
				if(!chatbuffer.empty())
				{
					for(auto it = chatbuffer.begin(); it != chatbuffer.end(); ++it)
					{
						C2S_Chat c2s_chat = *it;
						sf::Packet packet;
						packet << c2s_chat;
						this->sendPacket(packet);
					}
				}

				ChatClient::clearChatBuffer();
			}
			// </Thread safe>

			// ------------------- Réception ----------------------------------------------------------------------------
			sf::Socket::Status status = mSocket.receive(packet);

			// Packet status ?
			if(status == sf::Socket::Status::Done)
			{
				{ std::ostringstream msg; msg << "Packet received successfuly" << ""; Debug::msg(msg); }
				this->handlePacket(packet);
			}
			else if(status == sf::Socket::Status::Disconnected)
			{
				{ std::ostringstream msg; msg << "Packet received with code: Status::Disconnected ("<< status << ")"; Debug::msg(msg); }
				this->disconnect();
			}
			else if(status == sf::Socket::Status::NotReady)
			{
				{ std::ostringstream msg; msg << "Packet received with code: Status::NotReady ("<< status << ")"; Debug::msg(msg); }
			}
			else if(status == sf::Socket::Status::Error)
			{
				{ std::ostringstream msg; msg << "Packet received with code: Status::Error ("<< status << ")"; Debug::msg(msg); }
			}
			else
			{
				{ std::ostringstream msg; msg << "(!) ERROR This code is not handle by SFML 2.0/2.1 : ("<< status << ")"; Debug::msg(msg); }
			}
			// ----------------------------------------------------------------------------------------------------------
			packet.clear();						// important
			sf::sleep(sf::milliseconds(10));	// for CPU
			// ----------------------------------------------------------------------------------------------------------
		}
	}
	else
	{
		{ std::ostringstream msg; msg << "(!) Couldn't connect to chat server, status : ("<< status << ")"; Debug::msg(msg); }
	}
}

void ChatClient::terminate(void)
{
	C2S_Command c2s_command(ClientCommand::C_QUIT, "Closed by user");
	sf::Packet packet;
	packet << c2s_command;
	this->sendPacket(packet);

	/*
	if(this->sendPacket(packet) == sf::Socket::Status::Done)
		this->disconnect();
	exit(1);
	*/
}

void ChatClient::disconnect(void)
{
	mRunning = false;
	mSocket.disconnect();
	{ std::ostringstream msg; msg << "Disconnected" << ""; Debug::msg(msg); }
}