#include <iostream>
#include "ChatServer.h"

#include <vector>
#include "SFML\Network.hpp"

int main(int argc, char** argv)
{
	//create object
	ChatServer chatServer;
	//start a server on the default port
	chatServer.Create();

	//wait for input to quit
	std::cout << "Ctrl + C to exit." << std::endl;
	while(1);

	return 0;
}