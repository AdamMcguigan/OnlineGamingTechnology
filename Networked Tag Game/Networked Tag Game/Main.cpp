//Author - Adam Mcguigan
//Date - December 2022

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif

#include "Game.h"
#include "Server.h"
#include "Client.h"
#include <iostream>

int main()
{
	//int num = 0;
	//std::cout << "1 to start server, 2 to connect to a server: ";
	//std::cin >> num;

	//if (num == 1)
	//{
	//	Server MyServer(1111, false); //Create server on port 1111, false=do not loopback to localhost (others can connect)
	//	while (true)
	//	{
	//		MyServer.ListenForNewConnection(); //Accept new connection (if someones trying to connect)
	//	}
	//}
	//else if (num == 2)
	//{
	//	Client myClient("127.0.0.1", 1111); //Create client to connect to server 127.0.0.1 [localhost] on port 1111
	//	if (!myClient.Connect()) //If client fails to connect...
	//	{
	//		std::cout << "Failed to connect to server..." << std::endl;
	//		system("pause");
	//		return -1;
	//	}
	//	std::string userinput; //holds the user's chat message
	//	while (true)
	//	{
	//		std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
	//		myClient.SendString(userinput); //Send string to server
	//	}

	//	std::cin.get();
	//}

	Game game;
	game.run();

	return 0;
}