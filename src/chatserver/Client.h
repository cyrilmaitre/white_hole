#pragma once
#include <vector>
#include "SFML/Network.hpp"
// --------------
// --- DEFINE ---
// --------------
#define UNNAMED_PLAYER "UnnamedPlayer"

// ------------
// --- ENUM ---
// ------------

enum ClientState
{
	UNKNOWN_CS,
	TCP_CONNECTED,
	DROPPED,
	AUTHED
};

enum ClientAttributes
{
	ATTR_NONE	= 0,	// 00000000

	ATTR_MUTED	= 1,	// 00000001 :2^0
	ATTR_VOICE	= 2,	// 00000010 :2^1
	ATTR_MOD	= 4,	// 00000100 :2^2
	ATTR_ADMIN	= 8,	// 00001000 :2^3
	ATTR_AFK	= 16	// 00010000 :2^4
};

// -------------
// --- CLASS ---
// -------------

class Client
{
public:
	// (con/de)structor
	Client(void);
	~Client(void);

	// uid
	sf::Uint64 getUniqueID();

	// state
	ClientState getState();
	void setState(ClientState p_state);

	// attributes
	sf::Uint16 getAttributes();
	void setAttributes(sf::Uint16 p_attributes);

	bool hasAttribute(ClientAttributes p_attribute);
	void addAttribute(ClientAttributes p_attribute);
	void removeAttribute(ClientAttributes p_attribute);

	// socket
	sf::TcpSocket& getSocket();

	// name
	std::string getName();
	void setName(std::string p_name);

	bool isNamed();

	// nb dropped packets
	sf::Uint64	getNbDroppedPackets();
	void		notifyDroppedPacket();

	// last activity time
	sf::Uint64	getLastActivityTime();
	void		notifyLastActivityTime();

	// connection time
	sf::Uint64	getConnectionTime();

	// waiting for pong
	bool isPongRequested();	// do the client have to pong the server ?
	void requestPong();		// we want a PONG !
	void notifyPong();		// has answered to ping

	// flood control time
	sf::Uint64	getFloodControlTime();
	void		updateFloodControlTime();

	// nb sent packets (flood control)
	sf::Uint64	getNbSentPackets();
	void		notifySentPacket();
	void		resetNbSentPackets();
	

private:
	sf::Uint64						mUniqueID;
	ClientState						mState;
	sf::Uint16						mAttributes;
	std::unique_ptr<sf::TcpSocket>	mSocket;
	std::string						mName;
	sf::Uint64						mNbDroppedPackets;
	sf::Uint64						mConnectionTime;
	sf::Uint64						mDisconnectionTime;
	sf::Uint64						mLastActivityTime;	// in ms (milliseconds)
	bool							mPongRequested;

	sf::Uint64						mFloodControlTime;
	sf::Uint64						mNbSentPackets;			// used for flood control

};

