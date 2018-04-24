#include "../../../mysqlconnector/v32/include/my_global.h"
#include "../../../mysqlconnector/v32/include/mysql.h"

#include "mysqldef.h"

int getDataType(int nDataType)
{
	switch(nDataType)
	{
	case MYSQL_TYPE_TINY:
		return TYPE_CHAR;
	case MYSQL_TYPE_VAR_STRING:
	case MYSQL_TYPE_STRING:
	case MYSQL_TYPE_TINY_BLOB:
	case MYSQL_TYPE_MEDIUM_BLOB:
	case MYSQL_TYPE_LONG_BLOB:
	case MYSQL_TYPE_BLOB:
		return TYPE_STRING;
	case MYSQL_TYPE_LONG:
		return TYPE_INT;
	case MYSQL_TYPE_LONGLONG:
		return TYPE_LONG64;
	case MYSQL_TYPE_DOUBLE:
	case MYSQL_TYPE_FLOAT:
		return TYPE_DOUBLE;
	case MYSQL_TYPE_DATE:
	case MYSQL_TYPE_DATETIME:
		return TYPE_DATE;
	case MYSQL_TYPE_TIME:
		return TYPE_TIME;
	case MYSQL_TYPE_TIMESTAMP:
		return TYPE_TIMESTAMP;
	default:
		return -1;
	}
}
