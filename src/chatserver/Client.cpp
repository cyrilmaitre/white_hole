#include "Client.h"

// ----------------------------------------------------------------------
// (con/de)structor
// ----------------------------------------------------------------------
Client::Client(void) : 
	mSocket(std::unique_ptr<sf::TcpSocket>(new sf::TcpSocket)),
	mState(ClientState::UNKNOWN_CS),
	mName(UNNAMED_PLAYER),
	mAttributes(ClientAttributes::ATTR_NONE)
{
}


Client::~Client(void)
{
}


// ----------------------------------------------------------------------
// getters,setters
// ----------------------------------------------------------------------
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


// ----------------------------------------------------------------------
// methods
// ----------------------------------------------------------------------

// <attributes>
// - test if client has an attribute
bool Client::hasAttribute(ClientAttributes p_attribute)
{
	return true;
}

// - add an attribute to the client
void Client::addAttribute(ClientAttributes p_attribute)
{
	this->setAttributes(this->getAttributes() | p_attribute);
}

// - remove an attr to the client
void Client::removeAttribute(ClientAttributes p_attribute)
{
	this->setAttributes(this->getAttributes() & ~ p_attribute);
}
// </attributes>


// <name>
// - return true if the client name has been set (= different from #define UNNAMED_PLAYER)
bool Client::isNamed()
{
	return (this->getName().compare(UNNAMED_PLAYER) != 0);
}
// </name>