#include "serversockettest.h"
#include "../frame/net/serversocket.h"

void ServerSocketDemo::Start()
{
	socket_init();
	ServerSocket server(5555);
	server.Start();
	while(1)
	{

	}
	socket_clean();
}