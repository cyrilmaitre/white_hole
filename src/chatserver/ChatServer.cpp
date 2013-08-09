#include "ChatServer.h"
#include "Debug.h"
#include "../space_2/ChatDefine.h"

///***operator overloads for sf::Packet***///
// * SERVER to CLIENT *
// -- Chat
sf::Packet& operator << (sf::Packet& packet, const S2C_Chat s2c_chat)
{
	return packet << S2C_Type::CHAT << s2c_chat.from << s2c_chat.message << s2c_chat.to << s2c_chat.dstType;
}
// -- Command
sf::Packet& operator << (sf::Packet& packet, const S2C_Command s2c_command)
{
	return packet << S2C_Type::COMMAND << s2c_command.command << s2c_command.argument;
}

// * CLIENT to SERVER *
// -- Chat
sf::Packet& operator >> (sf::Packet& packet, C2S_Chat& c2s_chat)
{
	return packet >> c2s_chat.message >> c2s_chat.to >> c2s_chat.dstType;
}


ChatServer::ChatServer(void)
{
	mRunning = false;
}


void ChatServer::Create()
{
	Create((unsigned short)CHAT_SERVER_PORT);
}

void ChatServer::Create(unsigned short port)
{

	mPort = port;
	mRunServer();
}

void ChatServer::mRunServer(void)
{
	// Create a socket to listen to new connections
	sf::Socket::Status status = listener.listen(mPort);

	if(status != sf::Socket::Status::Done) {
		{ std::ostringstream msg; msg << "Unable to bind port: " << mPort << ""; Debug::msg(msg); }
		exit(EXIT_FAILURE);
	}
	{ std::ostringstream msg; msg << "Server starting on port: " << mPort << ". Listener blocking: " << listener.isBlocking() << ""; Debug::msg(msg); }

	// Add the listener to the selector
	selector.add(listener);

	//
	mRunning = true;

	// Enter loop to handle new connection and updating of server / clients
	while(mRunning)
	{		
		//Make the selector wait for data on any socket
		if(selector.wait())
		{
			//If there are available slots test the listener
			if(selector.isReady(listener))
			{
				{ std::ostringstream msg; msg << "Selector is ready" << ""; Debug::msg(msg); }

				//The listener is ready: there is a pending connection
				std::shared_ptr<Client> client = std::shared_ptr<Client>(new Client);
				client->getSocket().setBlocking(false);

				if(listener.accept(client->getSocket()) == sf::Socket::Done)
				{

					sf::Packet packet;
					if(clients.size() < MAX_CLIENTS)
					{
						//adding new client (not authenticated at the moment, just tcp connected)
						AddClient(client);

						//send motd to new client
						S2C_Command s2c_cmd(ServerCommand::MOTD, SERVER_MOTD);
						{
							packet << s2c_cmd;
						}
						SendPacket(packet, client);
					}
					else
					{
						//send rejection message because server is full and tidy up
						S2C_Command s2c_cmd(ServerCommand::SAY, "Connection refused. Reason: Server full.");
						{
							packet << s2c_cmd;
						}
						SendPacket(packet, client);
						DropClient(client);
					}

				}
				else 
				{
					{ std::ostringstream msg; msg << "Error, can't get connection with client " << client->getSocket().getRemoteAddress() << ""; Debug::msg(msg); }
					DropClient(client);
				}

			} // -- end of server listener ready


			//The listener socket is not ready, test all other sockets (the clients)
			for(unsigned int i = 0; i < clients.size(); i++)
			{
				std::shared_ptr<Client> client = clients[i];
				sf::Packet packet;

				//check to see if we can receive data
				if (selector.isReady(client->getSocket()))
				{

					//The client has sent some data, we can receive it
					sf::Socket::Status status = client->getSocket().receive(packet);

					// Packet status ?
					if(status == sf::Socket::Status::Done)
					{
						{ std::ostringstream msg; msg << "Packet received successfuly" << ""; Debug::msg(msg); }
						HandlePacket(packet, client);
					}
					else if(status == sf::Socket::Status::Disconnected)
					{
						{ std::ostringstream msg; msg << "Packet received with code: Status::Disconnected ("<< status << ")"; Debug::msg(msg); }
						DropClient(client);
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

				} // -- end of client socket ready

			} // -- end of clients loop

		} 


	} // -- end of server main loop

	// Clear clients vector
	clients.clear();
	clients.shrink_to_fit();
}


void ChatServer::AddClient(std::shared_ptr<Client> client)
{
	client->setState(ClientState::TCP_CONNECTED);

	//Add the new client to the clients list
	clients.push_back(client);

	//Add the new client to the selector so that we will
	//be notified when he sends something
	selector.add(client->getSocket());

	{ std::ostringstream msg; msg << "Client " << clients.size() << "added in clientlist: " << client->getSocket().getRemoteAddress() << ""; Debug::msg(msg); }
}


void ChatServer::DropClient(std::shared_ptr<Client> client)
{
	client->setState(ClientState::DROPPED); // this might seems useless since it will be delete later. it's just a security.

	{ std::ostringstream msg; msg << "Client disconnected - " << client->getSocket().getRemoteAddress().toString() << "";	Debug::msg(msg); }

	selector.remove(client->getSocket());

	std::vector<std::shared_ptr<Client>>::iterator it;
    for (it = clients.begin(); it != clients.end();) {
        if (*it == client) {
            it = clients.erase(it);
			{ std::ostringstream msg; msg << "Clients size is now " << clients.size() << ""; Debug::msg(msg); }
		} else {
            it++;
		}
	}
}

bool ChatServer::SendPacket(sf::Packet &packet, std::shared_ptr<Client> client)
{
    bool packetSent = false;
    
    for(int i = 0; i < MAX_PACKETSEND_RETRY; i++)
    {
        // Si le packet a été envoyé
        if(client->getSocket().send(packet) == sf::Socket::Status::Done)
        {
            packetSent = true;
			{ std::ostringstream msg; msg << "[SEND] Packet sent - size=" << packet.getDataSize() << ""; Debug::msg(msg); }
            break;
        }
    }
    
    // Si on n'arrive à pas envoyer, on drop le client
    if(!packetSent) {
		{ std::ostringstream msg; msg << "[SEND] Error: Packet NOT sent ! - size=" << packet.getDataSize() << ""; Debug::msg(msg); }
        DropClient(client);
    }

	return packetSent;
}


void ChatServer::HandlePacket(sf::Packet& packet, std::shared_ptr<Client> client)
{	
	{ std::ostringstream msg; msg << "[RECV] Received data - size:" << packet.getDataSize() << ""; Debug::msg(msg); }

	// If client is authed
	switch(client->getState())
	{
	case ClientState::TCP_CONNECTED:
		{
			// Should auth something around there
			break;
		}

	case ClientState::AUTHED:
		{

			// If client can speak
			if(!(client->hasAttribute(ClientAttributes::ATTR_MUTED)))
			{
				// We expect only chat messages from client at the moment
				C2S_Chat c2s_chat;

				// If we can read the message
				if(packet >> c2s_chat)
				{
					// We receive this:
					//(std::string)	c2s_chat.message;
					//(std::string)	c2s_chat.to;
					//(sf::Uint16)	c2s_chat.dstType;
					S2C_Chat s2c_chat;
					sf::Packet packet;
			
					s2c_chat.from = client->getName();
					s2c_chat.to = c2s_chat.to;
					s2c_chat.message = c2s_chat.message;
					s2c_chat.dstType = c2s_chat.dstType;

					packet << s2c_chat;

					// Let's broadcast the message to all authed users
					for(auto it = clients.begin(); it != clients.end(); ++it)
					{
						std::shared_ptr<Client> dstClient = *it;
						if(dstClient->getState() == ClientState::AUTHED)
						{
							{ std::ostringstream msg; msg << "broadcast to: " << client->getSocket().getRemoteAddress().toString() << "";	Debug::msg(msg); }
							SendPacket(packet, dstClient);
						}

					}
				}
				else
				{
					{ std::ostringstream msg; msg << "Malformed packet" << "";	Debug::msg(msg); }
				}

			} // -- end of client can speak
			break;
		}
			
	case ClientState::DROPPED:
	case ClientState::UNKNOWN_CS:
		{
			// holy shit, this case shouldn't happen
			break;
		}

	default:
		{
			// holy shit, this case shouldn't happen
			break;
		}
	}
}
