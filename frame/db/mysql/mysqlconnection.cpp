#include "mysqlconnection.h"
#include "../transaction.h"
#include "../../../mysqlconnector/v32/include/my_global.h"
#include "../../../mysqlconnector/v32/include/mysql.h"



#include <string.h>

MysqlConnection::MysqlConnection(const char* host,const char* dbuser, const char* dbpw, const char* dbname, unsigned short port, const char* dbcharset)
{
	strcpy(m_user,dbuser);
	strcpy(m_passwd, dbpw);
	strcpy(m_database,dbname);
	strcpy(m_host,host);
	m_port = port;
	strcpy(m_charset,dbcharset);
	m_mysql = 0;
	m_begin = false;
	m_isCache = false;
	//m_transaction = new ITransaction();
}

MysqlConnection::~MysqlConnection()
{

}

IConnection* MysqlConnection::Clone()
{
	return new MysqlConnection(m_host,m_user,m_passwd,m_database,m_port,m_charset);
}

bool MysqlConnection::Connect()
{
	Close();

	int ret = 0;
	MYSQL* tmp = 0;
	m_mysql = mysql_init(0);
	unsigned long client_flag = 0;
	client_flag |= CLIENT_FOUND_ROWS;
	tmp = mysql_real_connect(m_mysql,m_host,m_user,m_passwd,m_database,m_port,0,client_flag);
	if(0 == tmp)
	{
		Close();
		return false;
	}
	ret = mysql_set_character_set(m_mysql,m_charset);

	return true;
}

bool MysqlConnection::Reconnect()
{
	return Connect();
}

bool MysqlConnection::IsActive()
{
	if( 0 != m_mysql && 0 == mysql_ping(m_mysql))
	{
		return true;
	}
	return false;
}

bool MysqlConnection::IsBegin()
{
	return true;
}

void MysqlConnection::Close()
{
	if(0 != m_mysql)
	{
		mysql_close(m_mysql);
		m_mysql = 0;
	}
}

bool  MysqlConnection::SetAutoCommit(bool AutoCommit)
{
	return true;
}

bool MysqlConnection::GetAutoCommit()
{
	return true;
}

bool MysqlConnection::GetIsCache()
{
	return m_isCache;
}

int MysqlConnection::GetErrNo() const
{
	return mysql_errno(m_mysql);
}

const char* MysqlConnection::GetError() const
{
	return mysql_error(m_mysql);
}

void* MysqlConnection::GetConn()
{
	return (void*)m_mysql;
}


bool MysqlConnection::Begin(bool isCache /* = true */)
{
	if(!m_begin && 0 != m_mysql && 0 == mysql_real_query(m_mysql,"begin",sizeof("begin")))
	{
		m_begin = true;
		m_isCache = isCache;
		if(m_isCache)
		{
			m_transaction->Begin();
		}
		return true;
	}
	return false;
}

bool MysqlConnection::Commit()
{
	if(m_begin && 0 != m_mysql && 0 == mysql_commit(m_mysql))
	{
		m_begin = false;
		if(m_isCache && m_transaction->IsBegin())
		{
			m_transaction->Commit();
		}
		return true;
	}
	return false;
}

bool MysqlConnection::Rollback()
{
	if(m_begin && 0 != m_mysql && 0 == mysql_rollback(m_mysql))
	{
		m_begin = false;
		if(m_isCache && m_transaction->IsBegin())
		{
			m_transaction->Rollback();
		}
		return true;
	}
	return false;
}

long long MysqlConnection::GetInsertID()
{
	if(0 != m_mysql)
	{
		return mysql_insert_id(m_mysql);
	}
	return -1;
}