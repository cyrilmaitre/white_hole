#include "ChatClient.h"
#include "signal.h"

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

// -- Auth
sf::Packet& operator << (sf::Packet& packet, const C2S_Auth c2s_auth)
{
	return packet << (sf::Uint16) PacketType::AUTHENTICATION << c2s_auth.user << c2s_auth.sha1password;
}



// * SERVER to CLIENT (receive) *
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

// -- Auth
sf::Packet& operator >> (sf::Packet& packet, S2C_Auth& s2c_auth)
{
	return packet >> s2c_auth.authResponse >> s2c_auth.optionnalMessage;
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
// <mutex>
sf::Mutex& ChatClient::getMutex()
{
	return this->mMutex;
}
// </mutex>

// <chatbuffer>
// out
const OutputBuffer& ChatClient::getOutputBuffer()
{
	sf::Lock lock(mMutex);
	return this->mOutputBuffer;
}

void ChatClient::clearOutputBuffer()
{
	sf::Lock lock(mMutex);
	mOutputBuffer.clear();
	mOutputBuffer.shrink_to_fit();
}

void ChatClient::pushOutputBuffer(S2C_Chat& s2c_chat)
{
	sf::Lock lock(mMutex);
	mOutputBuffer.push_back(s2c_chat);
}

// int
const InputBuffer& ChatClient::getInputBuffer()
{
	sf::Lock lock(mMutex);
	return this->mInputBuffer;
}

void ChatClient::pushInputBuffer(C2S_Chat& c2s_chat)
{
	sf::Lock lock(mMutex);
	mInputBuffer.push_back(c2s_chat);
}

void ChatClient::clearInputBuffer()
{
	sf::Lock lock(mMutex);
	mInputBuffer.clear();
	mInputBuffer.shrink_to_fit();
}
// </chatbuffer>


// Launch the thread connecting to the chat server
void ChatClient::connect(void)
{
	if(!mRunning)
	{
		mThread = std::unique_ptr<sf::Thread>(new sf::Thread(&ChatClient::mRunClient, this));
		mRunning = true;
		mThread->launch();
	}
	else
	{
		{ std::ostringstream msg; msg << "[ERR] Thread already running !" << ""; Debug::msg(msg); }
	}
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
				this->pushOutputBuffer(s2c_chat);
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
		this->pushInputBuffer(c2s_chat);
		c2s_chat.message = "wésh";
		this->pushInputBuffer(c2s_chat);
		c2s_chat.message = "message 3";
		this->pushInputBuffer(c2s_chat);


		sf::Packet packet;
		while(mRunning)
		{
			// ------------------- Envoi --------------------------------------------------------------------------------
			// <Thread safe>
			{
				sf::Lock lock(mMutex);
				InputBuffer chatbuffer(this->getInputBuffer());

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

				this->clearInputBuffer();
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
	sf::Lock lock(mMutex);

	C2S_Command c2s_command(ClientCommand::C_QUIT, "Closed by user");
	sf::Packet packet;
	packet << c2s_command;

	if(this->sendPacket(packet) == sf::Socket::Status::Done)
		this->disconnect();
}

void ChatClient::disconnect(void)
{
	sf::Lock lock(mMutex);

	mRunning = false;
	mSocket.disconnect();
	{ std::ostringstream msg; msg << "Disconnected" << ""; Debug::msg(msg); }
}