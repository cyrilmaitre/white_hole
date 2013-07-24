#pragma once
#include "Resource.h"

class Network
{
public:
	static void init();

	static sf::Http::Response sendRequest(sf::Http::Request::Method p_method, std::string p_uri, std::string p_body, std::map<std::string, std::string> p_fields);
	static sf::Http::Response sendJsonRequest(sf::Http::Request::Method p_method, std::string p_uri, std::string p_json = "");

private:
	// Constructor - Destructor
	Network(void);
	~Network(void);

	// Attributs
	static sf::Http http;
};

