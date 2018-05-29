#include "mysqlconnfactory.h"
#include "mysqlconnection.h"


MysqlConnFactory::MysqlConnFactory(std::string host,std::string user, std::string pass, std::string database,unsigned short port,std::string charset)
{
	m_host = host;
	m_user = user;
	m_pass = pass;
	m_port = port;
	m_charset = charset;
	m_database = database;
}

MysqlConnFactory::~MysqlConnFactory()
{

}

IConnection* MysqlConnFactory::CreateConn()
{
	IConnection* ic = new MysqlConnection(m_user.c_str(),m_pass.c_str(),m_database.c_str(),m_host.c_str(),m_port,m_charset.c_str());
	ic->Connect();
	return ic;
}

