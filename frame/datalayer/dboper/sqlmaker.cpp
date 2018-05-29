#include "sqlmaker.h"
#include "dataadapter.h"
#include "../db/statement.h"

namespace sqlmaker
{
	std::string MakeUpdate(const MetaTableDef *table, const DataNodeList &data_node_list)
	{
		if(data_node_list.size() <= 0)
		{
			return "";
		}
		std::string sql = " set";
		for(DataNodeList::const_iterator iter = data_node_list.begin(); iter != data_node_list.end(); ++iter)
		{
			sql += " ";
			sql += table->m_meta_data[iter->GetColumn()].name;
			sql += " = ? , ";
		}
		sql.erase(sql.size() - 2, 2);

		return sql;
	}

	std::string MakeQuery(const MetaTableDef *table, const CmpNodeList &cmp_node_list)
	{
		if(cmp_node_list.size() <= 0)
		{
			return "";
		}
		std::string sql = " where";
		for (CmpNodeList::const_iterator it = cmp_node_list.begin(); it != cmp_node_list.end(); it++)
		{
			sql += " ";
			if(it->IsSet()) 
			{
				sql += table->m_meta_data[it->GetColumn()].name + " in ( ";
				if(it->GetDataType() == DATYPE_INT)
				{
					for(std::vector<int>::const_iterator iterint = it->GetIntSet().begin(); iterint != it->GetIntSet().end(); iterint++)
					{
						sql += std::to_string((long long)*iterint) + ",";
					}
				}
				else if(it->GetDataType() == DATYPE_LONG64)
				{
					for(std::vector<long long>::const_iterator iterlong = it->GetLong64Set().begin(); iterlong != it->GetLong64Set().end(); iterlong++)
					{
						sql += std::to_string(*iterlong) + ",";
					}
				}
				sql.erase(sql.length()-1,1);
				sql += ") and ";
				continue;
			}
			
			if(it->GetDataType() == DATYPE_STRING)
			{
				switch(it->GetLikeCmpType())
				{
				case CMP_LIKE_TYPE_L_LIKE:
					sql += table->m_meta_data[it->GetColumn()].name + " like '" + it->GetString() + "%' and ";
					continue;
					break;
				case CMP_LIKE_TYPE_R_LIKE:
					sql += table->m_meta_data[it->GetColumn()].name + " like '%" + it->GetString() + "' and ";
					continue;
					break;
				case CMP_LIKE_TYPE_LIKE:
					sql += table->m_meta_data[it->GetColumn()].name + " like '%" + it->GetString() + "%' and ";
					continue;
					break;
				case CMP_LIKE_TYPE_UNLIKE:
					break;
				case CMP_LIKE_TYPE_REGEXP:
					sql += table->m_meta_data[it->GetColumn()].name + " REGEXP '" + it->GetString() +"' and ";
					break;
				}
			}
			sql += table->m_meta_data[it->GetColumn()].name;

			EQUAL_TYPE equalType = it->GetEqualType();
			if(equalType & EQUAL_TYPE_LESS)
			{
				sql += "<? and ";
				continue;                                                                                                               
			}
			if(equalType & EQUAL_TYPE_GRANTER)
			{
				sql += ">? and ";
				continue;
			}
			if(equalType & EQUAL_TYPE_EQUAL)
			{
				sql += "=? and ";
				continue;
			}
			if(equalType & EQUAL_TYPE_LESS_EQUAL)
			{
				sql += "<=? and ";
				continue;
			}
			if(equalType & EQUAL_TYPE_GRANTER_EQUAL)
			{
				sql += ">=? and ";
				continue;
			}
			if(equalType & EQUAL_TYPE_NOT_EQUAL)
			{
				sql += "!=? and ";
				continue;
			}
		}
		sql.erase(sql.size() - 4 , 4);

		return sql;
	}

	std::string MakeOrder(const MetaTableDef *table, const QueryCondition &query)
	{
		std::string sql;
		if(query.order_list.size() > 0)
		{
			sql += " order by";
			for(OrderTypeList::const_iterator iter = query.order_list.begin(); iter != query.order_list.end(); ++iter)
			{
				sql += " " + table->m_meta_data[iter->column].name;
				switch(iter->type)
				{
				case ORDER_TYPE_ASC:
					sql += " asc,";
					break;
				case ORDER_TYPE_DESC:
					sql += " desc,";
					break;
				}
			}
			sql.erase(sql.size() - 1);
		}

		if(query.query_num != 0)
		{
			sql += " limit ";
			if(query.start_offset != 0)
			{
				sql += std::to_string((long long)query.start_offset) + ", ";
			}
			sql += std::to_string((long long)query.query_num);
		}
		return sql;
	}

	void WriteStmt(int index , const DataNode &dataNode, IStatement *stmt)
	{
		switch(dataNode.GetDataType())
		{
		case DATYPE_CHAR:
			stmt->SetByte(index,dataNode.GetBype());
			break;
		case DATYPE_INT:
			stmt->SetInt32(index,dataNode.GetInt32());
			break;
		case DATYPE_LONG64:
			stmt->SetLong64(index,dataNode.GetLong64());
			break;
		case DATYPE_DOUBLE:
			stmt->SetDouble(index, dataNode.GetDouble());
			break;
		case DATYPE_STRING:
			stmt->SetString(index,dataNode.GetString().c_str(),(unsigned long)dataNode.GetString().size());
			break;
		}
	}

	void WriteStmt(int startIndex, const CmpNodeList &cmp_node_list, IStatement *stmt)
	{
		for(CmpNodeList::const_iterator iter = cmp_node_list.begin(); iter != cmp_node_list.end(); iter ++)
		{
			if(iter->IsSet())
			{
				continue;
			}
			if(!(iter->GetDataType() == DATYPE_STRING && 
				(iter->GetLikeCmpType() == CMP_LIKE_TYPE_LIKE 
				|| iter->GetLikeCmpType() == CMP_LIKE_TYPE_L_LIKE
				|| iter->GetLikeCmpType() == CMP_LIKE_TYPE_R_LIKE
				|| iter->GetLikeCmpType() == CMP_LIKE_TYPE_REGEXP)))
			{
				WriteStmt( startIndex ++ , *iter , stmt);
			}
		}
	}

	void WriteStmt(int startIndex, const DataNodeList &data_node_list, IStatement *stmt)
	{
		for(DataNodeList::const_iterator iter = data_node_list.begin(); iter != data_node_list.end(); iter ++)
		{
			WriteStmt(startIndex ++ , *iter , stmt);
		}
	}
}