#include "Network.h"
#include "Manager.h"


//*************************************************************
// Init static
//*************************************************************
sf::Http Network::http;


//*************************************************************
// Constructor - Destructor
//*************************************************************
Network::Network(void)
{
}

Network::~Network(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void Network::init()
{
	Network::http.setHost(Manager::getInstance()->getConfig()->getHttpHost(), Manager::getInstance()->getConfig()->getHttpHostPort());
}

sf::Http::Response Network::sendJsonRequest( sf::Http::Request::Method p_method, std::string p_uri, std::string p_json )
{
	std::map<std::string, std::string> map;
	map.insert(std::pair<std::string, std::string>("Content-type", "application/json"));
	return Network::sendRequest(p_method, p_uri, p_json, map);
}

sf::Http::Response Network::sendRequest( sf::Http::Request::Method p_method, std::string p_uri, std::string p_body, std::map<std::string, std::string> p_fields )
{
	// Send request
	sf::Http::Request request;
	request.setMethod(p_method);
	request.setUri(p_uri);
	if(p_body != "")
		request.setBody(p_body);
	for( std::map<std::string, std::string>::iterator it = p_fields.begin() ; it != p_fields.end(); it++ )
		request.setField((*it).first, (*it).second);
	request.setHttpVersion(1, 0);

	// Get response
	return Network::http.sendRequest(request);
}


