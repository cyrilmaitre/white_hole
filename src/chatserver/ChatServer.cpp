#include "ChatServer.h"
#include <json\json.h>

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
	// properties size veritifcation
	// msg
	if(c2s_chat.message.length() > MAX_SIZE_USERNAME) {
		c2s_chat.message.substr(0,MAX_SIZE_USERNAME);
	}

	// username OR channel
	if(c2s_chat.dstType == ChatDstType::USER) {
		if(c2s_chat.to.length() > MAX_SIZE_USERNAME)
			c2s_chat.to.substr(0,MAX_SIZE_USERNAME);
	}
	else if(c2s_chat.dstType == ChatDstType::CHANNEL) {
		if(c2s_chat.to.length() > MAX_SIZE_CHANNEL)
			c2s_chat.to.substr(0,MAX_SIZE_CHANNEL);
	}

	return packet >> c2s_chat.message >> c2s_chat.to >> c2s_chat.dstType;
}

// -- Command
sf::Packet& operator >> (sf::Packet& packet, C2S_Command& c2s_command)
{
	// properties size veritifcation
	// msg
	if(c2s_command.argument.length() > MAX_SIZE_CMDARG) {
		c2s_command.argument.substr(0,MAX_SIZE_CMDARG);
	}

	return packet >> c2s_command.command >> c2s_command.argument;
}

// -- Auth
sf::Packet& operator >> (sf::Packet& packet, C2S_Auth& c2s_auth)
{
	// properties size veritifcation
	// username
	if(c2s_auth.user.length() > MAX_SIZE_USERNAME) {
		c2s_auth.user.substr(0,MAX_SIZE_USERNAME);
	}

	// sha1password
	if(c2s_auth.sha1password.length() > MAX_SIZE_PASSWORD) {
		c2s_auth.sha1password.substr(0,MAX_SIZE_PASSWORD);
	}

	return packet >> c2s_auth.user >> c2s_auth.sha1password;
}

// ----------------------------------------------------------------------
// (con/de)structor
// ----------------------------------------------------------------------
ChatServer::ChatServer(void) : mRunning(false)
{
}


// ----------------------------------------------------------------------
// methods
// ----------------------------------------------------------------------
// <mutex>
sf::Mutex& ChatServer::getMutex()
{
	return this->mMutex;
}
// </mutex>


//<running>
bool ChatServer::isRunning(void)
{
	sf::Lock lock(mMutex);
	return this->mRunning;
}

void ChatServer::setRunning(bool p_running)
{
	sf::Lock lock(mMutex);
	{ std::ostringstream msg; msg << "[PROP] mRunning changed to <" << (p_running ? "TRUE" : "FALSE") << ">"; Debug::msg(msg); }
	this->mRunning = p_running;
}
// </running>


void ChatServer::create()
{
	this->create((unsigned short)CHAT_SERVER_PORT);
}

void ChatServer::create(unsigned short port)
{

	this->mPort = port;

	if(!this->isRunning())
	{
		this->mRunServer();
	}
	else
	{
		{ std::ostringstream msg; msg << "[ERR] Server already running !" << ""; Debug::msg(msg); }
	}
	
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
	this->setRunning(true);

	// -- ASYNC JOBS --
	// Async friendlists job
	this->mThread = std::unique_ptr<sf::Thread>(new sf::Thread(&ChatServer::mAsyncTasks, this));
	this->mThread->launch();


	// -- SERVER MAIN LOOP --
	// Enter loop to handle new connection and updating of server / clients
	while(this->isRunning())
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
							S2C_Command s2c_cmd(ServerCommand::S_DROPPED_NORC, "Too many connections from same IP");
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
						S2C_Command s2c_cmd(ServerCommand::S_DROPPED_NORC, "Chat server is full");
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


		// CHECK / UPDATES (ie: ping, auth, flood) -> "asynchronous" jobs, low CPU time
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

	// May be useful for all async jobs to stop
	this->setRunning(false);

	// Clear clients vector
	this->clients.clear();
	this->clients.shrink_to_fit();
}

