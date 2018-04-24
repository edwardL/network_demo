#ifndef ISTATEMENT_H
#define ISTATEMENT_H

#include "dbdef.h"

class IConnection;
class IResultSet;

class IStatement
{
public:
	IStatement(){};
	virtual ~IStatement(){};

	virtual void SetConnection(IConnection* conn)= 0;
	virtual IConnection* GetConnection() = 0;

	// 获得语句实体对象指针，如MYSQL_STMT*
	virtual void* GetStmt() = 0;
	// 返回预处理insert 或update 语句为auto_increment 列生成的值
	virtual long long GetInsertID() = 0;

	virtual bool Prepare(const char* sql) = 0;
	virtual void ClearParameters() = 0;
	virtual void Close() = 0;

	// 写入一个字节
	virtual bool SetByte(int paramIndex, char value) = 0;
	virtual bool SetBoolean(int paramIndex, bool value) = 0;
	// 写入一个32位整形
	virtual bool SetInt32(int paramIndex, int value) = 0;
	virtual bool SetDouble(int paramIndex, double value) = 0;
	virtual bool SetLong64(int paramIndex, long long value) = 0;

	// 写入字符串，例如mysql中的VARCHAR
	virtual bool SetString(int paramIndex, const char* value, unsigned long length) = 0;

	virtual bool SetDate(int paramIndex, const tm& value) = 0;  /// DATETIME
	virtual bool SetTime(int paramIndex, const tm& value) = 0;	/// TIME
	virtual bool SetTimestamp(int paramIndex, const tm& value) = 0; // TIMESTAMP

	virtual int Execute() = 0;
	virtual int Execute(const char* sql) = 0;

	/*
	virtual IResultset* ExecuteQuery() = 0;
	virtual IResultset* ExecuteQuery(const char* sql) = 0;
	*/
	};


#endif