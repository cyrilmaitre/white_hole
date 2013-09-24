#include "ChatClient.h"

// ----------------------------------------------------------------------
// operator overloads for sf::Packet
// ----------------------------------------------------------------------
// * CLIENT to SERVER (send) *
// -- Chat
sf::Packet& operator << (sf::Packet& packet, const C2S_Chat c2s_chat)
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

	return c2s_chat.insertIntoPacket(packet);
}
// -- Commad
sf::Packet& operator << (sf::Packet& packet, const C2S_Command c2s_command)
{
	// properties size veritifcation
	// msg
	if(c2s_command.argument.length() > MAX_SIZE_CMDARG) {
		c2s_command.argument.substr(0,MAX_SIZE_CMDARG);
	}

	return c2s_command.insertIntoPacket(packet);
}

// -- Auth
sf::Packet& operator << (sf::Packet& packet, const C2S_Auth c2s_auth)
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
ChatClient::ChatClient(void) : mServerPort(CHAT_SERVER_PORT), mServerIP(CHAT_SERVER_HOST), mRunning(false), lastSentStatus(sf::Socket::Status::Error), mAutoReconnect(true)
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

void ChatClient::setRunning(bool p_running)
{
	sf::Lock lock(mMutex);
	{ std::ostringstream msg; msg << "[PROP] mRunning changed to <" << (p_running ? "TRUE" : "FALSE") << ">"; Debug::msg(msg); }
	this->mRunning = p_running;
}
// </running>

//<autoreconnect>
bool ChatClient::isAutoReconnectEnabled(void)
{
	sf::Lock lock(mMutex);
	return this->mAutoReconnect;
}

void ChatClient::setAutoReconnect(bool p_autoreconnect)
{
	sf::Lock lock(mMutex);
	{ std::ostringstream msg; msg << "[PROP] mAutoReconnect changed to <" << (p_autoreconnect ? "TRUE" : "FALSE") << ">"; Debug::msg(msg); }
	this->mAutoReconnect = p_autoreconnect;
}
// </autoreconnect>

// <mutex>
sf::Mutex& ChatClient::getMutex()
{
	return this->mMutex;
}
// </mutex>

// <chatbuffer>
// out
const MessageBuffer& ChatClient::getOutputBuffer()
{
	sf::Lock lock(mMutex);
	return this->mOutputBuffer;
}

void ChatClient::clearOutputBuffer()
{
	sf::Lock lock(mMutex);
	this->mOutputBuffer.clear();
	this->mOutputBuffer.shrink_to_fit();
}

void ChatClient::pushOutputBuffer(std::shared_ptr<Message> p_message)
{
	sf::Lock lock(mMutex);
	this->mOutputBuffer.push_back(p_message);
}

// int
const MessageBuffer& ChatClient::getInputBuffer()
{
	sf::Lock lock(mMutex);
	return this->mInputBuffer;
}

void ChatClient::pushInputBuffer(std::shared_ptr<Message> p_message)
{
	sf::Lock lock(mMutex);
	this->mInputBuffer.push_back(p_message);
}

void ChatClient::clearInputBuffer()
{
	sf::Lock lock(mMutex);
	this->mInputBuffer.clear();
	this->mInputBuffer.shrink_to_fit();
}
// </chatbuffer>

// <networkstate>
const NetworkState& ChatClient::getNetworkState()
{
	sf::Lock lock(mMutex);
	return this->mNetworkState;
}

void ChatClient::updateNetworkState(NetworkStateCode p_networkStateCode, std::string p_optionalString)
{
	sf::Lock lock(mMutex);
	if(p_networkStateCode != this->mNetworkState.code) {
		this->mNetworkState.code = p_networkStateCode;
		this->mNetworkState.newState = true;
		this->mNetworkState.optionalString = p_optionalString;
		this->mNetworkState.timestamp = (sf::Uint64)time(NULL);
	}

}

