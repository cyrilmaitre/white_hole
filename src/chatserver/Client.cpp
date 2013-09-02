#include "Client.h"
#include "ChatServer.h"
#include <time.h>

// ----------------------------------------------------------------------
// (con/de)structor
// ----------------------------------------------------------------------
Client::Client(void) : 
	mSocket(std::unique_ptr<sf::TcpSocket>(new sf::TcpSocket)),
	mState(ClientState::UNKNOWN_CS),
	mName(UNNAMED_PLAYER),
	mAttributes(ClientAttributes::ATTR_NONE),
	mNbDroppedPackets(0),
	mLastActivityTime(0),
	mPongRequested(false),
	mConnectionTime((sf::Uint64)time(NULL)),
	mFloodControlTime((sf::Uint64)time(NULL) + FLOOD_INTERVAL),
	mNbSentPackets(0)
{
	this->mUniqueID = (sf::Uint64) mSocket.get();
}


Client::~Client(void)
{
}


// ----------------------------------------------------------------------
// getters,setters
// ----------------------------------------------------------------------
// <uniqueID>
sf::Uint64 Client::getUniqueID()
{
	return this->mUniqueID;
}
// </uniqueID>

// <state>
ClientState Client::getState()
{
	return this->mState;
}

void Client::setState(ClientState p_state)
{
	this->mState = p_state;
}
// </state>

// <attributes>
sf::Uint16 Client::getAttributes()
{
	return this->mAttributes;
}

void Client::setAttributes(sf::Uint16 p_attributes)
{
	this->mAttributes = p_attributes;
}
// </attributes>

// <socket>
sf::TcpSocket& Client::getSocket()
{
	return *(this->mSocket);
}
// </socket>

// <name>
std::string Client::getName()
{
	return this->mName;
}

void Client::setName(std::string p_name)
{
	this->mName = p_name;
}
// </name>

// <mNbDroppedPackets>
sf::Uint64	Client::getNbDroppedPackets()
{
	return this->mNbDroppedPackets;
}
// </mNbDroppedPackets>


// <lastActivityTime>
sf::Uint64 Client::getLastActivityTime()
{
	return this->mLastActivityTime;
}
// </lastActivityTime>

// <pingRequested>
bool Client::isPongRequested()
{
	return this->mPongRequested;
}
// </pingRequested>


// <connectionTime>
sf::Uint64 Client::getConnectionTime()
{
	return this->mConnectionTime;
}
// </connectionTime>




// <floodControlTime>
sf::Uint64	Client::getFloodControlTime()
{
	return this->mFloodControlTime;
}
// <floodControlTime>

// <nbSentPackets>
sf::Uint64 Client::getNbSentPackets()
{
	return this->mNbSentPackets;
}
// </nbSentPackets>

// ----------------------------------------------------------------------
// methods
// ----------------------------------------------------------------------

// <attributes>
// - test if client has an attribute
bool Client::hasAttribute(ClientAttributes p_attribute)
{
	return (this->getAttributes() & p_attribute);
}

// - add an attribute to the client
void Client::addAttribute(ClientAttributes p_attribute)
{
	this->setAttributes(this->getAttributes() | p_attribute);
}

// - remove an attr to the client
void Client::removeAttribute(ClientAttributes p_attribute)
{
	this->setAttributes(this->getAttributes() ^ p_attribute);
}
// </attributes>


// <name>
// - return true if the client name has been set (= different from #define UNNAMED_PLAYER)
bool Client::isNamed()
{
	return (this->getName().compare(UNNAMED_PLAYER) != 0);
}
// </name>


// <mNbDroppedPackets>
void Client::notifyDroppedPacket()
{
	++(this->mNbDroppedPackets);
}
// </mNbDroppedPackets>


// <lastActivityTime>
void Client::notifyLastActivityTime()
{
	this->mLastActivityTime = (sf::Uint64)time(NULL);
}
// </lastActivityTime>


// <pingRequested>
void Client::notifyPong()
{
	this->mPongRequested = false;
}

void Client::requestPong()
{
	this->mPongRequested = true;
}
// </pingRequested>


// <floodControlTime>
void Client::updateFloodControlTime()
{
	this->mFloodControlTime = (sf::Uint64)time(NULL) + FLOOD_INTERVAL;
}
// </floodControlTime>


// <nbSentPackets>
void Client::notifySentPacket()
{
	++this->mNbSentPackets;
}

void Client::resetNbSentPackets()
{
	this->mNbSentPackets = 0;
}
// </nbSentPackets>