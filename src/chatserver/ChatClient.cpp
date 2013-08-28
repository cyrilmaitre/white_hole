#include "ChatClient.h"

// ----------------------------------------------------------------------
// operator overloads for sf::Packet
// ----------------------------------------------------------------------
// * CLIENT to SERVER (send) *
// -- Chat
sf::Packet& operator << (sf::Packet& packet, const C2S_Chat c2s_chat)
{
	return c2s_chat.insertIntoPacket(packet);
}
// -- Commad
sf::Packet& operator << (sf::Packet& packet, const C2S_Command c2s_command)
{
	return c2s_command.insertIntoPacket(packet);
}

// -- Auth
sf::Packet& operator << (sf::Packet& packet, const C2S_Auth c2s_auth)
{
	return c2s_auth.insertIntoPacket(packet);
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
ChatClient::ChatClient(void) : mServerPort(CHAT_SERVER_PORT), mServerIP(CHAT_SERVER_HOST), mRunning(false), lastSentStatus(sf::Socket::Status::Error)
{
}


ChatClient::~ChatClient(void)
{
}

// ----------------------------------------------------------------------
// methods
// ----------------------------------------------------------------------
//<running>
bool ChatClient::isRunning(void)
{
	sf::Lock lock(mMutex);
	return this->mRunning;
}
// </running>

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

void ChatClient::pushOutputBuffer(std::shared_ptr<Message> p_message)
{
	sf::Lock lock(mMutex);
	mOutputBuffer.push_back(p_message);
}

// int
const InputBuffer& ChatClient::getInputBuffer()
{
	sf::Lock lock(mMutex);
	return this->mInputBuffer;
}

void ChatClient::pushInputBuffer(std::shared_ptr<Message> p_message)
{
	sf::Lock lock(mMutex);
	mInputBuffer.push_back(p_message);
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
		this->lastSentStatus = mSocket.send(p_packet);
		if(this->lastSentStatus == sf::Socket::Status::Done)
        {
            packetSent = true;
			{ std::ostringstream msg; msg << "[SEND] Packet sent - size=" << p_packet.getDataSize() << ""; Debug::msg(msg); }
            break;
        }
    }
    
    // Si on n'arrive à pas envoyer, on drop le client
    if(!packetSent) {
		{ std::ostringstream msg; msg << "[SEND] Error: Packet NOT sent ! - size=" << p_packet.getDataSize() << " after " << MAX_C_PACKETSEND_RETRY << " attemps"; Debug::msg(msg); }
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
			std::shared_ptr<S2C_Chat> s2c_chat(new S2C_Chat);
			if(p_packet >> *s2c_chat)
			{
				this->pushOutputBuffer(s2c_chat);
				{ std::ostringstream msg; msg << "[CHAT] FROM <" << s2c_chat->from << "> TO <" << s2c_chat->to << "("<< s2c_chat->dstType <<")> : " << s2c_chat->message << ""; Debug::msg(msg); }
			}
		}
		// Command
		else if(packetType == PacketType::COMMAND)
		{
			std::shared_ptr<S2C_Command> s2c_command(new S2C_Command);
			if(p_packet >> *s2c_command)
			{
				this->pushOutputBuffer(s2c_command);
				{ std::ostringstream msg; msg << "[CMD] #" << s2c_command->command << ":" << s2c_command->argument << ""; Debug::msg(msg); }

				// switch command ID
				switch(s2c_command->command)
				{
					// PING request
				case ServerCommand::S_PING:
					{
						C2S_Command c2s_pong(ClientCommand::C_PONG);
						sf::Packet pongPacket;
						pongPacket << c2s_pong;
						this->sendPacket(pongPacket);
					}
					break;
				}
			}
		}
		// Auth
		else if(packetType == PacketType::AUTHENTICATION)
		{

			std::shared_ptr<S2C_Auth> s2c_auth(new S2C_Auth);
			if(p_packet >> *s2c_auth)
			{
				this->pushOutputBuffer(s2c_auth);
				{ std::ostringstream msg; msg << "[AUTH] #" << s2c_auth->authResponse << ""; Debug::msg(msg); }
			}
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

	// WORKAROUND
	// bug avec socket non bloquantes : https://github.com/LaurentGomila/SFML/issues/194
	sf::Socket::Status status = sf::Socket::Error;

	if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
	{
			mSocket.disconnect();
			mSocket.setBlocking(false);
			unsigned int max_retry = 50;
			unsigned int attempt = 0;
			while(true) {
				{ std::ostringstream msg; msg << "Attempt " << attempt << "/" << max_retry << ""; Debug::msg(msg); }
				status = mSocket.connect(mServerIP, mServerPort);
				if(status == sf::Socket::Status::Done)
					break;
				
				if(++attempt >= 50) {
					{ std::ostringstream msg; msg << "Connection FAILED !" << ""; Debug::msg(msg); }
					break;
				}

				sf::sleep(sf::milliseconds(100));	// for CPU
			}

	}
	if(status == sf::Socket::Status::Done)
	{
		{ std::ostringstream msg; msg << "Connection OK !" << ""; Debug::msg(msg); }

		// TEST : adding some messages to the buffer
		std::shared_ptr<C2S_Auth> auth(new C2S_Auth("username", "password"));
		this->pushInputBuffer(auth);
		std::shared_ptr<C2S_Chat> msg1(new C2S_Chat("Message 1", "ok", ChatDstType::CHANNEL));
		std::shared_ptr<C2S_Chat> msg2(new C2S_Chat("Message 2", "babouche", ChatDstType::USER));
		std::shared_ptr<C2S_Chat> msg3(new C2S_Chat("Message 3", "mazouteman", ChatDstType::CHANNEL));
		this->pushInputBuffer(msg1);
		this->pushInputBuffer(msg2);

		// Flood testing
		for(unsigned int i = 0; i < 300; i++) {
			this->pushInputBuffer(msg3);
		}
		

		sf::Packet packet;
		while(this->isRunning())
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
						sf::Packet packet;
						(*it)->insertIntoPacket(packet);
						// if packet not sent && status = disconnected, then stop sending
						if(!this->sendPacket(packet) && this->lastSentStatus == sf::Socket::Status::Disconnected) {
							this->disconnect();
							break;
						}

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
				//{ std::ostringstream msg; msg << "Packet received with code: Status::NotReady ("<< status << ")"; Debug::msg(msg); }
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
			sf::sleep(sf::milliseconds(100));	// for CPU
			// ----------------------------------------------------------------------------------------------------------
		}
	}
	else
	{
		{ std::ostringstream msg; msg << "(!) Couldn't connect to chat server, status : ("<< status << ")"; Debug::msg(msg); }
	}
	
	{ std::ostringstream msg; msg << "Thread ended" << ""; Debug::msg(msg); }
}

void ChatClient::terminate(void)
{
	sf::Lock lock(mMutex);

	if(this->isRunning())
	{
		this->clearOutputBuffer();
		this->clearInputBuffer();

		C2S_Command c2s_command(ClientCommand::C_QUIT, "Closed by user");
		sf::Packet packet;
		packet << c2s_command;

		this->sendPacket(packet);
		this->disconnect();
	}
}

void ChatClient::disconnect(void)
{
	sf::Lock lock(mMutex);
	mRunning = false;
	mSocket.disconnect();
	{ std::ostringstream msg; msg << "Disconnected" << ""; Debug::msg(msg); }
}