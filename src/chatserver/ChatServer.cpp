#include "ChatServer.h"
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


ChatServer::ChatServer(void)
{
}


void ChatServer::Create()
{
	Create(CHAT_SERVER_PORT);
}

void ChatServer::Create(sf::Uint16 port)
{

	//we should never have any running threads here so we don't need to lock
	mPort = port;


	//start the listen server in own thread
	mNetThread = std::unique_ptr<sf::Thread>(new sf::Thread(&ChatServer::mRunServer, this));
	mRunThread = true;
	mNetThread->launch();
}

void ChatServer::mRunServer(void)
{
	// Create a socket to listen to new connections
	sf::TcpListener listener;
	listener.listen(mPort);

	// Create a list to store the future clients
	std::list< std::shared_ptr<Client> > clients;

	// Create a selector
	sf::SocketSelector selector;

	// Add the listener to the selector
	selector.add(listener);

	// Enter loop to handle new connection and updating of server / clients
	while(mRunThread)
	{		
		//Make the selector wait for data on any socket
		if(selector.wait(sf::Time(sf::seconds(0.5f))))
		{
			//If there are available slots test the listener - TODO report server full to client
			if(selector.isReady(listener))
			{
				//The listener is ready: there is a pending connection
				std::shared_ptr<Client> client = std::shared_ptr<Client>(new Client);
				
				if(listener.accept(*client->socket) == sf::Socket::Done)
				{
					sf::Packet packet;
					if(clients.size() < MAX_CLIENTS)
					{
						//Add the new client to the clients list
						clients.push_back(client);

						//Add the new client to the selector so that we will
						//be notified when he sends something
						selector.add(*client->socket);

						//send motd to new client
						S2C_Command s2c_cmd(ServerCommand::MOTD, SERVER_MOTD);
						{
							sf::Lock lock(mMutex);
							packet << s2c_cmd;
						}
						client->socket->send(packet);
					}
					else
					{
						//send rejection message because server is full and tidy up
						S2C_Command s2c_cmd(ServerCommand::SAY, "Connection refused. Reason: Server full.");
						{
							sf::Lock lock(mMutex);
							packet << s2c_cmd;
						}
						client->socket->send(packet);
						client->socket->disconnect();
					}

				}
			}		
		}

	}
}