#pragma once
#include "Debug.h"
#include <SFML/Network.hpp>
#include <vector>

#define CHAT_SERVER_HOST "localhost"
#define CHAT_SERVER_PORT 30035


// ------------
// --- ENUM ---
// ------------
// Is is a command (kick, ban, motd, etc) or a chat message
enum PacketType
{
	CHAT,
	COMMAND,
	AUTHENTICATION
};

// Commands sent by the server to clients for display purposes (ex: "Bob has been kicked")
enum ServerCommand
{
	S_UNKNOWN_CMD,
	S_JOIN,
	S_QUIT,
	S_KICK,
	S_MOTD,
	S_SAY,
	S_MUTE
};

// Commands sent by the client (ex: quit)
enum ClientCommand
{
	C_UNKNOWN_CMD,
	C_QUIT,
	C_AFK,
	C_BUSY,
	C_LOOKING_FOR_TRADE,
};


// Is this a channel to a channel or to a user (= private message)
enum ChatDstType
{
	NONE,
	USER,
	CHANNEL
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
	S2C_Command(sf::Uint16 command = ServerCommand::S_UNKNOWN_CMD, std::string argument = "")
		: command(command), argument(argument)
	{}

	sf::Uint16 command;
	std::string argument;
};

// Client To Server - Commands
struct C2S_Command
{
	C2S_Command(sf::Uint16 command = ClientCommand::C_UNKNOWN_CMD, std::string argument = "")
		: command(command), argument(argument)
	{}

	sf::Uint16 command;
	std::string argument;
};