#ifndef OBJ_H
#define OBJ_H
#include "../../base/gamedef.h"

class Scene;

class Obj
{
public:
	enum _ObjType
	{
		OBJ_TYPE_INVALID,
		OBJ_TYPE_ROLE,
		OBJ_TYPE_MONSTER,
		OBJ_TYPE_PET,
		OBJ_TYPE_TRUCK,
		OBJ_TYPE_FALLINGITEM,
		OBJ_TYPE_GATHER,
		OBJ_TYPE_GODCITYGIFT,
		OBJ_TYPE_SENTRY,
		OBJ_TYPE_COUNT,
	};

	Obj(ObjType type);
	Obj(ObjType type, ObjID obj_id, const GameName _name);
	virtual	~Obj();

	void		SetId(ObjID gid) { m_obj_id = gid; }
	ObjID		GetId() { return m_obj_id; }
	ObjType		GetObjType() { return m_obj_type; }
	UInt32		GetSingleMgrIndex() { return m_single_mgr_index; }
	void		SetSingleMgrIndex(UInt32 index) { m_single_mgr_index = index; }
	virtual void SetPos(const Posi &pos) { m_posi = pos; }
	const Posi&	GetPos() const{ return m_posi; }
	void		GetName(GameName name);
	const char* GetName() { return m_name; }
	void		SetName(GameName name);
	void		SetScene(Scene *scene) { m_scene = scene; }
	Scene*		GetScene() { return m_scene; }

	virtual void OnEnterScene();
	virtual void OnLeaveScene();

	virtual void OnAOIEnter(ObjID obj_id){};
	virtual void OnAOILeave(ObjID obj_id){};

	virtual void Update(unsigned long interval, time_t now_second){}

	virtual bool IsCharactor(){ return false; }

	virtual bool CanBeAttack(){ return false; }

	void SetHasDelete(bool has_delete) { m_has_delete = has_delete; }
	bool HasDelete()const { return m_has_delete; }
protected:
	UInt32		m_single_mgr_index;
	bool		m_has_delete;

	const ObjType	m_obj_type;
	ObjID		m_obj_id;

	GameName	m_name;					// 名称
	Scene		*m_scene;				// 所在场景的id
	Posi		m_posi;					// 目前的位置，用于逻辑计算
	UInt32		m_obser_handle;
};

#endif