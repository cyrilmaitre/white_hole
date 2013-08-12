#pragma once
#include "Client.h"
#include <SFML/Network.hpp>

#define MAX_C_PACKETSEND_RETRY	5

class ChatClient
{
public:
	ChatClient(void);
	~ChatClient(void);
	void connect(void);
	void connect(sf::IpAddress p_address, unsigned short p_port);
	void handlePacket(sf::Packet& p_packet);
	bool sendPacket(sf::Packet& p_packet);
	void disconnect(void);

private:
	sf::TcpSocket	mSocket;
	unsigned short	mServerPort;
	sf::IpAddress	mServerIP;
	bool			mRunning;
	void			mRunClient(void);
};

