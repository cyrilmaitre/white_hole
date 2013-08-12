#pragma once
#include <vector>
#include "Client.h"
#include <SFML/Network.hpp>

#define SERVER_NAME				"Makaki"
#define SERVER_MOTD				"Sisi la famille"
#define MAX_CLIENTS				10
#define MAX_S_PACKETSEND_RETRY	5

// ------------
// --- ENUM ---
// ------------


// Commands sent by the server to clients for display purposes (ex: "Bob has been kicked")
enum ServerCommand
{
	UNKNOWN_CMD,
	JOIN,
	QUIT,
	KICK,
	MOTD,
	SAY,
	MUTE
};


// Is this a channel to a channel or to a user (= private message)
enum ChatDstType
{
	NONE,
	USER,
	CHANNEL
};

// Is is a command (kick, ban, motd, etc) or a chat message
enum S2C_Type
{
	CHAT,
	COMMAND,
	AUTHENTICATION
};

enum AuthResponse
{
	OK,				// valid IDs = auth OK
	INVALID_IDS,	// invalid IDs
	ERROR,			// error sent from the server (ex: if cannot contact database)
	MAINTENANCE,	// maintenance mode, can't connect
	BANNED			// should receive "BANNED" only if IDs are valids
};

// --------------
// --- STRUCT ---
// --------------
// AUTH -----------------------------------------------------
struct S2C_Auth
{
	S2C_Auth(){}
};

struct C2S_Auth
{
	C2S_Auth(){}
};

// CHAT -----------------------------------------------------
// Server To Client - Chat
struct S2C_Chat
{
	S2C_Chat(std::string from = "", std::string message = "", std::string to = "", sf::Uint16 dstType = ChatDstType::NONE)
		: from(from), message(message),	to(to), dstType(dstType)
	{}

	std::string from, to, message;
	sf::Uint16 dstType;
};


// Client To Server - Chat
struct C2S_Chat
{
	C2S_Chat(std::string message = "", std::string to = "", sf::Uint16 dstType = ChatDstType::NONE)
		: message(message),	to(to), dstType(dstType)
	{}

	std::string to, message;
	sf::Uint16 dstType;
};

// COMMANDS  -----------------------------------------------------
// Server To Client - Commands
struct S2C_Command
{
	S2C_Command(sf::Uint16 command = ServerCommand::UNKNOWN_CMD, std::string argument = "")
		: command(command), argument(argument)
	{}

	sf::Uint16 command;
	std::string argument;
};

// -------------
// --- CLASS ---
// -------------

class ChatServer
{
public:
	ChatServer(void);
	void create(void);
	void create(unsigned short p_port);
	void addClient(std::shared_ptr<Client> p_client);
	void dropClient(std::shared_ptr<Client> p_client);
	void handlePacket(sf::Packet& p_packet, std::shared_ptr<Client> p_client);
	bool sendPacket(sf::Packet& p_packet, std::shared_ptr<Client> p_client);
	void broadcast(sf::Packet& p_packet);
	void disconnect(void);

private:
	sf::SocketSelector selector;
	sf::TcpListener listener;
	std::vector< std::shared_ptr<Client> > clients;	// List to store the future clients
	unsigned short mPort;
	bool mRunning;
	void mRunServer(void);
};