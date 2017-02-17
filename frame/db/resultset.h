#ifndef IRESULTSET_H
#define IRESULTSET_H

#include <time.h>
#include <string>
#include "dbdef.h"

class IStatement;

class IResultset
{
public:
	IResultset(){};
	virtual ~IResultset(){};

	virtual IStatement* GetStmt() = 0;
	virtual void SetStmt(IStatement* stmt) = 0;

	virtual bool Init() = 0;
	virtual void Close() = 0;

	virtual int GetColumnCount() = 0;
	virtual std::string GetColumnName(int index) = 0;
	virtual bool GetColumnDataType(int index, int* type) = 0;

	virtual int FindColumn(const char* columnName) = 0;

	// 获取下一行数据，返回获取失败时， 若isErr为false则读取完成，若为true则发生异常
	virtual bool Next(bool* isErr) = 0;

	virtual bool IsNull(int index, bool* isnull) = 0;
	virtual bool IsNull(const char* columnName, bool* isnull) = 0;

	virtual  bool GetByte(int index, char* ret)  = 0;
	virtual bool  GetByte(const char* columnName, char* ret) = 0;

	virtual bool GetBoolean(int index, bool* ret) = 0;
	virtual bool GetBoolean(const char* columnName, bool* ret) = 0;

	virtual bool GetString(int index, char* ret, unsigned long* length) = 0;
	virtual bool GetString(const char* ColumnName, char* ret, unsigned long* length) = 0;

	virtual bool GetInt32(int index,int* ret) = 0;
	virtual bool GetInt32(const char* column, int* ret) = 0;

	virtual bool GetDouble(int index, double* ret) = 0;
	virtual bool GetDouble(const char* column, double* ret) = 0;

	virtual bool GetDate(int index, tm* ret) = 0;
	virtual bool GetDate(const char* column, tm* ret);

	virtual bool GetTime(int index, tm* ret) = 0;
	virtual bool GetTime(const char* column, tm* ret) = 0;

	virtual bool GetTimestamp(int index, tm* ret) = 0;
	virtual bool GetTimestamp(const char* column, tm* ret) = 0;

	virtual bool GetLong64(int index, long long* ret) = 0;
	virtual bool GetLong64(const char* column, long long* ret) = 0;

protected:
	IStatement* m_stmt;
};

#endif