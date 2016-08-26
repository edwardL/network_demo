#pragma once

#ifndef INETWORKMODULE_H
#define INETWORKMODULE_H

#include "imodule.h"
#include <string>
#include <WinSock2.h>
#pragma comment(lib,"WS2_32")

static const char NETWORK_MODULE[] = "NetworkModule";

typedef unsigned int NetID;
typedef unsigned int IP;
typedef unsigned short Port;

class IEngineNetCallback
{
public:
	virtual ~IEngineNetCallback(){}

	virtual void OnAccept(Port listen_port, NetID netid, IP ip, Port port) =0;
	
	virtual void OnRecv(NetID netid, const char* data , int length) =  0;

	virtual void OnDisconnect(NetID netid) = 0;

	virtual void OnConnect(bool result, int handle, NetID netid, IP ip , Port port) =0;
	
};
class LoginServerModule;
class ServerInternalNetCallback : public IEngineNetCallback
{
public:
	ServerInternalNetCallback(LoginServerModule* server):m_server(server){}
	~ServerInternalNetCallback(){}
	void SetAllowIpPrefix(const std::string &allow_ip_prefix){m_allow_ip_prefix == allow_ip_prefix;}
	/// listen port 为监听的端口
	virtual void OnAccept(Port listen_port, NetID netid, IP ip, Port port)
	{
		/// 检查IP 前缀是否合法
	}
	virtual void OnRecv(NetID netid, const char* data , int length)
	{

	}

	virtual void OnDisconnect(NetID netid)
	{

	}

	virtual void OnConnect(bool result, int handle, NetID netid, IP ip , Port port)
	{

	}
private:
	LoginServerModule *m_server;
	std::string m_allow_ip_prefix;
};
class INetworkModule : public IModule
{
public:
	virtual int Init() =0;
	virtual int Start() =0;
	virtual int Update() =0;
	virtual int Stop() =0;
	virtual int Release() = 0;
	virtual void Free() = 0;

	/* 注册网络消息回调*/
	virtual void RegisterCallback(IEngineNetCallback *callback) =0;

};

#endif