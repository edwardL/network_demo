#include "../../../mysqlconnector/v32/include/my_global.h"
#include "../../../mysqlconnector/v32/include/mysql.h"

#include "mysqlresult.h"
#include "../statement.h"
#include "mysqldef.h"

MysqlResult::MysqlResult():m_fieldIndexInfo(0),m_metadata(0),m_fieldCount(0),m_result(0)
{
}

MysqlResult::~MysqlResult()
{
	Close();
}

IStatement* MysqlResult::GetStmt()
{
	return m_stmt;
}

void MysqlResult::SetStmt(IStatement* stmt)
{
	m_stmt = stmt;
}

bool MysqlResult::Init()
{
	if(0 == m_stmt)
	{
		return false;
	}
	m_metadata = mysql_stmt_result_metadata((MYSQL_STMT*)(m_stmt->GetStmt()));
	if(0 == m_metadata)
	{
		return false;
	}
	m_fieldCount = mysql_num_fields(m_metadata);
	if(m_fieldCount > 0)
	{
		m_result = new MYSQL_BIND[m_fieldCount];
		m_fieldIndexInfo = new TypeName[m_fieldCount];

		MYSQL_FIELD* fields = mysql_fetch_fields(m_metadata);
		for(unsigned int i = 0; i < m_fieldCount; ++i)
		{
			MYSQL_FIELD *field = &fields[i];
			static const unsigned long MAX_BLOB_LENGTH = 100 * 1024;
			if(field->length > MAX_BLOB_LENGTH)
			{
				field->length = MAX_BLOB_LENGTH;
			}
			MYSQL_BIND* bind = &m_result[i];
			memset(bind,0,sizeof(MYSQL_BIND));
			bind->buffer_type = field->type;
			bind->is_null = new char;
			bind->length = new unsigned long;

			DBDATATYPE type = (DBDATATYPE)getDataType((int)field->type);
			
			m_field_name_info[field->name].type = type;
			m_field_name_info[field->name].index = i;
			m_fieldIndexInfo[i].type = (int)type;
			m_fieldIndexInfo[i].name = field->name;

			switch(type)
			{
			case TYPE_INT:
				bind->buffer = malloc(sizeof(int));
				break;
			case TYPE_STRING:
				bind->buffer = malloc(field->length);
				*bind->length = field->length;
				bind->buffer_length = field->length;
				break;
			case TYPE_DATE:
				bind->buffer = malloc(sizeof(MYSQL_TIME));
				break;
			case TYPE_TIMESTAMP:
				bind->buffer = malloc(sizeof(MYSQL_TIME));
				break;
			case TYPE_TIME:
				bind->buffer = malloc(sizeof(MYSQL_TIME));
				break;
			case TYPE_LONG64:
				bind->buffer = malloc(sizeof(long long));
				break;
			case TYPE_DOUBLE:
				bind->buffer = malloc(sizeof(double));
				break;
			case TYPE_CHAR:
				bind->buffer = malloc(sizeof(char));
				break;
			default:
				break;
			}
		}
		mysql_stmt_bind_result( (MYSQL_STMT*)(m_stmt->GetStmt()), m_result );
	}
	return true;
}

void MysqlResult::Close()
{
	Clear();
	if(0 != m_stmt)
	{
		m_stmt->Close();
		m_stmt = 0;
	}
}

int MysqlResult::GetColumnCount()
{
	return m_fieldCount;
}

std::string MysqlResult::GetColumnName(int index)
{
	if(!ValidIndex(index))
	{
		return 0;
	}
	return m_fieldIndexInfo[index].name;
}

bool MysqlResult::GetColumnDataType(int index, int* type)
{
	if(!ValidIndex(index))
	{
		return 0;
	}
	*type = m_fieldIndexInfo[index].type;
	return true;
}

int MysqlResult::FindColumn(const char* columnName)
{
	std::map<std::string,IndexType>::iterator iter = m_field_name_info.find(columnName);
	if(iter == m_field_name_info.end())
	{
		return -1;
	}
	return (int)iter->second.index;
}

bool MysqlResult::Next(bool* isErr)
{
	*isErr = false;
	int ret = mysql_stmt_fetch((MYSQL_STMT*)(m_stmt)->GetStmt());
	if(0 == ret)
	{
		return true;
	}
	if(MYSQL_NO_DATA != ret)
	{
		*isErr = true;
	}
	return false;
}

