#include "mysqlconnection.h"
//#include "../transaction.h"
#include "../../../mysqlconnector/v32/include/my_global.h"
#include "../../../mysqlconnector/v32/include/mysql.h"
#include "mysqlstatement.h"

MysqlConnection::MysqlConnection(const char*dbuser,const char* dbpw, const char* dbname, const char* dbhost, unsigned int dbport, const char* charset)
{
	strcpy(m_username,dbuser);
	strcpy(m_pw , dbpw);
	strcpy(m_database , dbname);
	strcpy(m_host, dbhost);
	m_port = dbport;
	strcpy(m_charset , charset);

	m_connected = false;
	m_autoCommit = false;
	m_begin = false;
	m_isCache = true;

	m_mysql = 0;
}

MysqlConnection::~MysqlConnection()
{
	Close();
}

IConnection* MysqlConnection::Clone()
{
	return new MysqlConnection(m_username,m_pw,m_database,m_host,m_port,m_charset);
}

bool MysqlConnection::Connect()
{
	Close();
	int ret = 0;
	MYSQL* tmp = 0;
	m_mysql = mysql_init(0);
	unsigned long client_flag = 0;
	client_flag |= CLIENT_FOUND_ROWS;
	tmp = mysql_real_connect(m_mysql,m_host,m_username,m_pw,m_database,m_port,0,client_flag);
	if(0 == tmp)
	{
		Close();
		return false;
	}
	ret = mysql_set_character_set(m_mysql,m_charset);
	ret = SetAutoCommit(m_autoCommit);
	m_connected = true;
	return true;
}

bool MysqlConnection::Reconnect()
{
	return Connect();
}

bool MysqlConnection::IsActive()
{
	if(0 != m_mysql && 0 == mysql_ping(m_mysql))
	{
		return true;
	}
	return false;
}

bool MysqlConnection::IsBegin()
{
	return m_begin;
}

void MysqlConnection::Close()
{
	if(0 != m_mysql)
	{
		mysql_close(m_mysql);
		mysql_library_end();
		m_mysql = 0;
	}
	m_connected = false;
	m_begin = false;
}

bool MysqlConnection::IsClosed()
{
	return !m_connected;
}

bool MysqlConnection::SetAutoCommit(bool AutoCommit)
{
	if(0 != m_mysql && 0 == mysql_autocommit(m_mysql,AutoCommit))
	{
		m_autoCommit = AutoCommit;
		return true;
	}
	return false;
}

bool MysqlConnection::GetAutoCommit()
{
	return m_autoCommit;
}

bool MysqlConnection::GetIsCache()
{
	return m_isCache;
}

void* MysqlConnection::GetConn()
{
	return (void*)m_mysql;
}

long long MysqlConnection::GetInsertID()
{
	if(0 != m_mysql)
	{
		return mysql_insert_id(m_mysql);
	}
	return -1;
}

bool MysqlConnection::Begin(bool iscache )
{
	if(!m_begin && 0 != m_mysql && 0 == mysql_real_query(m_mysql,"begin",sizeof("begin")))
	{
		m_begin = true;
		m_isCache = iscache;
		return true;
	}
	return false;
}

bool MysqlConnection::Commit()
{
	if(m_begin && 0 != m_mysql && 0 == mysql_commit(m_mysql))
	{
		m_begin = false;
		return true;
	}
	return false;
}

bool MysqlConnection::Rollback()
{
	if(m_begin && 0 != m_mysql && 0 == mysql_rollback(m_mysql))
	{
		m_begin = false;
		return true;
	}
	return false;
}

IStatement* MysqlConnection::createStatement()
{
/*
	IStatement* stmt = new MysqlStatement();
	stmt->SetConnection(this);
	return stmt;
	*/
	return NULL;
}

int MysqlConnection::GetErrNo() const
{
	return mysql_errno(m_mysql);
}

const char* MysqlConnection::GetError() const
{
	return mysql_error(m_mysql);
}