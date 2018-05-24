#include "dataadapter.h"

char* DataArea::GetString(unsigned int *len)
{
	if(len != 0)*len = length;
	return vcharp;
}

void DataArea::SetString(const char *v)
{
	size_t len = strlen(v);
	len >= length ? (len = length - 1) : 0; // 对datalayer之外的接口，不允许设置到length
	memcpy(vcharp , v , len);
	vcharp[len] = 0;
	length = (unsigned int)len;
}

void DataArea::SetString(const char *v, unsigned int vlen)
{
	vlen >= length ? (vlen = length -1) : 0;
	memcpy(vcharp , v, vlen);
	vcharp[vlen] = 0;
	length = vlen;
}

void DataArea::Malloc(unsigned int len)
{
	unsigned int malloc_length = len + 1;
	vcharp = (char*)malloc(malloc_length);
	memset(vcharp, 0 , malloc_length);
	length = len;
}

void DataArea::Free()
{
	free(vcharp);
}

MetaTableDef::MetaTableDef():m_table_id(-1), m_key_id_index(-1)
{
}
MetaTableDef::~MetaTableDef()
{
}

bool MetaTableDef::Init(const TableInitArg &arg)
{
	m_table_id = arg.table_id;
	m_table_name = arg.table_name;
	m_key_id_index = arg.key_id_index;
	m_meta_data = arg.meta_data;

	for (int i = 0; i < (int)m_meta_data.size(); ++i)
	{
		if(m_meta_data[i].type == DATYPE_STRING)
		{
			m_malloc_area_list.push_back(i);
		}
	}
	m_data_prototype.Init(this);
	return true;
}

DataAdapter::DataAdapter()
{
}

DataAdapter::DataAdapter(const DataAdapter &_r)
	:m_data_area(_r.m_data_area), m_table(_r.m_table)
{

}

DataAdapter::~DataAdapter()
{
}

void DataAdapter::Malloc()
{
	for (int i = 0; i < (int)m_table->m_malloc_area_list.size(); ++i)
	{
		int index = m_table->m_malloc_area_list[i];
		m_data_area[index].Malloc(m_table->m_meta_data[index].length);
	}
}

void DataAdapter::Free()
{
	for(int i = 0; i < (int)m_table->m_malloc_area_list.size(); ++i)
	{
		m_data_area[m_table->m_malloc_area_list[i]].Free();
	}
}

void DataAdapter::Init(const MetaTableDef *table)
{
	m_table = table;
	m_data_area.resize(m_table->m_meta_data.size());
	for (int i = 0; i < (int)m_table->m_meta_data.size(); ++i)
	{
		m_data_area[i].length = m_table->m_meta_data[i].length;
		m_data_area[i].vint64 = 0;
	}
}