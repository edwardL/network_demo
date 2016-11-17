#ifndef SINGLEMANAGER_H
#define SINGLEMANAGER_H

#define Obj int

class Scene;


class SingleManager
{
public:
	SingleManager();
	virtual ~SingleManager();

	void Init();
	void Release();

	bool Add(Obj *obj);
	bool Remove(Obj *obj);

	unsigned int Size() const {return m_size;}
	
	void SetScene(Scene* scene) {m_scene = scene;}
	Scene* GetScene() {return m_scene; }

	Obj *GetObjByIndex(unsigned int index)
	{
		if(index < m_size)
		{
			return m_obj[index];
		}
		else
		{
			return 0;
		}
	}

private:
	void Resize(unsigned int size);

protected:
	Obj	** m_obj;
	unsigned int m_size;
	unsigned int m_max_size;
	Scene	*m_scene;
};


#endif