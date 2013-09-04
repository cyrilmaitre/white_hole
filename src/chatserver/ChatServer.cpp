#include "ChatServer.h"

// ----------------------------------------------------------------------
// operator overloads for sf::Packet
// ----------------------------------------------------------------------
// * SERVER to CLIENT (send) *
// -- Chat
sf::Packet& operator << (sf::Packet& packet, const S2C_Chat s2c_chat)
{
	return s2c_chat.insertIntoPacket(packet);
}

// -- Command
sf::Packet& operator << (sf::Packet& packet, const S2C_Command s2c_command)
{
	return s2c_command.insertIntoPacket(packet);
}

// -- Auth
sf::Packet& operator << (sf::Packet& packet, const S2C_Auth s2c_auth)
{
	return s2c_auth.insertIntoPacket(packet);
}


// * CLIENT to SERVER (receive) *
// -- Chat
sf::Packet& operator >> (sf::Packet& packet, C2S_Chat& c2s_chat)
{
	return packet >> c2s_chat.message >> c2s_chat.to >> c2s_chat.dstType;
}

// -- Command
sf::Packet& operator >> (sf::Packet& packet, C2S_Command& c2s_command)
{
	return packet >> c2s_command.command >> c2s_command.argument;
}

// -- Auth
sf::Packet& operator >> (sf::Packet& packet, C2S_Auth& c2s_auth)
{
	return packet >> c2s_auth.user >> c2s_auth.sha1password;
}

// ----------------------------------------------------------------------
// (con/de)structor
// ----------------------------------------------------------------------
ChatServer::ChatServer(void)
{
	mRunning = false;
}


// ----------------------------------------------------------------------
// methods
// ----------------------------------------------------------------------
void ChatServer::create()
{
	this->create((unsigned short)CHAT_SERVER_PORT);
}

void ChatServer::create(unsigned short port)
{

	mPort = port;
	this->mRunServer();
}

/*
	threaded method (main loop)
*/
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
		if(selector.wait(sf::Time(sf::microseconds(50))))
		{

			//If there are available slots test the listener
			if(selector.isReady(listener))
			{
				{ std::ostringstream msg; msg << "Selector is ready" << ""; Debug::msg(msg); }

				//The listener is ready: there is a pending connection
				std::shared_ptr<Client> client = std::make_shared<Client>();

				// non-blocking = big packets won't block server
				client->getSocket().setBlocking(false);		

				if(listener.accept(client->getSocket()) == sf::Socket::Done)
				{

					sf::Packet packet;
					// if server is not full
					if(clients.size() < MAX_CLIENTS)
					{

						// if max connections by ip not reached
						if(this->connectionCountByIP(client->getSocket().getRemoteAddress()) < MAX_IP_TOGETHER)
						{
							// client allowed
							this->addClient(client);

							//send motd to new client
							S2C_Command s2c_cmd(ServerCommand::S_MOTD, SERVER_MOTD);
							{
								packet << s2c_cmd;
							}

							this->sendPacket(packet, client);
						}
						else
						{
							//send rejection message because too many connections from same IP
							S2C_Command s2c_cmd(ServerCommand::S_SAY, "Connection refused. Reason: Too many connections from same IP.");
							{
								packet << s2c_cmd;
							}
							this->sendPacket(packet, client);
							this->dropClient(client);
						}
					}
					else
					{
						//send rejection message because server is full and tidy up
						S2C_Command s2c_cmd(ServerCommand::S_SAY, "Connection refused. Reason: Server full.");
						{
							packet << s2c_cmd;
						}
						this->sendPacket(packet, client);
						this->dropClient(client);
					}

				}
				else 
				{
					{ std::ostringstream msg; msg << "Error, can't get connection with client " << client->getSocket().getRemoteAddress() << ""; Debug::msg(msg); }
					this->dropClient(client);
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
						this->handlePacket(packet, client);
					}
					else if(status == sf::Socket::Status::Disconnected)
					{
						{ std::ostringstream msg; msg << "Packet received with code: Status::Disconnected ("<< status << ")"; Debug::msg(msg); }
						this->dropClient(client);
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

		}  // -- end of selector.wait


		// CHECK / UPDATES (ie: ping, auth, flood) -> "asynchronous jobs"
		for(unsigned int i = 0; i < clients.size(); i++)
		{
			std::shared_ptr<Client> client = clients[i];
			sf::Uint64 now = (sf::Uint64)time(NULL);

			// update flood control -> reset next control time. see handlePacket() for "counter-flood" actions
			if(client->getFloodControlTime() < now) {
				client->resetNbSentPackets();
				client->updateFloodControlTime();
			}

			// check auth timeot
			if(client->getState() == ClientState::TCP_CONNECTED && client->getConnectionTime()+AUTH_TIMEOUT < now){
				{ std::ostringstream msg; msg << "Client #" << client->getUniqueID() << " AUTH timeout (" << client->getSocket().getRemoteAddress() << ")"; Debug::msg(msg); }
				this->dropClient(client);
			}

			// check ping timeout
			if(client->isPongRequested())
			{
				if(client->getLastActivityTime()+PING_IDLE_TIME+PING_TIMEOUT < now) {
					{ std::ostringstream msg; msg << "Client #" << client->getUniqueID() << " PING timeout (" << client->getSocket().getRemoteAddress() << ")"; Debug::msg(msg); }
					this->dropClient(client);
				}
			}
			else
			{
				// if no ping requested, then request one if client is idling
				if(client->getLastActivityTime() != 0 && client->getLastActivityTime()+PING_IDLE_TIME < now)
				{
					client->requestPong();

					sf::Packet pingPacket;
					S2C_Command s2c_ping(ServerCommand::S_PING);
					pingPacket << s2c_ping;
					this->sendPacket(pingPacket, client);
				}
			}

		} // -- end of clients loop


	} // -- end of server main loop

	// Clear clients vector
	clients.clear();
	clients.shrink_to_fit();
}

