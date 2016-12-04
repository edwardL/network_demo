#ifndef ICONNFACTROY_H
#define ICONNFACTROY_H

class IConnection;

class IConnFactory
{
public:
	IConnFactory() {};
	virtual ~IConnFactory() {};
	virtual IConnection* CreateConn() = 0;
};


#endif