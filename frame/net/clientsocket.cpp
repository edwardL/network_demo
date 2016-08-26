#include "clientsocket.h"
#include<string.h>
#include<stdio.h>

ClientSocket::ClientSocket(const char* server_name,int port)
{
	hostent * hent;
	if((hent = gethostbyname(server_name)) == NULL)
	{
		throw "get host error";
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr = *((in_addr *)hent->h_addr);
	memset(&(addr.sin_zero),0,8);

	int ret = connect(m_socket,(sockaddr *)&addr,sizeof(sockaddr));
	if(SOCKET_ERROR == ret)
	{
		throw "connect error";
	}
}

void ClientSocket::Receive()
{
	char buff[MAX_MSG_LENGTH] = "";
	recv(m_socket,buff,MAX_MSG_LENGTH,0);
	printf("%s\n",buff);
}

void ClientSocket::Send(void* data,int length)
{
	if(!SendTo(m_socket,data,length))
	{
		printf("send failed\n");
		CloseSocket();
	}
}

