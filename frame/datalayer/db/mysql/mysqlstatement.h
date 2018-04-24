#ifndef MYSQLSTATEMENT_H
#define MYSQLSTATEMENT_H

#include "../statement.h"

struct st_mysql_stmt;
typedef st_mysql_stmt MYSQL_STMT;

struct st_mysql_bind;
typedef st_mysql_bind MYSQL_BIND;
class IResultset;

class MysqlStatement : public IStatement
{
public:
	MysqlStatement();
	~MysqlStatement();

	virtual void SetConnection(IConnection* conn);
	virtual IConnection* GetConnection();

	virtual void* GetStmt();
	// 返回预处理INSERT 或UPDAT 语句为AUTO_INCREMENT 列生成的值
	virtual long long GetInsertID();
	virtual bool Prepare(const char* sql);
	virtual void ClearParameters();
	virtual void Close();

	virtual bool SetByte(int paramIndex, char value);
	virtual bool SetBoolean(int paramIndex, bool value);
	virtual bool SetInt32(int paramIndex, int value);
	virtual bool SetDouble(int paramIndex, double value);
	virtual bool SetLong64(int paramIndex, long long value);
	virtual bool SetString(int paramIndex, const char* value, unsigned long length);

	virtual bool SetDate(int paramIndex, const tm& value);
	virtual bool SetTime(int paramIndex, const tm& value);
	virtual bool SetTimestamp(int paramIndex, const tm& value);

	virtual int Execute();
	virtual int Execute(const char* sql);

	
	IResultset* ExecuteQuery();
	IResultset* ExecuteQuery(const char* sql);
	

protected:
	bool ValidIndex(int index);
	void InitParams();
	void CleanParam(MYSQL_BIND* param);
	void DestroyParams();

private:
	IConnection* m_conn;
	MYSQL_STMT*  m_stmt;
	int			 m_paramcount;
	MYSQL_BIND*  m_params;
};



#endif