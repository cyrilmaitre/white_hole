#pragma once
#include "Chat.h"

#define MAX_C_PACKETSEND_RETRY		5
#define	RECONNECTION_INTERVAL		30 // time before reconnecting (seconds)
#define	SOCKET_CONNECTION_ATTEMPTS	15 // max connection attempt

typedef std::vector<std::shared_ptr<Message>> MessageBuffer;

enum NetworkStateCode {
	NS_NONE,
	NS_CONNECTING,
	NS_CONNECTION_OK,					// connected
	NS_CONNECTION_OK_AUTHRESPONSE,		// connected + got auth response
	NS_CONNECTION_FAILED,
	NS_DISCONNECTED,
};

struct NetworkState {
	NetworkState(NetworkStateCode code = NetworkStateCode::NS_NONE, std::string optionalString = "")
	: code(code), optionalString(optionalString), timestamp((sf::Uint64)time(NULL)), newState(true)
	{}

	sf::Uint16	code;
	std::string optionalString;
	sf::Uint64	timestamp;
	bool		newState;
};

class ChatClient
{
public:

	// (con/de)structor
	ChatClient(void);
	~ChatClient(void);
	
	// running
	bool isRunning(void);
	void setRunning(bool p_running);

	// chat input buffer (send)
	const MessageBuffer& getInputBuffer(void);
	void pushInputBuffer(std::shared_ptr<Message> p_message);		// add a chat message to the buffer (public)

	// chat output buffer (received)
	const MessageBuffer& getOutputBuffer(void);
	void clearOutputBuffer(void);					// clear received messages buffer (public)

	// network state
	const NetworkState& getNetworkState();
	void				notifyNetworkState();	// called after reading the network state

	// auth response
	const AuthResponse	getAuthResponse();

	// others methods
	void connect(std::string p_username, std::string p_sha1password);
	void handlePacket(sf::Packet& p_packet);
	bool sendPacket(sf::Packet& p_packet);
	void disconnect(bool p_reconnect = true);
	void terminate(void);

	// thread
	sf::Mutex& getMutex(void);

	// auto reconnect
	bool isAutoReconnectEnabled(void);
	void setAutoReconnect(bool p_autoreconnect);

private:
	sf::TcpSocket		mSocket;
	unsigned short		mServerPort;
	sf::IpAddress		mServerIP;
	bool				mRunning;
	bool				mAutoReconnect;
	sf::Socket::Status	lastSentStatus;

	// buffers
	// -- received packets
	MessageBuffer			mOutputBuffer;
	void					pushOutputBuffer(std::shared_ptr<Message> p_message);	// store received messages (private)
	// -- packets being sent
	MessageBuffer			mInputBuffer;
	void					clearInputBuffer(void);										// clear sent messages (private)

	// thread
	sf::Mutex					mMutex;
	std::unique_ptr<sf::Thread> mThread;
	void						mRunClient(void);	// threaded function

	// auth stuff
	std::string mUsername;
	std::string mSha1password;

	// network state
	NetworkState	mNetworkState;
	void			updateNetworkState(NetworkStateCode p_networkStateCode, std::string p_optionalString = "");

	// auth response
	AuthResponse	mAuthResponse;
	void			setAuthResponse(AuthResponse p_authResponse);
	
};

