#pragma once
#include "Chat.h"

#define MAX_C_PACKETSEND_RETRY	5

typedef std::vector<C2S_Chat> ChatBuffer;

class ChatClient
{
public:
	// static members
	static sf::Mutex	mutex;

	// (con/de)structor
	ChatClient(void);
	~ChatClient(void);

	// chatbuffer
	static ChatBuffer& getChatBuffer();
	static void pushChatBuffer(C2S_Chat& c2s_chat);
	static void clearChatBuffer();

	// others methods
	void connect(void);
	void handlePacket(sf::Packet& p_packet);
	bool sendPacket(sf::Packet& p_packet);
	void disconnect(void);
	void terminate(void);

private:
	sf::TcpSocket		mSocket;
	unsigned short		mServerPort;
	sf::IpAddress		mServerIP;
	bool				mRunning;
	static ChatBuffer	chatBuffer;	// std::vector<C2S_Chat>

	// threaded function
	void			mRunClient(void);
	
};

