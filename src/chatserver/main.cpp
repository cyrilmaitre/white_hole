#include <iostream>
#include "ChatServer.h"
#include "ChatClient.h"		
#ifdef  _DEBUG
#include <vld.h>
#endif




int main(int argc, char** argv)
{

	std::cout << "Enter 's' to start server / 'c' to start client: ";
	std::string str;
	std::cin >> str;

	// server
	if(str == "s")
	{
		//create object
		ChatServer chatServer;
		//start a server on the default port
		chatServer.create();

	}
	// client
	else if(str == "c")
	{
		
		ChatClient chatClient3;
		ChatClient chatClient4;
		ChatClient chatClient5;
		ChatClient chatClient6;
		ChatClient chatClient7;
		ChatClient chatClient8;
		bool started = false;

		// simulate game loop & mandatory for thread to live forever
		while(1)
		{
			if(!started) {
				started = true;
				chatClient3.connect("watwat3", "b754d59302ca2aaaa54dc6cd42a6e963d60d99c");
				chatClient4.connect("watwat4", "b754d59302ca2aaaa54dc6cd42a6e963d60d99c");
				chatClient5.connect("watwat5", "b754d59302ca2aaaa54dc6cd42a6e963d60d99c");
				chatClient6.connect("watwat6", "b754d59302ca2aaaa54dc6cd42a6e963d60d99c");
				chatClient7.connect("watwat7", "b754d59302ca2aaaa54dc6cd42a6e963d60d99c");
				chatClient8.connect("watwat8", "b754d59302ca2aaaa54dc6cd42a6e963d60d99c");
			} else {
				sf::sleep(sf::seconds(1));
			}
		}
	
	}

	exit(EXIT_SUCCESS);
}