/*
	add a client in vector & selector
*/
void ChatServer::addClient(std::shared_ptr<Client> p_client)
{
	p_client->setState(ClientState::TCP_CONNECTED);

	//Add the new client to the clients list
	clients.push_back(p_client);

	//Add the new client to the selector so that we will
	//be notified when he sends something
	selector.add(p_client->getSocket());

	{ std::ostringstream msg; msg << "Client #" << p_client->getUniqueID() << " added in clientlist: " << p_client->getSocket().getRemoteAddress() << ""; Debug::msg(msg); }
}

/*
	Authenticate the user
*/
void ChatServer::authenticate(std::shared_ptr<Client> p_client, C2S_Auth p_auth)
{
	{ std::ostringstream msg; msg << "[AUTH] user:" << p_auth.user << "- pass:" << p_auth.sha1password;	Debug::msg(msg); }
	// auth test here
	// set name after
	p_client->setName(p_auth.user);

	// if auth IDs OK...
	// already online ?
	std::shared_ptr<Client> dstClient = this->findClientByName(p_client->getName());

	// if client is already connected ..., kill the other
	if(dstClient.get() != 0)
	{
		S2C_Command s2c_cmd(ServerCommand::S_SAY, "Connection closed. Reason: Ghost kill");
		sf::Packet packet;
		packet << s2c_cmd;
		this->sendPacket(packet, dstClient);
		this->dropClient(dstClient);
	}
	


	// if tests above are OK
	if(true)
	{
		// client is now authed
		p_client->setState(ClientState::AUTHED); 
	
		// send him a response
		{
			sf::Packet packet;
			S2C_Auth s2c_auth(AuthResponse::AR_OK);
			packet << s2c_auth;
			this->sendPacket(packet, p_client);
		}

		// broadcast to all authed user that the user joined
		{
			sf::Packet packet;
			S2C_Command s2c_command(ServerCommand::S_JOIN, p_client->getName());
			packet << s2c_command;

			BroadcastCondition bc;
			bc.ignoreClientID = p_client->getUniqueID();
			bc.clientState = ClientState::AUTHED;

			this->broadcast(packet, bc);
		}
	}
	else
	{
		sf::Packet packet;
		S2C_Auth s2c_auth(AuthResponse::AR_INVALID_IDS);

		packet << s2c_auth;
		this->sendPacket(packet, p_client);
	}
}


