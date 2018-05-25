/*
#ifndef DATAADAPTER_H
#define DATAADAPTER_H

#include <string>
#include <vector>

#pragma pack(push)
#pragma pack(4)

/*
	使用注意：
	1、MataTableDef的正确性由使用者保证！
	2、MataTableDef::m_id_index 必须为long long 并自增，数据库中也必须为相应类型
	3、DataArea 必须和 一个 MataTableDef 对应

 enum
 {
	 DATYPE_CHAR,
	 DATYPE_INT,
	 DATYPE_LONG64,
	 DATYPE_DOUBLE,
	 DATYPE_STRING,
	 DATYPE_TIME,
 };

 struct DataArea
 {
	 unsigned int length;
	 union {
		 char vchar;
		 int  vint;
		 long long vint64;
		 double vdouble;
		 char *vcharp;
		 long long vtime;
	 };

	 char GetByte()	{return vchar;}
	 int  GetInt32() {return vint;}
	 long long GetInt64() {return vint64;}
	 double GetDouble() {return vdouble;}
	 char *GetString(unsigned int* len = 0);
	 long long GetTime() {return vtime;}

	 void SetByte(char v) {vchar = v;}
	 void SetInt32(int v) {vint = v;}
	 void SetInt64(long long v) {vint64 = v;}
	 void SetDouble(double v) {vdouble = v;}
	 void SetTime(long long v) { vtime = v; }
	 void SetString(const char *v);
	 void SetString(const char *v, unsigned int vlen);

	 void Malloc(unsigned int len);
	 void Free();

	 unsigned int GetLength() {return length;}
 };

#pragma pack(pop)

class MetaTableDef; // 表定义

// 数据list
class DataAdapter
{
protected:
	DataAdapter();
	void Init(const MetaTableDef *table);

public:
	DataAdapter(const DataAdapter &_r);
	~DataAdapter();

	// 为需要独立空间的字段创建空间,主要用于从数据库中读取
	void Malloc();
	void Free();

	typedef std::vector<DataArea> DataAreaList;
	DataAreaList	m_data_area;
	const MetaTableDef * m_table;
};

typedef std::vector<DataAdapter> DataAdapterList;

struct TableInitArg;

class MetaTableDef
{
public:
	struct MetaData
	{
		int			type;
		std::string name;
		unsigned int length;
	};

	MetaTableDef();
	~MetaTableDef();

	bool Init(const TableInitArg &arg);
	const DataAdapter& GetPrototype() const {return m_data_prototype;}

	typedef std::vector<MetaData> MetaDataList;
	int		m_table_id;
	std::string m_table_name;
	MetaDataList m_meta_data;
	int			m_key_id_index;
	DataAdapter m_data_prototype;

	typedef std::vector<int> MallocAreaList;
	MallocAreaList m_malloc_area_list; // 记录需要分配独立空间的字段
};

struct TableInitArg
{
	int		table_id;
	std::string table_name;
	MetaTableDef::MetaDataList meta_data;
	int		key_id_index;
};

#endif

*/