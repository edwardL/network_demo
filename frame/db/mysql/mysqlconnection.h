#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include "../connection.h"

struct st_mysql;
typedef st_mysql MYSQL;
class ITransaction;

class MysqlConnection : public IConnection
{
public:
	MysqlConnection(const char*dbuser,const char* dbpw, const char* dbname, const char* dbhost, unsigned int dbport, const char* charset);
	virtual ~MysqlConnection();

	virtual IConnection* Clone();

	virtual bool Connect();
	virtual bool Reconnect();

	virtual bool IsActive();
	virtual bool IsBegin();

	virtual void Close();
	virtual bool IsClosed();

	virtual bool SetAutoCommit(bool AutoCommit);
	virtual bool GetAutoCommit();

	virtual bool GetIsCache();

	virtual void* GetConn();
	virtual long long GetInsertID();

	virtual bool Begin(bool iscache /* = true */);
	virtual bool Commit();
	virtual bool Rollback();

	virtual IStatement* createStatement();

	virtual int GetErrNo() const;
	virtual const char* GetError() const;

private:
	MYSQL *m_mysql;

	char m_username[64];
	char m_pw[64];
	char m_host[64];
	unsigned short m_port;
	char m_charset[32];
	char m_database[64];

	bool m_connected;
	bool m_autoCommit;
	bool m_begin;
	bool m_isCache;
};

#endif