/*
	remove client from selector & from vector (if in it)
*/
void ChatServer::dropClient(std::shared_ptr<Client> p_client)
{

	// broadcast disconnexion to all clients
	if(p_client->getState() == ClientState::AUTHED)
	{
		sf::Packet packet;
		S2C_Command s2c_command(ServerCommand::S_QUIT, p_client->getName());
		packet << s2c_command;

		BroadcastCondition bc;
		bc.ignoreClientID = p_client->getUniqueID();
		bc.clientState = ClientState::AUTHED;

		this->broadcast(packet, bc);
	}

	// disconnect
	p_client->setState(ClientState::DROPPED); // this might seems useless since it will be delete later. it's just a security.

	{ std::ostringstream msg; msg << "Client #" <<  p_client->getUniqueID() << " disconnected - " << p_client->getSocket().getRemoteAddress().toString() << "";	Debug::msg(msg); }

	selector.remove(p_client->getSocket());

    for (auto it = clients.begin(); it != clients.end();) {
        if (*it == p_client) {
            it = clients.erase(it);
			{ std::ostringstream msg; msg << "Clients size is now " << clients.size() << ""; Debug::msg(msg); }
		} else {
            it++;
		}
	}
}


/*
	send packet to a client, drop client if dropClientIfFailed=true
*/
bool ChatServer::sendPacket(sf::Packet& p_packet, std::shared_ptr<Client> p_client, bool dropClientIfFailed)
{
    bool packetSent = false;
    
    for(int i = 0; i < MAX_S_PACKETSEND_RETRY; i++)
    {
        // Si le packet a été envoyé
        if(p_client->getSocket().send(p_packet) == sf::Socket::Status::Done)
        {
            packetSent = true;
			{ std::ostringstream msg; msg << "[SEND] Packet sent - size=" << p_packet.getDataSize() << ""; Debug::msg(msg); }
            break;
        }
    }
    
    // Si on n'arrive à pas envoyer
    if(!packetSent) {
		p_client->notifyDroppedPacket();
		{ std::ostringstream msg; msg << "[SEND] Error: Packet NOT sent ! - size=" << p_packet.getDataSize() << ""; Debug::msg(msg); }

		if(dropClientIfFailed)
			this->dropClient(p_client);
    }

	return packetSent;
}



/*
	broadcast
*/
void ChatServer::broadcast(sf::Packet& p_packet, BroadcastCondition& p_broadcastCond)
{
	{ std::ostringstream msg; msg << "[BROADCAST] Starting..." << "";	Debug::msg(msg); }

	// Nb of client that will be sent messages
	sf::Uint64 targetedClients = 0;

	// Let's broadcast the message
	for(auto it = clients.begin(); it != clients.end(); ++it)
	{
		// CLIENT
		std::shared_ptr<Client> dstClient = *it;

		// CONDITIONS
		// 1. if UID condition && UID == client.UID => continue (= do not send to this client)
		if(p_broadcastCond.ignoreClientID != 0 && dstClient->getUniqueID() == p_broadcastCond.ignoreClientID)
			continue;

		// 2. if clientState condition && clientState != client.clientState (= wrong state, so do not send)
		if(p_broadcastCond.clientState != ClientState::UNKNOWN_CS && p_broadcastCond.clientState != dstClient->getState())
			continue;

		// 3. if attributes condition && client has not this clientatttribute
		if(p_broadcastCond.clientHasAttributes != ClientAttributes::ATTR_NONE && !dstClient->hasAttribute(p_broadcastCond.clientHasAttributes))
			continue;

		
		// SEND
		this->sendPacket(p_packet, dstClient);
		++targetedClients;

	} // -- end of broadcast loop

	{ std::ostringstream msg; msg << "[BROADCAST] Finished - Sent to " << targetedClients << "/" << clients.size() << " clients" << "";	Debug::msg(msg); }
}


