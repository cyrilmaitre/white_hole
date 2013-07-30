#include <iostream>
#include "ChatServer.h"

int main()
{
	//create object
	ChatServer chatServer;
	//start a server on the default port with logging enabled
	chatServer.Create();

	//wait for input to quit
	std::cout << "Ctrl + C to exit." << std::endl;
	while(1);

	return 0;
}