/*
	add a client in vector & selector
*/
void ChatServer::addClient(std::shared_ptr<Client> p_client)
{
	sf::Lock lock(mMutex);
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
// test (temp method)
bool ChatServer::authenticate(std::shared_ptr<Client> p_client)
{
	sf::Lock lock(mMutex);
	return this->authenticate(p_client, C2S_Auth(p_client->getUsername(), p_client->getSha1Password()));
}

bool ChatServer::authenticate(std::shared_ptr<Client> p_client, C2S_Auth p_auth)
{
	sf::Lock lock(mMutex);

	{ std::ostringstream msg; msg << "[AUTH] user:" << p_auth.user << " - pass:" << p_auth.sha1password;	Debug::msg(msg); }

	// ---------------------------------------------------------------------------------------
	// auth test (JSON request)
	AuthResponse authResponseFail = AuthResponse::AR_NONE;
	bool authSuccessful = false;

	Json::Value jsonRequest;
	jsonRequest["username"] = p_auth.user;
	jsonRequest["password"] = p_auth.sha1password;

	Json::StyledWriter writer;
	sf::Http::Response response = Chat::sendJsonRequest(sf::Http::Request::Post, "/SpaceUMad/resources/user/login", writer.write(jsonRequest));
	Json::Value* jsonResponse = new Json::Value();   
	Json::Reader reader;
	bool parsingSuccessfull = reader.parse(response.getBody(), *jsonResponse);
	if(parsingSuccessfull)
	{
		if(jsonResponse->get("authenticated", "false").asString() == "true")
		{
			authSuccessful = true;
		} else {
			authResponseFail = AuthResponse::AR_INVALID_IDS;
		}
	} else {
		// error from the server ?
		authResponseFail = AuthResponse::AR_ERROR;
	}
	// -- end of auth test (JSON request) ----------------------------------------------------


	// If login+password are OKs
	if(authSuccessful)
	{
		// set name after
		p_client->setName(p_auth.user);

		// if auth IDs OK...
		// already online ?
		std::shared_ptr<Client> dstClient = this->findClientByName(p_client->getName());

		// if client is already connected ..., kill the other
		if(dstClient.get() != 0)
		{
			S2C_Command s2c_cmd(ServerCommand::S_DROPPED_NORC, "Ghost kill (by "+p_client->getSocket().getRemoteAddress().toString()+")");
			sf::Packet packet;
			packet << s2c_cmd;
			this->sendPacket(packet, dstClient);
			this->dropClient(dstClient);
		}

		// client is now authed
		p_client->setState(ClientState::AUTHED); 
		// client will now receive pong requests if inactive
		p_client->notifyLastActivityTime();

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
	// if auth not successful...
	else
	{
		sf::Packet packet;
		S2C_Auth s2c_auth(authResponseFail);

		packet << s2c_auth;
		this->sendPacket(packet, p_client);
	}

	// auth test done, so clear IDs from memory
	{
		sf::Lock lock(mMutex);
		p_client->clearIDs();
	}

	return authSuccessful;
}


/*
	remove client from selector & from vector (if in it)
*/
void ChatServer::dropClient(std::shared_ptr<Client> p_client)
{
	sf::Lock lock(mMutex);

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
					{
					sf::Lock lock(mMutex);
					p_client->setIDs(c2s_auth.user, c2s_auth.sha1password);
					this->mAsyncRequests.push_back(AsyncRequest(p_client, AsyncRequestCode::ASR_AUTHENTICATE));
					}
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
						//bc.ignoreClientID = p_client->getUniqueID();
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
							if(dstClient.get() != 0 && dstClient->getState() == ClientState::AUTHED)
							{
								// if client is not AFK
								if(!dstClient->hasAttribute(ClientAttributes::ATTR_AFK))
								{
									this->sendPacket(packet, p_client);
									this->sendPacket(packet, dstClient);
								}
								else {
									// notify sender that the receiver is AFK
									S2C_Command s2c_command(ServerCommand::S_CHAT_PEER_AFK, s2c_chat.to);
									sf::Packet peerAFKPacket;
									peerAFKPacket << s2c_command;
									this->sendPacket(peerAFKPacket, p_client);
								}
							}
							else
							{
								// notify sender that the receiver is OFFLINE
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
						// ...........................................
						// UNKNOWN CMD
						// ...........................................
					case ClientCommand::C_UNKNOWN_CMD:
						{
							// [WARNING] Log -> Client shouldn't send this cmd code = Hacking attempt
							this->dropClient(p_client);
						}
						break;

						// ...........................................
						// QUIT
						// ...........................................
					case ClientCommand::C_QUIT:
						{
							// drop the client since he wants to leave
							this->dropClient(p_client);

						}
						break;


						// ...........................................
						// AFK
						// ...........................................
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


						// ...........................................
						// LOOKING FOR TRADE
						// ...........................................
					case ClientCommand::C_LOOKING_FOR_TRADE:
						{
						}
						break;


						// ...........................................
						// PONG
						// ...........................................
					case ClientCommand::C_PONG:
						{
							if(p_client->isPongRequested())
								p_client->notifyPong();
						}
						break;


						// ...........................................
						// FRIEND ADD
						// ...........................................
					case ClientCommand::C_FRIEND_ADD:
						{
							// can't send it to yourself!
							if(p_client->getName().compare(c2s_command.argument) == 0)
								break;

							// check is username exists, contact DB? WebService?
							// AND
							// check if invitation inserted into DB correclty
							// if everything OK...

							if(true)
							{
								// send confirmation to the sender
								{
									sf::Packet packet;
									S2C_Command s2c_cmd(ServerCommand::S_CONFIRM_FRIEND_ADD, c2s_command.argument);
									packet << s2c_cmd;
									this->sendPacket(packet, p_client);
								}

								// send invitation to the receiver IF it's ONLINE
								std::shared_ptr<Client> dstClient = this->findClientByName(c2s_command.argument);
								if(dstClient.get() != 0 && dstClient->getState() == ClientState::AUTHED)
								{
									sf::Packet packet;
									S2C_Command s2c_cmd(ServerCommand::S_FRIEND_ADD, p_client->getName());
									packet << s2c_cmd;
									this->sendPacket(packet, p_client);
								}
							}
							// if NOT
							else
							{
								sf::Packet packet;
								S2C_Command s2c_cmd(ServerCommand::S_PEER_NOTEXIST, c2s_command.argument);
								packet << s2c_cmd;
								this->sendPacket(packet, p_client);
							}
						}
						break;


						// ...........................................
						// FRIEND DELETE
						// ...........................................
					case ClientCommand::C_FRIEND_DEL:
						{
							// can't send it to yourself!
							if(p_client->getName().compare(c2s_command.argument) == 0)
								break;


						}
						break;


						// ...........................................
						// FRIEND DELETE
						// ...........................................
					case ClientCommand::C_FRIEND_IGNORE:
						{
							// can't send it to yourself!
							if(p_client->getName().compare(c2s_command.argument) == 0)
								break;


						}
						break;


						// ...........................................
						// NOTHING
						// ...........................................
					default:
						{
							// [WARNING] Log -> Cmd not handled by server = Hacking attempt
							this->dropClient(p_client);
						}
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
			// [WARNING] Log
			// holy shit, this case shouldn't happen
			
		}
		break;

	default:
		{
			// [WARNING] Log
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


sf::Uint32 ChatServer::connectionCountByIP(sf::IpAddress p_compareIP)
{
	sf::Uint32 count = 0;

	for(auto it = clients.begin(); it != clients.end(); ++it)
	{
		// CLIENT
		std::shared_ptr<Client> currentClient = *it;
		if(currentClient->getSocket().getRemoteAddress() == p_compareIP)
			count++;
	}

	return count;
}



// threaded, used for high CPU time operations
void ChatServer::mAsyncTasks(void)
{
	{ std::ostringstream msg; msg << "[THREAD] Async Task thread STARTING" << ""; Debug::msg(msg); }
	while(this->isRunning())
	{

		{
			sf::Lock lock(mMutex);

			// Async Requests
			for (auto it = mAsyncRequests.begin(); it != mAsyncRequests.end();)
			{
				// request removal
				if (it->asyncRequestCode == AsyncRequestCode::ASR_DONE) {
					it = mAsyncRequests.erase(it);
				} 
				// authentication
				else if (it->asyncRequestCode == AsyncRequestCode::ASR_AUTHENTICATE) {
					{ std::ostringstream msg; msg << "[ASYNC] Authentication" << ""; Debug::msg(msg); }
					// if authentication is OK
					if(this->authenticate(it->client)) {
						// send userlist
						// - reset userlist
						sf::Packet packet;
						packet << S2C_Command(ServerCommand::S_USERLIST_RESYNC);
						this->sendPacket(packet, it->client);
						// - send username one by one
						for(auto cl = clients.begin(); cl != clients.end(); ++cl) {
							if((*cl)->getState() == ClientState::AUTHED && (*cl)->isNamed()) {
								// don't send the username of the receiver (it's added in userlist elsewhere in the code, see S_USERLIST_RESYNC in ChatClient)
								if(it->client->getName().compare((*cl)->getName()) != 0)
								{
									sf::Packet packet;
									packet << S2C_Command(ServerCommand::S_JOIN, (*cl)->getName());
									this->sendPacket(packet, it->client);
								}
							}
						}
					}
					it->asyncRequestCode = AsyncRequestCode::ASR_DONE;
					++it;
				}
				// friend list fetch
				else if (it->asyncRequestCode == AsyncRequestCode::ASR_FETCH_FRIENDLIST) {
					{ std::ostringstream msg; msg << "[ASYNC] Fetch friendlist" << ""; Debug::msg(msg); }
					it->asyncRequestCode = AsyncRequestCode::ASR_DONE;
					++it;
				}
				else {
					++it;
				}

			} // -- end of loop for

		} // -- end of lock

		sf::sleep(sf::milliseconds(500));	// for CPU
	}
	{ std::ostringstream msg; msg << "[THREAD] Async Task thread FINISHED" << ""; Debug::msg(msg); }
}
