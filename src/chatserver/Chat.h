#pragma once
#include "Debug.h"
#include <SFML/Network.hpp>
#include <vector>

#define CHAT_SERVER_HOST "localhost"
#define CHAT_SERVER_PORT 30035

// security measures
#define MAX_SIZE_USERNAME		20					// max username length
#define MAX_SIZE_PASSWORD		20					// max (sha1) password length
#define MAX_SIZE_CHANNEL		20					// max channel length
#define MAX_SIZE_CHATMSG		200					// max message length
#define MAX_SIZE_CMDARG			200					// max cm dargument length
#define CHAT_REPOST_TIME		2					// interval between 2 identical messages

// ------------
// --- ENUM ---
// ------------

enum PeerType
{
	CLIENT,
	SERVER
};

// Is is a command (kick, ban, motd, etc) or a chat message
enum PacketType
{
	CHAT,
	COMMAND,
	AUTHENTICATION
};

enum MessageType
{
	MT_S2C_Auth,
	MT_C2S_Auth,
	MT_S2C_Chat,
	MT_C2S_Chat,
	MT_S2C_Command,
	MT_C2S_Command,
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
	S_MUTE,
	S_PING,
	S_CHAT_PEER_OFFLINE,
	S_CHAT_PEER_AFK,
	S_FRIEND_ADD,
	S_AFK_ON,
	S_AFK_OFF,
	S_PEER_NOTEXIST,
	S_DROPPED,
	S_DROPPED_NORC,
	// confirmations
	S_CONFIRM_FRIEND_ADD,		// <-> C_FRIEND_ADD
	S_CONFIRM_FRIEND_IGNORE,	// <-> C_FRIEND_IGNORE
	S_CONFIRM_FRIEND_DEL,		// <-> C_FRIEND_DEL
};

// Commands sent by the client (ex: quit)
enum ClientCommand
{
	C_UNKNOWN_CMD,
	C_QUIT,
	C_AFK,
	C_BUSY,
	C_LOOKING_FOR_TRADE,
	C_PONG,
	C_FRIEND_ADD,
	C_FRIEND_IGNORE,
	C_FRIEND_DEL
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
	AR_NONE,
	AR_OK,				// valid IDs = auth OK
	AR_INVALID_IDS,		// invalid IDs
	AR_ERROR,			// error sent from the server (ex: if cannot contact database)
	AR_MAINTENANCE,		// maintenance mode, can't connect
	AR_BANNED,			// should receive "BANNED" only if IDs are valids
	AR_ALREADY_ONLINE,
};

// --------------
// --- STRUCT ---
// --------------
// TOP STRUCT OF ALL MESSAGES
struct Message
{
	Message(PacketType packetType, MessageType messageType, PeerType peerType) 
		: packetType(packetType), messageType(messageType), peerType(peerType)
	{}

	sf::Uint16 packetType;
	sf::Uint16 messageType;
	sf::Uint16 peerType;

	virtual sf::Packet& insertIntoPacket(sf::Packet& packet) const { return packet; }
};


// AUTH -----------------------------------------------------
struct S2C_Auth : public Message
{
	S2C_Auth(sf::Uint16 authResponse = AuthResponse::AR_NONE, std::string optionnalMessage = "")
		: Message(PacketType::AUTHENTICATION, MessageType::MT_S2C_Auth, PeerType::SERVER),	// infos
		authResponse(authResponse), optionnalMessage(optionnalMessage)						// datas
	{}

	sf::Uint16 authResponse;
	std::string optionnalMessage;
	virtual sf::Packet& insertIntoPacket(sf::Packet& packet) const { return packet << this->packetType << this->authResponse << this->optionnalMessage; }
};



struct C2S_Auth : public Message
{
	C2S_Auth(std::string user = "", std::string sha1password = "")
		: Message(PacketType::AUTHENTICATION, MessageType::MT_C2S_Auth,  PeerType::CLIENT),	// infos
		user(user), sha1password(sha1password)												// datas
	{}

	std::string user, sha1password;
	virtual sf::Packet& insertIntoPacket(sf::Packet& packet) const { return packet << this->packetType << this->user << this->sha1password; }
};

// CHAT -----------------------------------------------------
// Server To Client - Chat
struct S2C_Chat : public Message
{
	S2C_Chat(std::string from = "", std::string message = "", std::string to = "", sf::Uint16 dstType = ChatDstType::NONE)
		: Message(PacketType::CHAT, MessageType::MT_S2C_Chat,  PeerType::SERVER),		// infos
		from(from), message(message),	to(to), dstType(dstType)						// datas
	{}

	std::string from, to, message;
	sf::Uint16 dstType;
	virtual sf::Packet& insertIntoPacket(sf::Packet& packet) const { return packet << this->packetType << this->from << this->message << this->to << this->dstType; }
};


// Client To Server - Chat
struct C2S_Chat : public Message
{
	C2S_Chat(std::string message = "", std::string to = "", sf::Uint16 dstType = ChatDstType::NONE)
		: Message(PacketType::CHAT, MessageType::MT_C2S_Chat,  PeerType::CLIENT),	// infos
		message(message),	to(to), dstType(dstType)								// datas
	{}

	std::string to, message;
	sf::Uint16 dstType;
	virtual sf::Packet& insertIntoPacket(sf::Packet& packet) const { return packet << this->packetType << this->message << this->to << this->dstType; }
};

// COMMANDS  -----------------------------------------------------
// Server To Client - Commands
struct S2C_Command : public Message
{
	S2C_Command(sf::Uint16 command = ServerCommand::S_UNKNOWN_CMD, std::string argument = "")
		: Message(PacketType::COMMAND, MessageType::MT_S2C_Command,  PeerType::SERVER),	// infos
		command(command), argument(argument)											// datas
	{}

	sf::Uint16	command;
	std::string	argument;
	virtual sf::Packet& insertIntoPacket(sf::Packet& packet) const { return packet << this->packetType << this->command << this->argument; }
};

// Client To Server - Commands
struct C2S_Command : public Message
{
	C2S_Command(sf::Uint16 command = ClientCommand::C_UNKNOWN_CMD, std::string argument = "")
		: Message(PacketType::COMMAND, MessageType::MT_C2S_Command,  PeerType::CLIENT),	// infos
		command(command), argument(argument)											// datas
	{}

	sf::Uint16	command;
	std::string	argument; 
	virtual sf::Packet& insertIntoPacket(sf::Packet& packet) const { return packet << this->packetType << this->command << this->argument; }
};


class Chat {
public:
	static std::string serverCmdToString(sf::Uint16 p_command);
};