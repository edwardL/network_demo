#ifndef SQLMAKER_H
#define SQLMAKER_H

#include "sqlnode.h"

class IStatement;

/*
	ʹ��ע�⣺
		�˴�ֻ��sqlƴ�ӣ�����' ` " �ȷ��ţ����ⲿ��֤����
*/

namespace sqlmaker
{
	std::string MakeUpdate(const MetaTableDef *table, const DataNodeList &data_node_list);
	std::string MakeQuery(const MetaTableDef *table, const CmpNodeList &cmp_node_list);
	std::string MakeOrder(const MetaTableDef *table, const QueryCondition &query);

	void WriteStmt(int index , const DataNode &dataNode, IStatement *stmt);
	void WriteStmt(int startIndex, const CmpNodeList & cmp_node_list, IStatement *stmt);
	void WriteStmt(int startIndex, const DataNodeList &data_node_list, IStatement *stmt);
}


#endif