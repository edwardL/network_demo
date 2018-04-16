#include "obj.h"
#include "../../base/commonfunc.h"

Obj::Obj(ObjType type):
m_single_mgr_index(-1),
	m_has_delete(false),
	m_obj_type(type),
	m_obj_id(INVALID_OBJ_ID),
	m_scene(0),
	m_posi(0,0),
	m_obser_handle(-1)
{
	m_name[0] = 0;
}

Obj::Obj(ObjType type, ObjID obj_id, const GameName _name):
m_single_mgr_index(-1),
	m_has_delete(false),
	m_obj_type(type),
	m_obj_id(obj_id),
	m_scene(0),
	m_posi(0,0),
	m_obser_handle(-1)
{
	ZTStrCpy(m_name, _name, sizeof(GameName));
}

Obj::~Obj()
{

}

void Obj::GetName(GameName name)
{
	ZTStrCpy(name, m_name, sizeof(GameName));
}

void Obj::SetName(GameName name)
{
	ZTStrCpy(m_name, name, sizeof(GameName));
}

void Obj::OnEnterScene()
{
	//m_obser_handle = m_scene->GetZoneMatrix()->CreateObser(m_obj_id);
}

void Obj::OnLeaveScene()
{
	//m_scene->GetZoneMatrix()->DestroyObser(m_obser_handle);
}