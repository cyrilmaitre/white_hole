#pragma once
#include <list>
#include <SFML/Network.hpp>

#define SERVER_NAME		"Makaki"
#define SERVER_MOTD		"Sisi la famille"
#define MAX_CLIENTS		1200

// ------------
// --- ENUM ---
// ------------

enum ClientState
{
	UNKNOWN_CS,
	TCP_CONNECTED,
	AUTHED,
	OFFLINE,
	MUTED
};

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


enum ChatDstType
{
	NONE,
	USER,
	CHANNEL
};

enum S2C_Type
{
	CHAT,
	COMMAND
};

// --------------
// --- STRUCT ---
// --------------

// Server To Client - Chat
struct S2C_Chat
{
	S2C_Chat(std::string from = "", std::string message = "", std::string to = "", sf::Uint16 dstType = ChatDstType::NONE)
		: from(from), message(message),	to(to), dstType(dstType)
	{}

	std::string from, to, message;
	sf::Uint16 dstType;
};

// Server To Client - Commands
struct S2C_Command
{
	S2C_Command(sf::Uint16 command = ServerCommand::UNKNOWN_CMD, std::string argument = "")
		: command(command), argument(argument)
	{}

	sf::Uint16 command;
	std::string argument;
};

struct Client
{
	Client()
		: socket(std::unique_ptr<sf::TcpSocket>(new sf::TcpSocket)), uid(0), state(ClientState::UNKNOWN_CS)
	{
		//generate a unique ID from location in memory
		uid = (sf::Uint32)socket.get();
	}
	ClientState state;
	std::unique_ptr<sf::TcpSocket> socket;
	sf::Uint32 uid;
	std::string name;
};

// -------------
// --- CLASS ---
// -------------

class ChatServer
{
public:
	ChatServer(void);
	void Create(void);
	void Create(sf::Uint16 port);
	void Broadcast(sf::Packet packet);
	void Disconnect(void);

private:
	sf::Uint16 mPort;
	std::unique_ptr<sf::Thread> mNetThread;
	bool mRunThread;
	sf::Mutex mMutex;

	void mRunServer(void);	// Threaded function (1 server/language: EN, FR ? see later)
};