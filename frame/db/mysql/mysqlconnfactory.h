#ifndef MYSQLCONNFACTROY_H
#define MYSQLCONNFACTROY_H

#include "../connfactroy.h"
#include <string>

class MysqlConnFactory : public IConnFactory
{
public:
	MysqlConnFactory(std::string host,std::string user, std::string pass,std::string database, unsigned short port,std::string charset);
	virtual ~MysqlConnFactory();
	virtual IConnection* CreateConn();

private:
	std::string m_host;
	std::string m_user;
	std::string m_pass;
	unsigned short m_port;
	std::string m_charset;
	std::string m_database;
};

#endif