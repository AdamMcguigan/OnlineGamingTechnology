/*
Author: Pindrought
Date: 2/24/2016
This is the solution for the server that you should have at the end of tutorial 7.
*/

#include "Server.h"

int main()
{
	Server MyServer(623); //Create server on port 623
	for (int i = 0; i < 100; i++) //Up to 100 times...
	{
		MyServer.ListenForNewConnection(); //Accept new connection (if someones trying to connect)
		MyServer.checkGameReady();
	}

	system("pause");
	return 0;
}