#pragma once
#include "Chat.h"

#define MAX_C_PACKETSEND_RETRY	5

typedef std::vector<std::shared_ptr<Message>> InputBuffer;
typedef std::vector<std::shared_ptr<Message>> OutputBuffer;

enum ChatEventCode {
	CE_NONE,
	CE_CONNECTION_OK,
	CE_CONNECTION_FAILED,
	CE_RECONNECTION,
	CE_RECONNECTION_FAILED,
	CE_DISCONNECTED,
};

struct ChatEvent {
	ChatEvent(ChatEventCode code = ChatEventCode::CE_NONE, std::string optionalString = "")
	: code(code), optionalString(optionalString)
	{}

	sf::Uint16	code;
	std::string optionalString;
};

class ChatClient
{
public:

	// (con/de)structor
	ChatClient(void);
	~ChatClient(void);
	
	// running
	bool isRunning(void);

	// chat input buffer (send)
	const InputBuffer& getInputBuffer(void);
	void pushInputBuffer(std::shared_ptr<Message> p_message);		// add a chat message to the buffer (public)

	// chat output buffer (received)
	const OutputBuffer& getOutputBuffer(void);
	void clearOutputBuffer(void);					// clear received messages buffer (public)

	// others methods
	void connect(void);
	void handlePacket(sf::Packet& p_packet);
	bool sendPacket(sf::Packet& p_packet);
	void disconnect(void);
	void terminate(void);

	// tread
	sf::Mutex& getMutex(void);

private:
	sf::TcpSocket		mSocket;
	unsigned short		mServerPort;
	sf::IpAddress		mServerIP;
	bool				mRunning;
	sf::Socket::Status	lastSentStatus;

	// buffers
	OutputBuffer		mOutputBuffer;
	void				pushOutputBuffer(std::shared_ptr<Message> p_message);	// store received messages (private)
	InputBuffer			mInputBuffer;
	void				clearInputBuffer();										// clear sent messages (private)


	// thread
	sf::Mutex					mMutex;
	std::unique_ptr<sf::Thread> mThread;
	void						mRunClient(void);	// threaded function

	
};

