#ifndef ISTATEMENT_H
#define ISTATEMENT_H

class IConnection;
class IResultset;
class IStatement
{
public:
	IStatement(){};
	~IStatement(){};

	virtual void SetConnection(IConnection* conn) =0;
	virtual IConnection* GetConnection() =0 ;

	// ������ʵ�����ָ��,��MYSQL_STMT
	virtual void* GetStmt() = 0;
	// ����Ԥ����insert ��update ���Ϊauto_increment �����ɵ�ֵ
	virtual long long GetInsertID() = 0;

	virtual bool Prepare(const char* sql) = 0;
	virtual void ClearParameters() = 0;
	virtual void Close() = 0;

	//д��һ���ֽڣ���mysql ��TINYINT
	virtual bool SetBype(int paramIndex, char value) = 0;
	// д��N ���ֽڣ� ��mysql ��BLOB/TEXT

	// д��һ������ֵ
	virtual bool SetBoolean(int paramIndex, bool value) = 0;

	//д��һ��32 λ���Σ�����mysql �е�INT
	virtual bool SetInt32(int paramIndex, int value) = 0;

	// д��һ��Double
	virtual bool SetDouble(int paramIndex, double value) =0;

	// д��64 λ���� ����MYSQL ��big int
	virtual bool SetLong64(int paramIndex, long long value) = 0;

	// д���ַ����� ����mysql ��varchar
	virtual bool SetString(int paramIndex, const char* value,unsigned long length) =0;

	// д������+ ʱ�䣬 ����mysql �е�DATETIME
	virtual bool SetDate(int paramIndex, const tm& value) = 0;
	// д��ʱ�䣬����mysql �е�TIME
	virtual bool SetTime(int param, const tm& value) = 0;
	virtual bool SetTimeStamp(int paramIndex, const tm& value);

	virtual int Execute() = 0;
	virtual int Execute(const char* mysql) = 0;

	virtual IResultset* ExecuteQuery() = 0;
	virtual IResultset* ExecuteQuery(const char* sql) = 0;
};


#endif