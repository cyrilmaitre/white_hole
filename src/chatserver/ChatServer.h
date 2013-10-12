#pragma once
#include "Chat.h"
#include "Client.h"
#include <vector>

#define SERVER_NAME				"Makaki"
#define SERVER_MOTD				"Sisi la famille"
#define MAX_CLIENTS				5000				// max client allowed on server
#define MAX_IP_TOGETHER			15					// nd de connexion max par IP
#define MAX_S_PACKETSEND_RETRY	5					// if 5+ packets are not received by the client, then drop it
#define PING_IDLE_TIME			120					// if nothing received for 120s from the client, then ping it.
#define PING_TIMEOUT			100					// client must PONG within 100s
#define AUTH_TIMEOUT			30					// 30s to authenticate
#define FLOOD_INTERVAL			1					// control flood on X seconds
#define FLOOD_MAX_PACKETS		20					// max packets allowed in FLOOD_INTERVAL

// -------------
// --- CLASS ---
// -------------

// Client To Server - Chat
struct BroadcastCondition
{
	BroadcastCondition(
		sf::Uint64 ignoreClientID = 0,
		ClientState clientState = ClientState::UNKNOWN_CS,
		ClientAttributes clientHasAttributes = ClientAttributes::ATTR_NONE
		)
		: ignoreClientID(ignoreClientID), clientState(clientState),	clientHasAttributes(clientHasAttributes)
	{}

	sf::Uint64 ignoreClientID;
	ClientState clientState;
	ClientAttributes clientHasAttributes;
};



enum AsyncRequestCode
{
	ASR_UNKNOWN,
	ASR_AUTHENTICATE,
	ASR_FETCH_FRIENDLIST,
	ASR_DONE
};

struct AsyncRequest
{
	AsyncRequest(std::weak_ptr<Client> client, AsyncRequestCode asyncRequestCode = AsyncRequestCode::ASR_UNKNOWN)
		: client(client), asyncRequestCode(asyncRequestCode), timestamp((sf::Uint64)time(NULL))
	{

	}
	std::weak_ptr<Client>	client;
	AsyncRequestCode		asyncRequestCode;
	sf::Uint64				timestamp;

};


class ChatServer
{
public:
	ChatServer(void);
	void create(void);
	void create(unsigned short p_port);
	void addClient(std::shared_ptr<Client> p_client);
	bool authenticate(std::weak_ptr<Client> p_wclient, C2S_Auth p_auth);
	bool authenticate(std::weak_ptr<Client> p_wclient);
	void dropClient(std::weak_ptr<Client> p_wclient);
	void handlePacket(sf::Packet& p_packet, std::weak_ptr<Client> p_wclient);
	bool sendPacket(sf::Packet& p_packet, std::weak_ptr<Client> p_wclient, bool dropClientIfFailed = false);
	void broadcast(sf::Packet& p_packet, BroadcastCondition& p_broadcastCond);
	void disconnect(void);
	
	std::shared_ptr<Client> findClientByName(std::string p_name);
	std::shared_ptr<Client> findClientByUID(sf::Uint64 p_uid);

	sf::Uint32 connectionCountByIP(sf::IpAddress p_compareIP);

	// threads
	sf::Mutex& getMutex(void);

	// running
	bool isRunning(void);
	void setRunning(bool p_running);

private:
	sf::SocketSelector selector;
	sf::TcpListener listener;
	std::vector<std::shared_ptr<Client>> clients;	// List to store the future clients
	unsigned short mPort;
	bool mRunning;
	void mRunServer(void);

	// friend lists
	std::map<std::string, std::vector<std::string>> mClientFriendlists;

	// threads
	sf::Mutex					mMutex;
	std::unique_ptr<sf::Thread> mThread;
	void						mAsyncTasks(void);

	std::unique_ptr<sf::Thread> mThreadCLI;
	void						mCLI(void);

	// async requests
	std::vector<AsyncRequest> mAsyncRequests;


};
