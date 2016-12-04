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

	// 获得语句实体对象指针,如MYSQL_STMT
	virtual void* GetStmt() = 0;
	// 返回预处理insert 或update 语句为auto_increment 列生成的值
	virtual long long GetInsertID() = 0;

	virtual bool Prepare(const char* sql) = 0;
	virtual void ClearParameters() = 0;
	virtual void Close() = 0;

	//写入一个字节，如mysql 的TINYINT
	virtual bool SetBype(int paramIndex, char value) = 0;
	// 写入N 个字节， 如mysql 的BLOB/TEXT

	// 写入一个布尔值
	virtual bool SetBoolean(int paramIndex, bool value) = 0;

	//写入一个32 位整形，例如mysql 中的INT
	virtual bool SetInt32(int paramIndex, int value) = 0;

	// 写入一个Double
	virtual bool SetDouble(int paramIndex, double value) =0;

	// 写入64 位数， 例如MYSQL 的big int
	virtual bool SetLong64(int paramIndex, long long value) = 0;

	// 写入字符串， 例如mysql 的varchar
	virtual bool SetString(int paramIndex, const char* value,unsigned long length) =0;

	// 写入日期+ 时间， 例如mysql 中的DATETIME
	virtual bool SetDate(int paramIndex, const tm& value) = 0;
	// 写入时间，例如mysql 中的TIME
	virtual bool SetTime(int param, const tm& value) = 0;
	virtual bool SetTimeStamp(int paramIndex, const tm& value);

	virtual int Execute() = 0;
	virtual int Execute(const char* mysql) = 0;

	virtual IResultset* ExecuteQuery() = 0;
	virtual IResultset* ExecuteQuery(const char* sql) = 0;
};


#endif