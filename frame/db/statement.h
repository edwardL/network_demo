
#ifndef ISTATEMENT_H
#define ISTATEMENT_H

#include <time.h>
#include "dbdef.h"

class IConnection;
class IResultset;

class IStatement
{
public:
	IStatement(){};
	virtual ~IStatement(){};

	virtual void SetConnection(IConnection* conn) = 0;
	virtual IConnection* GetConnection() = 0;

	//������ʵ�����ָ�룬��MYSQL_STMT*
	virtual void* GetStmt() = 0;
	//����Ԥ����INSERT��UPDATE���ΪAUTO_INCREMENT�����ɵ�ֵ
	virtual long long GetInsertID() = 0;

	virtual bool Prepare(const char* sql) = 0;
	virtual void ClearParameters() = 0;
	virtual void Close() = 0;

	//д��һ���ֽڣ�����mysql�е�TINYINT
	virtual bool SetByte(int paramIndex, char value) = 0;
	//д��N���ֽڣ�����mysql�е�BLOB/TEXT
	//virtual bool setBytes(int paramIndex, const char* value, int length) = 0;

	//д��һ��������
	virtual bool SetBoolean(int paramIndex, bool value) = 0;

	//д��һ��32λ���ͣ�����mysql�е�INT
	virtual bool SetInt32(int paramIndex, int value) = 0;
	//д��һ��˫���ȸ����ͣ�����mysql�е�DOUBLE
	virtual bool SetDouble(int paramIndex, double value) = 0;
	//д��һ��64λ��������mysql�е�BIGINT
	virtual bool SetLong64(int paramIndex, long long value ) = 0;

	//д���ַ���������mysql�е�VARCHAR
	virtual bool SetString(int paramIndex, const char* value, unsigned long length) = 0;

	//д������+ʱ�䣬����mysql�е�DATETIME
	virtual bool SetDate(int paramIndex, const tm& value) = 0;
	//д��ʱ�䣬����mysql�е�TIME
	virtual bool SetTime(int paramIndex, const tm& value) = 0;
	//д��ʱ�䣬����mysql�е�TIMESTAMP�������ֶθ���ʱ�����Զ�����
	virtual bool SetTimestamp(int paramIndex, const tm& value) = 0;

	virtual int Execute() = 0;
	virtual int Execute(const char* sql) = 0;

	//virtual int executeUpdate() = 0;
	//virtual int executeUpdate(const char* sql) = 0;

	virtual IResultset* ExecuteQuery() = 0;
	virtual IResultset* ExecuteQuery(const char* sql) = 0;

};

#endif
