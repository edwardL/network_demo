/*
#ifndef DATAADAPTER_H
#define DATAADAPTER_H

#include <string>
#include <vector>

#pragma pack(push)
#pragma pack(4)

/*
	ʹ��ע�⣺
	1��MataTableDef����ȷ����ʹ���߱�֤��
	2��MataTableDef::m_id_index ����Ϊlong long �����������ݿ���Ҳ����Ϊ��Ӧ����
	3��DataArea ����� һ�� MataTableDef ��Ӧ

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

class MetaTableDef; // ����

// ����list
class DataAdapter
{
protected:
	DataAdapter();
	void Init(const MetaTableDef *table);

public:
	DataAdapter(const DataAdapter &_r);
	~DataAdapter();

	// Ϊ��Ҫ�����ռ���ֶδ����ռ�,��Ҫ���ڴ����ݿ��ж�ȡ
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
	MallocAreaList m_malloc_area_list; // ��¼��Ҫ��������ռ���ֶ�
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