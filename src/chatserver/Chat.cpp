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

	case ServerCommand::S_USERLIST_RESYNC:
		return "USERLIST RESYNC";
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

// -------------------------------
//  ----------- TOOLS ------------
// -------------------------------
// return TRUE if a string is in a vector<string>
bool Chat::stringInVector(std::string& p_testString, std::vector<std::string>& p_testVector)
{
	return (std::find(p_testVector.begin(), p_testVector.end(), p_testString) != p_testVector.end());
}



// return a string with letters (A-Z) in lowercase
std::string	Chat::lowerLetters(std::string& p_string)
{
	std::string loweredString = "";

	// 65-90  = MAJ letters
	// 97-122 = MIN letters
	for(std::string::size_type i = 0; i < p_string.size(); ++i) {

		// if char is A-Z
		if(p_string[i] >= 65 && p_string[i] <= 90) {
			loweredString += (char)p_string[i]+32;
		}
		else {
			loweredString += (char)p_string[i];
		}
	}


	return loweredString;
}

sf::Http::Response Chat::sendJsonRequest( sf::Http::Request::Method p_method, std::string p_uri, std::string p_json )
{
	sf::Http http;
	http.setHost("makakistudio", 8080);

	std::map<std::string, std::string> fields;
	fields.insert(std::pair<std::string, std::string>("Content-type", "application/json"));

	// Send request
	sf::Http::Request request;
	request.setMethod(p_method);
	request.setUri(p_uri);
	if(p_json != "")
		request.setBody(p_json);
	for( std::map<std::string, std::string>::iterator it = fields.begin() ; it != fields.end(); it++ )
		request.setField((*it).first, (*it).second);
	request.setHttpVersion(1, 0);

	// Get response
	return http.sendRequest(request);
}