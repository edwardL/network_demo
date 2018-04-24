#ifndef MYSQLRESULT_H
#define MYSQLRESULT_H

#include "../resultset.h"
#include <map>

class IStatement;
struct st_mysql_bind;
typedef st_mysql_bind MYSQL_BIND;

struct st_mysql_res;
typedef st_mysql_res MYSQL_RES;

class MysqlResult : public IResultset
{
public:
	MysqlResult();
	virtual ~MysqlResult();

	IStatement* GetStmt();
	void SetStmt(IStatement* stmt);

	virtual bool Init();
	virtual void Close();

	virtual int GetColumnCount();
	virtual std::string GetColumnName(int index);
	virtual bool GetColumnDataType(int index, int* type);

	virtual int FindColumn(const char* columnName);
	virtual bool Next(bool* isErr);

	virtual bool IsNull(int index, bool* isnull);
	virtual bool IsNull(const char* columnName, bool* isnull);

	virtual bool GetByte(int index, char* ret);
	virtual bool GetByte(const char* columnName, char* ret);

	virtual bool GetBoolean(int index, bool*ret);
	virtual bool GetBoolean(const char* columnName, bool* ret);

	virtual bool GetString(int index, char* ret, unsigned long* length);
	virtual bool GetString(const char* columnName, char* ret, unsigned long* length);

	virtual bool GetInt32(int index, int* ret);
	virtual bool GetInt32(const char* columnName, int* ret);

	virtual bool GetDouble(int index, double* ret);
	virtual bool GetDouble(const char* column, double* ret);

	virtual bool GetDate(int index, tm* ret);
	virtual bool GetDate(const char* column, tm* ret);

	virtual bool GetTime(int index, tm* ret);
	virtual bool GetTime(const char* column, tm* ret);

	virtual bool GetTimestamp(int index, tm* ret);
	virtual bool GetTimestamp(const char* column, tm* ret);

	virtual bool GetLong64(int index, long long* ret);
	virtual bool GetLong64(const char* column,long long* ret);

	struct IndexType
	{
		unsigned int index;
		int type;
	};
	struct TypeName
	{
		int type;
		std::string name;
	};

protected:
	bool ValidIndex(int index);
	void CleanParam(MYSQL_BIND* bind);
	void Clear();

private:
	std::map<std::string, IndexType> m_field_name_info;
	TypeName*			m_fieldIndexInfo;
	MYSQL_RES*			m_metadata;
	unsigned int		m_fieldCount;
	MYSQL_BIND*			m_result;
};

#endif