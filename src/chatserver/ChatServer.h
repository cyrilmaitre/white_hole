#pragma once
#include <list>
#include <SFML/Network.hpp>

#define SERVER_NAME				"Makaki"
#define SERVER_MOTD				"Sisi la famille"
#define MAX_CLIENTS				1
#define MAX_PACKETSEND_RETRY	5

// ------------
// --- ENUM ---
// ------------

enum ClientState
{
	UNKNOWN_CS,
	TCP_CONNECTED,
	DROPPED,
	AUTHED,
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

// Client To Server - Chat
struct C2S_Chat
{
	C2S_Chat(std::string message = "", std::string to = "", sf::Uint16 dstType = ChatDstType::NONE)
		: message(message),	to(to), dstType(dstType)
	{}

	std::string to, message;
	sf::Uint16 dstType;
};

struct Client
{
	Client()
		: socket(std::unique_ptr<sf::TcpSocket>(new sf::TcpSocket)), state(ClientState::UNKNOWN_CS)
	{}

	ClientState state;
	std::unique_ptr<sf::TcpSocket> socket;
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
	void Create(unsigned short port);
	void AddClient(std::shared_ptr<Client> client);
	void DropClient(std::shared_ptr<Client> client);
	void HandlePacket(sf::Packet& packet, std::shared_ptr<Client> client);
	bool SendPacket(sf::Packet &packet, std::shared_ptr<Client> client);
	void Broadcast(sf::Packet& packet);
	void Disconnect(void);

private:
	sf::SocketSelector selector;
	sf::TcpListener listener;
	std::list< std::shared_ptr<Client> > clients;	// List to store the future clients
	unsigned short mPort;
	bool mRunning;
	void mRunServer(void);
};