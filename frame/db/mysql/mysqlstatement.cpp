#include "../../../mysqlconnector/v32/include/my_global.h"
#include "../../../mysqlconnector/v32/include/mysql.h"

#include "../connection.h"
#include "mysqlstatement.h"


MysqlStatement::MysqlStatement()
{
	m_conn = 0;
	m_stmt = 0;
	m_params = 0;
	m_paramcount = 0;
}

MysqlStatement::~MysqlStatement()
{
	Close();
	m_conn = 0;
}

void MysqlStatement::SetConnection(IConnection* conn)
{
	m_conn = conn;
}

IConnection* MysqlStatement::GetConnection()
{
	return m_conn;
}

long long MysqlStatement::GetInsertID()
{
	if(0 != m_stmt)
	{
		return mysql_stmt_insert_id(m_stmt);
	}
	if(0 != m_conn)
	{
		
	}
	return -1;
}

bool MysqlStatement::Prepare(const char* sql)
{
	if(0 == m_stmt)
	{
		Close();
	}
	if(0 == m_conn)
	{
		return false;
	}
	MYSQL* tmp  = (MYSQL*)(m_conn)->GetConn();
	if(0 == tmp)
	{
		return false;
	}

	m_stmt = mysql_stmt_init(tmp);
	if(0 == m_stmt)
	{
		return false;
	}

	int ret = mysql_stmt_prepare(m_stmt,sql,(unsigned long)strlen(sql));
	if(0 != ret)
	{
		Close();
		return false;
	}
}


/// 设置数据
bool MysqlStatement::SetBype(int paramIndex, char value)
{
	if(!ValidIndex(paramIndex))
		return false;
	MYSQL_BIND *bind = &m_params[paramIndex];
	bind->buffer_type = MYSQL_TYPE_TINY;
	bind->buffer = malloc(sizeof(char)); // 迟点用内存池实现
	*((unsigned char*)bind->buffer) = (unsigned char)value;
	bind->length = 0;
	return true;
}

bool MysqlStatement::SetBoolean(int paramIndex, bool value)
{
	return SetBype(paramIndex,value);
}

bool MysqlStatement::SetInt32(int paramIndex, int value)
{
	if(!ValidIndex(paramIndex))
	{
		return false;
	}
	MYSQL_BIND *bind = &m_params[paramIndex];
	bind->buffer_type = MYSQL_TYPE_LONG;
	bind->buffer = malloc(sizeof(int));
	(*(int*)bind->buffer) = value;
	bind->length = 0;
	return true;
}

bool MysqlStatement::SetDouble(int paramIndex, double value)
{
	if(!ValidIndex(paramIndex))
		return false;
	MYSQL_BIND *bind = &m_params[paramIndex];
	bind->buffer_type = MYSQL_TYPE_DOUBLE;
	bind->buffer = malloc(sizeof(double));
	*(double*)bind->buffer = value;
	bind->length = 0;
	return true;
}

bool MysqlStatement::SetLong64(int paramIndex, long long value)
{
	if(!ValidIndex(paramIndex))
		return false;
	MYSQL_BIND* bind = &m_params[paramIndex];
	bind->buffer_type = MYSQL_TYPE_LONGLONG;
	bind->buffer = malloc(sizeof(long long));
	*(long long*)bind->buffer = value;
	bind->length = 0;
	return true;
}

bool MysqlStatement::SetString(int paramIndex, const char* value,unsigned long length)
{
	if(!ValidIndex(paramIndex))
		return false;
	MYSQL_BIND *bind = &m_params[paramIndex];
	bind->buffer_type = MYSQL_TYPE_VAR_STRING;
	bind->buffer_length = length;
	bind->buffer = malloc(length);
	memcpy(bind->buffer,value,length);
	bind->length = 0;
	return true;
}

bool MysqlStatement::SetDate(int paramIndex, const tm& value)
{
	if(!ValidIndex(paramIndex))
		return false;
	MYSQL_BIND *bind = &m_params[paramIndex];
	bind->buffer_type = MYSQL_TYPE_DATETIME;
	bind->buffer = malloc(sizeof(MYSQL_TIME));
	memset(bind->buffer,0,sizeof(MYSQL_TIME));
	((MYSQL_TIME*)bind->buffer)->year = value.tm_year;
	((MYSQL_TIME*)bind->buffer)->month = value.tm_mon;
	((MYSQL_TIME*)bind->buffer)->day = value.tm_mday;
	((MYSQL_TIME*)bind->buffer)->hour = value.tm_hour;
	((MYSQL_TIME*)bind->buffer)->minute = value.tm_min;
	((MYSQL_TIME*)bind->buffer)->second = value.tm_sec;

	bind->length = 0;
	return true;
}

bool MysqlStatement::SetTime(int param, const tm& value)
{
	if(!ValidIndex(param))
		return false;
	MYSQL_BIND *bind = &m_params[param];
	bind->buffer_type = MYSQL_TYPE_TIMESTAMP;
	bind->buffer = malloc(sizeof(MYSQL_TIME));
	memset(bind->buffer,0,sizeof(MYSQL_TIME));
	((MYSQL_TIME*)bind->buffer)->year = value.tm_year;
	((MYSQL_TIME*)bind->buffer)->month = value.tm_mon;
	((MYSQL_TIME*)bind->buffer)->day = value.tm_mday;
	((MYSQL_TIME*)bind->buffer)->hour = value.tm_hour;
	((MYSQL_TIME*)bind->buffer)->minute = value.tm_min;
	((MYSQL_TIME*)bind->buffer)->second = value.tm_sec;
	
	bind->length =0;
	return true;
}

int MysqlStatement::Execute()
{
	if(0 == m_stmt || 0 != mysql_stmt_bind_param(m_stmt,m_params) || 0 != mysql_stmt_execute(m_stmt))
	{
		return -1;
	}
	return (int)(mysql_stmt_affected_rows(m_stmt));
}

int MysqlStatement::Execute(const char* sql)
{
	Close();
	if(0 == m_conn || 0 != mysql_real_query((MYSQL*)(m_conn->GetConn()),sql,(unsigned long)strlen(sql)))
	{
		return -1;
	}
	return (int)(mysql_affected_rows((MYSQL*)(m_conn->GetConn())));
}