/*
	handle every packet received
*/
void ChatServer::handlePacket(sf::Packet& p_packet, std::shared_ptr<Client> p_client)
{	
	// Flood control
	// -- if client is not flooding
	if(p_client->getNbSentPackets() < FLOOD_MAX_PACKETS) {
		p_client->notifySentPacket();
	}
	else {
		{ std::ostringstream msg; msg << "Client #" << p_client->getUniqueID() << " excess FLOOD (" << p_client->getSocket().getRemoteAddress() << ")"; Debug::msg(msg); }
		this->dropClient(p_client);
		return;
	}

	// Message type ? (command, chat?)
	sf::Uint16 packetType;

	if(!(p_packet >> packetType))
	{
		{ std::ostringstream msg; msg << "Error, can't retrieve packetType" << ""; Debug::msg(msg); }
		return;
	}

	{ std::ostringstream msg; msg 
		<< "[RECV] Received data - cstate:" << p_client->getState() 
		<< " / ptype:" << packetType 
		<< " / psize:" << p_packet.getDataSize() << ""; Debug::msg(msg); }


	// If client is authed
	switch(p_client->getState())
	{
	case ClientState::TCP_CONNECTED:
		{
			if(packetType == PacketType::AUTHENTICATION)
			{
				C2S_Auth c2s_auth;
				if(p_packet >> c2s_auth)
				{
					this->authenticate(p_client, c2s_auth);
				}
				else
				{
					{ std::ostringstream msg; msg << "Malformed auth packet" << "";	Debug::msg(msg); }
				}
			}
			
		}
		break;

	case ClientState::AUTHED:
		{
			// Update activity time
			p_client->notifyLastActivityTime();

			// --------------------------------------------------
			// ---------------------- CHAT ----------------------
			// --------------------------------------------------
			// If client can speak
			if(packetType == PacketType::CHAT && !(p_client->hasAttribute(ClientAttributes::ATTR_MUTED)))
			{
				// We expect only chat messages from client at the moment
				C2S_Chat c2s_chat;

				// If we can read the message
				if(p_packet >> c2s_chat)
				{
					// We receive this:
					//(std::string)	c2s_chat.message;
					//(std::string)	c2s_chat.to;
					//(sf::Uint16)	c2s_chat.dstType;
					S2C_Chat s2c_chat;
					sf::Packet packet;
			
					s2c_chat.from = p_client->getName();
					s2c_chat.to = c2s_chat.to;
					s2c_chat.message = c2s_chat.message;
					s2c_chat.dstType = c2s_chat.dstType;

					packet << s2c_chat;

					// CHANNEL message
					// Let's broadcast the message to all authed users
					if(s2c_chat.dstType == ChatDstType::CHANNEL)
					{
						BroadcastCondition bc;
						bc.ignoreClientID = p_client->getUniqueID();
						bc.clientState = ClientState::AUTHED;

						this->broadcast(packet, bc);
					}
					// PRIVATE message
					else if(s2c_chat.dstType == ChatDstType::USER)
					{
						// if sender != receiver (you can't send a msg to yourself !)
						if(p_client->getName().compare(s2c_chat.to) != 0)
						{
							std::shared_ptr<Client> dstClient = this->findClientByName(s2c_chat.to);

							// if client has been found
							if(dstClient.get() != 0)
							{
								// if client is not AFK
								if(!dstClient->hasAttribute(ClientAttributes::ATTR_AFK))
								{
									this->sendPacket(packet, dstClient);
								}
								else {
									S2C_Command s2c_command(ServerCommand::S_CHAT_PEER_AFK, s2c_chat.to);
									sf::Packet peerAFKPacket;
									peerAFKPacket << s2c_command;
									this->sendPacket(peerAFKPacket, p_client);
								}
							}
							else
							{
								S2C_Command s2c_command(ServerCommand::S_CHAT_PEER_OFFLINE, s2c_chat.to);
								sf::Packet peerOfflinePacket;
								peerOfflinePacket << s2c_command;
								this->sendPacket(peerOfflinePacket, p_client);
							}
						}
					}
				}
				else
				{
					{ std::ostringstream msg; msg << "Malformed chat packet" << "";	Debug::msg(msg); }
				}

			} // -- end of packetType=CHAT && client can speak

			// --------------------------------------------------
			// --------------------- COMMAND --------------------
			// --------------------------------------------------
			else if(packetType == PacketType::COMMAND)
			{
				C2S_Command c2s_command;
				// If we can read the message
				if(p_packet >> c2s_command)
				{
					// switch on command ID
					switch(c2s_command.command)
					{
						// PONG
					case ClientCommand::C_PONG:
						{
							if(p_client->isPongRequested())
								p_client->notifyPong();
						}
						break;

						// AFK
					case ClientCommand::C_AFK:
						{
							// if already afk, disable AFK mode
							if(p_client->hasAttribute(ClientAttributes::ATTR_AFK)) {

								p_client->removeAttribute(ClientAttributes::ATTR_AFK);

								S2C_Command s2_command(ServerCommand::S_AFK_OFF);
								sf::Packet packet;
								packet << s2_command;

								this->sendPacket(packet, p_client);
							}
							// else, enable AFK mode
							else {
								p_client->addAttribute(ClientAttributes::ATTR_AFK);
								
								S2C_Command s2c_command(ServerCommand::S_AFK_ON);
								sf::Packet packet;
								packet << s2c_command;

								this->sendPacket(packet, p_client);
							}

						}
						break;

						// QUIT
					case ClientCommand::C_QUIT:
						{
							// drop the client since he wants to leave
							this->dropClient(p_client);

						}
						break;

						// NOTHING
					default:
						break;
					}
				}
				else
				{
					{ std::ostringstream msg; msg << "Malformed command packet" << "";	Debug::msg(msg); }
				}
			}
			
		}
		break;
			
	case ClientState::DROPPED:
	case ClientState::UNKNOWN_CS:
		{
			// holy shit, this case shouldn't happen
			
		}
		break;

	default:
		{
			// holy shit, this case shouldn't happen
			
		}		
		break;
	}
}


