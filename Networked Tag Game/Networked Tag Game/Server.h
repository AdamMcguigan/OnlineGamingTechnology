#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h> // For win sockets
#include <string> // For std::string
#include <vector> // For std::vector
#include <shared_mutex> // for shared_mutex

#include "FileTransferData.h" // For FileTransferData class
#include "PacketManager.h" // For PacketManager class

class Connection
{
public:

	Connection(SOCKET socket)
		:m_socket(socket)
	{
	}
	SOCKET m_socket;

	//file transfer data
	FileTransferData m_file; // Object that contains information about our file that is being sent to the client from this server
	PacketManager m_pm; // Packet Manager for outgoing data for this connection
	int m_ID = 0;

};

class Server
{
public:

	Server(int port, bool loopBacktoLocalHost = true);
	~Server();
	bool ListenForNewConnection();

private:

	bool sendall(std::shared_ptr<Connection> connection, const char* data, const int totalBytes);
	bool recvall(std::shared_ptr<Connection> connection, char* data, int totalBytes);
	bool Getint32_t(std::shared_ptr<Connection> connection, std::int32_t& int32_t);
	bool GetPacketType(std::shared_ptr<Connection> connection, PacketType& packetType);
	void SendString(std::shared_ptr<Connection> connection, const std::string& str);
	bool GetString(std::shared_ptr<Connection> connection, std::string& str);

	bool ProcessPacket(std::shared_ptr<Connection> connection, PacketType packetType);

	static void ClientHandlerThread(Server& server, std::shared_ptr<Connection> connection);
	static void PacketSenderThread(Server& server);
	void DisconnectClient(std::shared_ptr<Connection> connection); //Called to properly disconnect and clean up a client (if possible)

private:

	std::vector<std::shared_ptr<Connection>> m_connections;
	std::shared_mutex m_mutex_connectionMgr; //mutex for managing connections (used when a client disconnects)
	int m_IDCounter = 0;
	SOCKADDR_IN m_addr; //Address that we will bind our listening socket to
	SOCKET m_sListen;
	bool m_terminateThreads = false;
	std::vector<std::thread*> m_threads; //so destructor can wait on created threads to end...

};

#endif // !SERVER_H