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
	}

	return "UNKNOWN";
};