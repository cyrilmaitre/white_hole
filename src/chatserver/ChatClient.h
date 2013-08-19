#pragma once
#include "Chat.h"

#define MAX_C_PACKETSEND_RETRY	5

typedef std::vector<C2S_Chat> InputBuffer;
typedef std::vector<S2C_Chat> OutputBuffer;

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
	void pushInputBuffer(C2S_Chat& c2s_chat);		// add a chat message to the buffer (public)

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

	// buffers
	OutputBuffer		mOutputBuffer;
	void				pushOutputBuffer(S2C_Chat& s2c_chat);	// store received messages (private)
	InputBuffer			mInputBuffer;
	void				clearInputBuffer();						// clear sent messages (private)


	// thread
	sf::Mutex					mMutex;
	std::unique_ptr<sf::Thread> mThread;
	void						mRunClient(void);	// threaded function

	
};

