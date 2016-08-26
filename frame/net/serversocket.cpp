#include "serversocket.h"
#include "../base/basetool.h"
#include<stdio.h>

void ClientAgentThread::Run()
{
	if(0 != m_server)
	{
		m_server->WaitClientMsg(m_client);
	}
}

void AcceptThread::Run()
{
	if(0 != m_server)
	{
		m_server->WaitClient();
	}
	m_exit = true;
}

ServerSocket::ServerSocket(int port)
	:m_port(port),
	m_stop(false),
	m_accept_thread(NULL)
{

}

ServerSocket::~ServerSocket()
{
	ClearAgent();
}

void ServerSocket::Start()
{
	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(m_port);
	serveraddr.sin_addr.s_addr = htons(INADDR_ANY);

	int lsock = bind(m_socket,(const SOCKADDR *)&serveraddr,sizeof(serveraddr));
	if(SOCKET_ERROR == lsock)
	{
		throw "bind error";
	}
	lsock = listen(m_socket,16);
	if(SOCKET_ERROR == lsock)
	{
		throw "listen error";
	}
	m_accept_thread = new AcceptThread(this);
	m_accept_thread->Start();
	Process();
}

void ServerSocket::Stop()
{
	m_stop = true;
}

void ServerSocket::Process()
{
	while(!m_stop)
	{

	}
}

void ServerSocket::WaitClient()
{
	while(!m_stop)
	{
		SOCKET client;
		SOCKADDR_IN clientaddr;
		ADDR_LEN addrlen = sizeof(clientaddr);
		client = accept(m_socket,(SOCKADDR *)&clientaddr,&addrlen);

		ClientAgentThread * agent = new ClientAgentThread(this,client);
		int ret =  agent->Start();
		if(0 != ret)
		{
			close_socket(client);
			delete agent;
		}
		else
		{
			m_client_agent_list.push_back(agent);
		}
	}
}

void ServerSocket::WaitClientMsg(SOCKET client)
{
	bool next = true;
	while(next && !m_stop)
	{
		char buff[MAX_MSG_LENGTH] = "";
		char data[MAX_MSG_LENGTH] = "";
		int flag = recv(client,buff,MAX_MSG_LENGTH,0);
		int msg_size =flag;
		if(SOCKET_ERROR == flag)
		{
			next = false;
			close_socket(client);
		}
		//if(msg_size > 4)
		{
		//	memcpy(data,buff + 4, msg_size - 4);
			OnMsgReceive(client,buff,msg_size);
		}
	}
}

void ServerSocket::OnMsgReceive(SOCKET socket, void* data, int length)
{
	printf("%s\n",data);
}

void ServerSocket::ClearAgent()
{
	while(true)
	{
		int count = 0;
		for(int i = 0; i < (int)m_client_agent_list.size(); ++i)
		{
			if(!m_client_agent_list[i]->IsExit())
			{
				
				count += 1;
			}
		}
		if(count <= 0)
		{
			break;
		}
		MS_SLEEP(10);
	}
	m_client_agent_list.clear();
}