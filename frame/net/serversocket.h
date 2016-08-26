#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "../net/basesock.h"
#include "../base/basethread.h"

#include <vector>

class ServerSocket;

class ClientAgentThread : public BaseThread
{
public:
	ClientAgentThread(ServerSocket* server, SOCKET client)
		:BaseThread(true)
		,m_server(server)
		,m_client(client)
	{

	}
public:
	void Run();

private:
	ServerSocket *m_server;
	SOCKET m_client;
};

class AcceptThread : public BaseThread
{
public:
	AcceptThread(ServerSocket *server)
	  :BaseThread(true)
	  ,m_server(server){}
	~AcceptThread(){}

public:
	void Run();
private:
	ServerSocket *m_server;
};

class ServerSocket : public BaseSocket
{
	friend class ClientAgentThread;
	friend class AcceptThread;
public:
	ServerSocket(int port);
	virtual ~ServerSocket();
public:
	void Start();
	void Stop();

protected:
	virtual void Process();
	void WaitClient();
	void WaitClientMsg(SOCKET client);
	virtual void OnMsgReceive(SOCKET client, void* data, int length);
	void ClearAgent();

private:
	int m_port;
	bool m_stop;
	AcceptThread *m_accept_thread;
	std::vector<ClientAgentThread *> m_client_agent_list;
};


#endif