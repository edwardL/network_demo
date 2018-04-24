#ifndef CONNPOOL_H
#define CONNPOOL_H
#include "../../base/mutex.h"
#include <queue>
class IConnection;
class IConnFactory;
class ConnPool
{
public:
	~ConnPool();

	static ConnPool* Instance();
	
	void Init(IConnFactory *cf);
	void Release();

	IConnection* GetConn();
	void		 PutConn(IConnection* conn);
private:
	ConnPool();

	typedef std::queue<IConnection*> ConnList;
	ConnList	m_conn_pool;
	Mutex		m_conn_pool_lock;
	IConnFactory *m_conn_factory;
};


#endif