void ChatClient::notifyNetworkState()
{
	sf::Lock lock(mMutex);
	this->mNetworkState.newState = false;
}
// </networkstate>


// <authresponse>
const AuthResponse ChatClient::getAuthResponse()
{
	sf::Lock lock(mMutex);
	return this->mAuthResponse;
}

void ChatClient::setAuthResponse(AuthResponse p_authResponse)
{
	sf::Lock lock(mMutex);
	this->mAuthResponse = p_authResponse;

}
// </authresponse>


// Launch the thread connecting to the chat server
void ChatClient::connect(std::string p_username, std::string p_sha1password)
{
	{
		sf::Lock lock(mMutex);
		this->mUsername = p_username;
		this->mSha1password = p_sha1password;

	}

	{ std::ostringstream msg; msg << mUsername << " / " << mSha1password; Debug::msg(msg); }
	if(!mRunning)
	{
		this->mThread = std::unique_ptr<sf::Thread>(new sf::Thread(&ChatClient::mRunClient, this));
		this->setRunning(true);
		this->mThread->launch();
	}
	else
	{
		{ std::ostringstream msg; msg << "[ERR] Thread already running !" << ""; Debug::msg(msg); }
	}
}

void ChatClient::mRunClient(void)
{

	sf::Uint64 nextConnectionTime = 0;

	// Reconnection loop --> break condition at the end of the loop
	while(this->isRunning()) 
	{

		if((sf::Uint64)time(NULL) > nextConnectionTime)
		{
			{ std::ostringstream msg; msg << "Connecting to " << mServerIP.toString() << ":" << mServerPort << ""; Debug::msg(msg); }

			// WORKAROUND
			// bug avec socket non bloquantes : https://github.com/LaurentGomila/SFML/issues/194
			sf::Socket::Status status = sf::Socket::Error;

			if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
			{
					mSocket.setBlocking(false);

					this->updateNetworkState(NetworkStateCode::NS_CONNECTING);

					unsigned int attempt = 0;
					while(true) {
						{ std::ostringstream msg; msg << "Attempt " << attempt+1 << "/" << SOCKET_CONNECTION_ATTEMPTS << ""; Debug::msg(msg); }
						status = mSocket.connect(mServerIP, mServerPort);
						if(status == sf::Socket::Status::Done)
							break;
				
						if(++attempt >= SOCKET_CONNECTION_ATTEMPTS) {
							{ std::ostringstream msg; msg << "Connection FAILED !" << ""; Debug::msg(msg); }
							break;
						}

						sf::sleep(sf::milliseconds(500));	// for CPU
					}

			}

			if(status == sf::Socket::Status::Done)
			{
				this->updateNetworkState(NetworkStateCode::NS_CONNECTION_OK);
				{ std::ostringstream msg; msg << "Connection OK !" << ""; Debug::msg(msg); }

				// ------------------- Auth packet ------------------------------------------------------------------------------
				std::shared_ptr<C2S_Auth> auth = std::make_shared<C2S_Auth>(this->mUsername, this->mSha1password);
				this->pushInputBuffer(auth);


				sf::Packet packet;
				// ~ RECV / SEND Loop ~
				while(this->isRunning() && this->getNetworkState().code == NetworkStateCode::NS_CONNECTION_OK)
				{
					// ------------------- Envoi --------------------------------------------------------------------------------
					// <Thread safe>
					{

						sf::Lock lock(mMutex);
						MessageBuffer chatbuffer(this->getInputBuffer()); // we get a copy of the buffer

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

				}  // -- after-connection loop (receiv/send)
				{ std::ostringstream msg; msg << "(!) RECV/SEND Loop ended" << ""; Debug::msg(msg); }
			}
			// else connection failed
			else
			{
				this->updateNetworkState(NetworkStateCode::NS_CONNECTION_FAILED);
				{ std::ostringstream msg; msg << "(!) Couldn't connect to chat server, status : ("<< status << ")"; Debug::msg(msg); }
			}
				
			// ------------------------------------------------------------------------------------------------------------------
			this->clearInputBuffer();
			this->clearOutputBuffer();

			// Auto reconnect
			if(!this->isAutoReconnectEnabled()) {
				{ std::ostringstream msg; msg << "Stopping chat..." << ""; Debug::msg(msg); }
				this->setRunning(false);
				break;
			}
			else {
				nextConnectionTime = (sf::Uint64)time(NULL) + RECONNECTION_INTERVAL;
			}
			// ------------------------------------------------------------------------------------------------------------------


		} // -- if connection time
		sf::sleep(sf::milliseconds(250));	// for CPU, since 

	} // -- reconnection loop

	{ std::ostringstream msg; msg << "Thread ended" << ""; Debug::msg(msg); }
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
			std::shared_ptr<S2C_Chat> s2c_chat = std::make_shared<S2C_Chat>();
			if(p_packet >>* s2c_chat)
			{
				this->pushOutputBuffer(s2c_chat);
				{ std::ostringstream msg; msg << "[CHAT] FROM <" << s2c_chat->from << "> TO <" << s2c_chat->to << "("<< s2c_chat->dstType <<")> : " << s2c_chat->message << ""; Debug::msg(msg); }
			}
		}
		// Command
		else if(packetType == PacketType::COMMAND)
		{
			std::shared_ptr<S2C_Command> s2c_command = std::make_shared<S2C_Command>();
			if(p_packet >> *s2c_command)
			{
				this->pushOutputBuffer(s2c_command);
				{ std::ostringstream msg; msg << "[CMD] #" << Chat::serverCmdToString(s2c_command->command) << ":" << s2c_command->argument << ""; Debug::msg(msg); }

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
				

					// DROPs
				case ServerCommand::S_DROPPED_NORC:
					{
						this->setAutoReconnect(false);
					}
					break;

				} // -- end of switch() {}

			}
		}
		// Auth
		else if(packetType == PacketType::AUTHENTICATION)
		{

			std::shared_ptr<S2C_Auth> s2c_auth(new S2C_Auth);
			if(p_packet >> *s2c_auth)
			{
				// update network state && auth response
				this->updateNetworkState(NetworkStateCode::NS_AUTH_RESPONSE);
				this->setAuthResponse((AuthResponse) s2c_auth->authResponse);

				// don't reconnect if banned, invalid IDs or maintenance
				if(s2c_auth->authResponse == AuthResponse::AR_BANNED
					&& s2c_auth->authResponse != AuthResponse::AR_INVALID_IDS
					&& s2c_auth->authResponse != AuthResponse::AR_MAINTENANCE)
				{
						this->setAutoReconnect(false);
				}

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


// used to stop "properly" the chat, at the end of the app
// should be called by UI client
void ChatClient::terminate(void)
{
	sf::Lock lock(mMutex);

	if(this->isRunning())
	{
		if(this->getNetworkState().code == NetworkStateCode::NS_CONNECTION_OK) {
			C2S_Command c2s_command(ClientCommand::C_QUIT, "Closed by user");
			sf::Packet packet;
			packet << c2s_command;

			this->sendPacket(packet);
		}

		this->disconnect(false);
	}
}


// stop the thread (if p_reconnect=false) or relaunch the connection (if p_reconnect=true)
// called by the ChatClient itself in case of network errors/disconnections
void ChatClient::disconnect(bool p_reconnect)
{
	sf::Lock lock(mMutex);
	this->updateNetworkState(NetworkStateCode::NS_DISCONNECTED);	// this will make the recv/snd loop stop
	this->mSocket.disconnect();

	// if no reconnection
	if(!p_reconnect) {
		this->setAutoReconnect(false);		// no auto reconnect, so the main loop will stop
		this->setRunning(false);			// main loop should have stopped, but here is one more "security"
	}
	
	{ std::ostringstream msg; msg << "Disconnected" << ""; Debug::msg(msg); }
}