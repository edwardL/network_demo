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

	// ������ʵ�����ָ�룬��MYSQL_STMT*
	virtual void* GetStmt() = 0;
	// ����Ԥ����insert ��update ���Ϊauto_increment �����ɵ�ֵ
	virtual long long GetInsertID() = 0;

	virtual bool Prepare(const char* sql) = 0;
	virtual void ClearParameters() = 0;
	virtual void Close() = 0;

	// д��һ���ֽ�
	virtual bool SetByte(int paramIndex, char value) = 0;
	virtual bool SetBoolean(int paramIndex, bool value) = 0;
	// д��һ��32λ����
	virtual bool SetInt32(int paramIndex, int value) = 0;
	virtual bool SetDouble(int paramIndex, double value) = 0;
	virtual bool SetLong64(int paramIndex, long long value) = 0;

	// д���ַ���������mysql�е�VARCHAR
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