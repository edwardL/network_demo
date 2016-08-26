#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
#include "basesock.h"

class ClientSocket : public BaseSocket
{
public:
	ClientSocket(const char* server_name,int port);
	virtual~ClientSocket(){}
	void Receive();
	void Send(void* data, int length);
};

#endif