#include "ChatClient.h"
#include "ChatServer.h"
#include "Debug.h"
#include "../space_2/ChatDefine.h"

// ----------------------------------------------------------------------
// operator overloads for sf::Packet
// ----------------------------------------------------------------------
// * CLIENT to SERVER (send) *
// -- Chat
sf::Packet& operator << (sf::Packet& packet, const C2S_Chat c2s_chat)
{
	return packet << c2s_chat.message << c2s_chat.to << c2s_chat.dstType;
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
ChatClient::ChatClient(void) : mServerPort(CHAT_SERVER_PORT), mServerIP(CHAT_SERVER_HOST)
{
}


ChatClient::~ChatClient(void)
{
}

// ----------------------------------------------------------------------
// methods
// ----------------------------------------------------------------------
void ChatClient::connect(void)
{
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
	{ std::ostringstream msg; msg << "[RECV] Received data - size:" << p_packet.getDataSize() << ""; Debug::msg(msg); }

	sf::Uint16 s2c_type;
	// Message type ? (command, chat?)
	if(p_packet >> s2c_type)
	{
		// Chat
		if(s2c_type == S2C_Type::CHAT)
		{
			S2C_Chat s2c_chat;
			if(p_packet >> s2c_chat)
			{
				{ std::ostringstream msg; msg << "[CHAT] FROM <" << s2c_chat.from << "> TO <" << s2c_chat.to << "("<< s2c_chat.dstType <<")> : " << s2c_chat.message << ""; Debug::msg(msg); }
			}
		}
		else if(s2c_type == S2C_Type::COMMAND)
		{
			S2C_Command s2c_command;
			if(p_packet >> s2c_command)
			{
				{ std::ostringstream msg; msg << "[CMD] #" << s2c_command.command << ":" << s2c_command.argument << ""; Debug::msg(msg); }
			}
		}
		else if(s2c_type == S2C_Type::AUTHENTICATION)
		{
		}
	}
	else
	{
		{ std::ostringstream msg; msg << "Error, can't retrieve s2c_type" << ""; Debug::msg(msg); }
	}
}

void ChatClient::mRunClient(void)
{
	{ std::ostringstream msg; msg << "Connecting to " << mServerIP.toString() << ":" << mServerPort << ""; Debug::msg(msg); }
	sf::Socket::Status status = mSocket.connect(mServerIP, mServerPort);

	if(status == sf::Socket::Status::Done)
	{
		{ std::ostringstream msg; msg << "Connection OK !" << ""; Debug::msg(msg); }


		C2S_Chat c2s_chat;
		c2s_chat.dstType = ChatDstType::CHANNEL;
		c2s_chat.message = "Coucou";
		c2s_chat.to = "trololo";
		sf::Packet packetSend;
		packetSend << c2s_chat;
		this->sendPacket(packetSend);

		sf::Packet packet;
		while(mRunning)
		{
			// ------------------- Envoi --------------------------------------------------------------------------------
			// si packet buffer non vide, on envoi

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
			packet.clear();
			// ----------------------------------------------------------------------------------------------------------

			sf::sleep(sf::seconds(0.1f));
		}
	}
	else
	{
		{ std::ostringstream msg; msg << "(!) Couldn't connect to chat server, status : ("<< status << ")"; Debug::msg(msg); }
	}
}

void ChatClient::disconnect(void)
{
	mRunning = false;
	mSocket.disconnect();
	{ std::ostringstream msg; msg << "Disconnected" << ""; Debug::msg(msg); }
}