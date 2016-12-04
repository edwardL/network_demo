#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include "../connection.h"

struct st_mysql;
typedef st_mysql MYSQL;
class ITransaction;


class MysqlConnection : public IConnection
{
public:
	MysqlConnection(const char* host,const char* dbuser, const char* dbpw, const char* dbname, unsigned short port, const char* charset);
	virtual ~MysqlConnection();

	// 复制链接
	virtual IConnection* Clone();

	// 连接数据库
	virtual bool Connect();
	// 重新连接数据库
	virtual bool Reconnect();

	// 连接是否活动
	virtual bool IsActive();
	// 实务是否开始
	virtual bool IsBegin();

	// 关闭连接
	virtual void Close();

	//设置是否自动提交
	virtual bool SetAutoCommit(bool AutoCommit);
	virtual bool GetAutoCommit();

	// 获取错误代码
	virtual int GetErrNo() const;
	// 获取错误字符串
	virtual const char* GetError() const;

	virtual bool GetIsCache();

	// 获取连接实体对象指针，例如MYSQL*
	virtual void* GetConn();


	//事务开始，参数表明此次事务是否使用缓存事务
	virtual bool Begin(bool isCache = true);
	// 事务提交
	virtual bool Commit();
	// 事务回滚
	virtual bool Rollback();	

private:
	MYSQL *m_mysql;

	char m_user[64];
	char m_passwd[64];
	char m_host[64];
	char m_charset[64];
	char m_database[64];
	unsigned short m_port;

	bool m_begin;
	bool m_isCache;
	ITransaction * m_transaction;
};



#endif