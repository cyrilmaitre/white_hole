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
		
		ChatClient chatClient;
		bool started = false;

		// simulate game loop & mandatory for thread to live forever
		while(1)
		{
			if(!started) {
				started = true;
				chatClient.connect("testcli", "testcli");
			}
		}
	
	}

	exit(EXIT_SUCCESS);
}