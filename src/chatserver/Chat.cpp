#include "Chat.h"

std::string Chat::serverCmdToString(sf::Uint16 p_command)
{
	switch(p_command)
	{
	case ServerCommand::S_UNKNOWN_CMD:
		return "UNKNOWN_CMD";
		break;

	case ServerCommand::S_JOIN:
		return "JOIN";
		break;

	case ServerCommand::S_QUIT:
		return "QUIT";
		break;

	case ServerCommand::S_KICK:
		return "KICK";
		break;

	case ServerCommand::S_MOTD:
		return "MOTD";
		break;

	case ServerCommand::S_SAY:
		return "SAY";
		break;

	case ServerCommand::S_MUTE:
		return "MUTE";
		break;

	case ServerCommand::S_PING:
		return "PING";
		break;

	case ServerCommand::S_CHAT_PEER_OFFLINE:
		return "USER OFFLINE";
		break;

	case ServerCommand::S_CHAT_PEER_AFK:
		return "USER AFK";
		break;

	case ServerCommand::S_FRIEND_ADD:
		return "FRIEND INVITATION RECEIVED";
		break;

	case ServerCommand::S_AFK_ON:
		return "AFK MODE ENABLED";
		break;

	case ServerCommand::S_AFK_OFF:
		return "AFK MODE DISABLED";
		break;

	case ServerCommand::S_PEER_NOTEXIST:
		return "USER DOES NOT EXIST";
		break;

	case ServerCommand::S_CONFIRM_FRIEND_ADD:
		return "FRIEND INVITATION SENT";
		break;

	case ServerCommand::S_CONFIRM_FRIEND_IGNORE:
		return "USER BLOCKED";
		break;

	case ServerCommand::S_CONFIRM_FRIEND_DEL:
		return "USER DELETED FROM FRIENDLIST";
		break;
		
	case ServerCommand::S_FRIEND_OFFLINE:
		return "FRIEND OFFLINE";
		break;

	case ServerCommand::S_FRIEND_ONLINE:
		return "FRIEND ONLINE";
		break;
	}

	return "UNKNOWN";
}


std::string Chat::authResponseToString(sf::Uint16 p_authResponse)
{
	switch(p_authResponse)
	{
	case AuthResponse::AR_NONE:
		return "No response";
		break;

	case AuthResponse::AR_OK:
		return "OK";
		break;

	case AuthResponse::AR_INVALID_IDS:
		return "Invalid username/password";
		break;

	case AuthResponse::AR_ERROR:
		return "Error";
		break;

	case AuthResponse::AR_MAINTENANCE:
		return "Chat server is in maintenance mode";
		break;

	case AuthResponse::AR_BANNED:
		return "You are banned";
		break;
	}


	return "Unknown response";
}