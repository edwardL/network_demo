#ifndef OBJ_MANAGER_H
#define OBJ_MANAGER_H

#include "../../file/raobjlist.h"

class Obj;

class ObjManager
{
	typedef RAObjList<Obj *> ObjList;
public:
	typedef ObjList::Iterator ObjIterator;
	ObjManager();
	~ObjManager();

	bool Add(Obj *obj);
	bool Remove(ObjID obj_id);
	Obj* GetObj(ObjID obj_id)
	{
		return m_objlist[obj_id];
	}

	bool Exist(ObjID obj_id)
	{
		return m_objlist.Exist(obj_id);
	}

protected:
	ObjList m_objlist;
};

#endif