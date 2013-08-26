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
	}

	return "UNKNOWN";
};