bool MysqlResult::IsNull(int index, bool* isnull)
{
	if(!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	*isnull = (0 != *bind->is_null);
	return true;
}

bool MysqlResult::IsNull(const char* columnName, bool* isnull)
{
	int index = FindColumn(columnName);
	return IsNull(index,isnull);
}

bool MysqlResult::GetByte(int index, char* ret)
{
	if(!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	if(bind->buffer_type != MYSQL_TYPE_TINY)
	{
		return false;
	}
	*ret = *(char*)(bind->buffer);
	return true;
}

bool MysqlResult::GetByte(const char* columnName, char* ret)
{
	int index = FindColumn(columnName);
	return GetByte(index,ret);
}

bool MysqlResult::GetBoolean(int index, bool*ret)
{
	if(!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	if(bind->buffer_type != MYSQL_TYPE_TINY)
	{
		return false;
	}
	*ret = *(bool*)bind->buffer;
	return true;
}

bool MysqlResult::GetBoolean(const char* columnName, bool* ret)
{
	int index = FindColumn(columnName);
	return GetBoolean(index,ret);
}

bool MysqlResult::GetString(int index, char* ret, unsigned long* length)
{
	if(!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	if ( bind->buffer_type != MYSQL_TYPE_STRING 
		&& bind->buffer_type != MYSQL_TYPE_VAR_STRING 
		&& bind->buffer_type != MYSQL_TYPE_TINY_BLOB 
		&& bind->buffer_type != MYSQL_TYPE_MEDIUM_BLOB 
		&& bind->buffer_type != MYSQL_TYPE_LONG_BLOB 
		&& bind->buffer_type != MYSQL_TYPE_BLOB )
	{
		return false;
	}

	unsigned long size = *length;
	if(size > *bind->length)
	{
		size = *bind->length;
	}
	memcpy(ret,bind->buffer,size);
	*length = size;
	return true;
}

bool MysqlResult::GetString(const char* columnName, char* ret, unsigned long* length)
{
	int index = FindColumn(columnName);
	return GetString(index, ret, length);
}

bool MysqlResult::GetInt32(int index, int* ret)
{
	if(!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	if(bind->buffer_type != MYSQL_TYPE_LONG)
	{
		return false;
	}
	*ret = *(int*)(bind->buffer);
	return true;
}

bool MysqlResult::GetInt32(const char* columnName, int* ret)
{
	int index = FindColumn(columnName);
	return GetInt32(index, ret);
}

bool MysqlResult::GetDouble(int index, double* ret)
{
	if(!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	if(bind->buffer_type != MYSQL_TYPE_DOUBLE)
	{
		return false;
	}
	*ret = *(double*)(bind->buffer);
	return true;
}

bool MysqlResult::GetDouble(const char* columnName, double* ret)
{
	int index = FindColumn(columnName);
	return GetDouble(index, ret);
}


bool MysqlResult::GetDate(int index, tm* ret)
{
	if (!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	if(bind->buffer_type != MYSQL_TYPE_DATETIME)
	{
		return false;
	}
	ret->tm_year = (*(MYSQL_TIME*)bind->buffer).year;
	ret->tm_mon = (*(MYSQL_TIME*)bind->buffer).month;
	ret->tm_mday = (*(MYSQL_TIME*)bind->buffer).day;
	ret->tm_hour = (*(MYSQL_TIME*)bind->buffer).hour;
	ret->tm_min = (*(MYSQL_TIME*)bind->buffer).minute;
	ret->tm_sec = (*(MYSQL_TIME*)bind->buffer).second;
	return true;
}
bool MysqlResult::GetDate(const char* columnName, tm* ret)
{
	int index = FindColumn(columnName);
	return GetDate(index, ret);
}

bool MysqlResult::GetTime(int index, tm* ret)
{
	if (!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	if(bind->buffer_type != MYSQL_TYPE_TIME)
	{
		return false;
	}
	ret->tm_year = (*(MYSQL_TIME*)bind->buffer).year;
	ret->tm_mon = (*(MYSQL_TIME*)bind->buffer).month;
	ret->tm_mday = (*(MYSQL_TIME*)bind->buffer).day;
	ret->tm_hour = (*(MYSQL_TIME*)bind->buffer).hour;
	ret->tm_min = (*(MYSQL_TIME*)bind->buffer).minute;
	ret->tm_sec = (*(MYSQL_TIME*)bind->buffer).second;
	return true;
}
bool MysqlResult::GetTime(const char* columnName, tm* ret)
{
	int index = FindColumn(columnName);
	return GetTime(index, ret);
}

bool MysqlResult::GetTimestamp(int index, tm* ret)
{
	if (!ValidIndex(index))
	{
		return false;
	}
	MYSQL_BIND* bind = &m_result[index];
	if(bind->buffer_type != MYSQL_TYPE_TIMESTAMP)
	{
		return false;
	}
	ret->tm_year = (*(MYSQL_TIME*)bind->buffer).year;
	ret->tm_mon = (*(MYSQL_TIME*)bind->buffer).month;
	ret->tm_mday = (*(MYSQL_TIME*)bind->buffer).day;
	ret->tm_hour = (*(MYSQL_TIME*)bind->buffer).hour;
	ret->tm_min = (*(MYSQL_TIME*)bind->buffer).minute;
	ret->tm_sec = (*(MYSQL_TIME*)bind->buffer).second;
	return true;
}
bool MysqlResult::GetTimestamp(const char* columnName, tm* ret)
{
	int index = FindColumn(columnName);
	return GetTimestamp(index, ret);
}

bool MysqlResult::GetLong64(int index, long long* ret)
{
	if (!ValidIndex(index))
	{
		return false;
	}

	MYSQL_BIND* bind = &m_result[index];
	if(bind->buffer_type != MYSQL_TYPE_LONGLONG)
	{
		return false;
	}

	*ret = *(long long*)(bind->buffer);
	return true;
}
bool MysqlResult::GetLong64(const char* columnName, long long* ret)
{
	int index = FindColumn(columnName);
	return GetLong64(index, ret);
}

bool MysqlResult::ValidIndex(int index)
{
	if(index < 0 || (unsigned int)index > m_fieldCount)
	{
		return false;
	}
	return true;
}

void MysqlResult::CleanParam(MYSQL_BIND* bind)
{
	if(0 != bind->is_null)
	{
		delete bind->is_null;
		bind->is_null = 0;
	}
	if(0 != bind->length)
	{
		delete bind->length;
		bind->length = 0;
	}
	if(0 != bind->buffer)
	{
		free(bind->buffer);
		bind->buffer = 0;
	}
}

void MysqlResult::Clear()
{
	if(0 != m_metadata)
	{
		mysql_free_result(m_metadata);
		m_metadata = 0;
	}
	if(0 != m_fieldCount)
	{
		delete[] m_fieldIndexInfo;
		m_fieldIndexInfo = 0;
	}
	m_field_name_info.clear();
	if(0 != m_result)
	{
		for(unsigned int i = 0; i < m_fieldCount; ++i)
		{
			CleanParam(&m_result[i]);
		}
		delete[] m_result;
		m_result = 0;
	}
}