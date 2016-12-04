#ifndef MYSQL_STATEMENT_H
#define MYSQL_STATEMENT_H

#include "../statement.h"

struct st_mysql_stmt;
typedef st_mysql_stmt MYSQL_STMT;

struct st_mysql_bind;
typedef st_mysql_bind MYSQL_BIND;

class MysqlStatement:public IStatement
{
public:
	MysqlStatement();
	~MysqlStatement();

	virtual void SetConnection(IConnection* conn);
	virtual IConnection* GetConnection();

	virtual void* GetStmt();

	// 返回预处理insert 或update 语句为AUTO_INCREMENT 列生成的值
	virtual long long GetInsertID();

	virtual bool Prepare(const char* sql);
	virtual void ClearParameters();
	virtual void Close();

	virtual bool SetBype(int paramIndex, char value);
	virtual bool SetBoolean(int paramIndex, bool value);
	virtual bool SetInt32(int paramIndex, int value);
	virtual bool SetDouble(int paramIndex, double value);
	virtual bool SetLong64(int paramIndex, long long value);
	virtual bool SetString(int paramIndex, const char* value,unsigned long length);
	virtual bool SetDate(int paramIndex, const tm& value);
	virtual bool SetTime(int param, const tm& value);
	virtual bool SetTimeStamp(int paramIndex, const tm& value);

	virtual int Execute(/* = 0 */);
	virtual int Execute(const char* mysql);

	virtual IResultset* ExecuteQuery();
	virtual IResultset* ExecuteQuery(const char* sql);

protected:
	bool ValidIndex(int index);
	void InitParams();
	void CleanParam(MYSQL_BIND* param);
	void DestroyParams();

private:
	IConnection*	m_conn;
	MYSQL_STMT*		m_stmt;
	MYSQL_BIND*		m_params;
	int				m_paramcount;
};

#endif