std::shared_ptr<Client> ChatServer::findClientByName(std::string p_name)
{
	std::shared_ptr<Client> foundClient(nullptr);
	for(auto it = clients.begin(); it != clients.end(); ++it)
	{
		// CLIENT
		std::shared_ptr<Client> currentClient = *it;
		if(currentClient->getState() == ClientState::AUTHED && currentClient->getName().compare(p_name) == 0)
		{
			foundClient = currentClient;
			break;
		}
	}

	return foundClient;
}

std::shared_ptr<Client> ChatServer::findClientByUID(sf::Uint64 p_uid)
{
	std::shared_ptr<Client> foundClient(nullptr);
	for(auto it = clients.begin(); it != clients.end(); ++it)
	{
		// CLIENT
		std::shared_ptr<Client> currentClient = *it;
		if(currentClient->getState() == ClientState::AUTHED && currentClient->getUniqueID() == p_uid)
		{
			foundClient = currentClient;
			break;
		}
	}

	return foundClient;
}


sf::Uint32 ChatServer::connectionCountByIP(sf::IpAddress compareIP)
{
	sf::Uint32 count = 0;

	for(auto it = clients.begin(); it != clients.end(); ++it)
	{
		// CLIENT
		std::shared_ptr<Client> currentClient = *it;
		if(currentClient->getSocket().getRemoteAddress() == compareIP)
			count++;
	}

	return count;
}