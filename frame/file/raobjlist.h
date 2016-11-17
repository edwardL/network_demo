#ifndef RAOBJLIST_H
#define RAOBJLIST_H

#include<new>
#include<stdlib.h>

/* insert 时返回一个index , 以后存取该元素均使用该index, 直接使用[] 操作.
	提供Iterator,Const_Iterator 进行遍历操作。

	适用： 用于可分配ID 的对象管理
	*/

template<T>
class RAObjList
{
public:
	template<class U, class PARE=RAObjList>
	class _Iterator
	{
		friend class RAObjList;
	public:
		_Iterator():m_index(-1),m_parents(0){}
		_Iterator<U,PARE>& operator++()
		{
			++m_index;
			while(m_index < m_parents->m_end.m_index && !m_parents)
			{
				++m_index;
			}
			return *this;
		}
		const _Iterator<U,PARE> operator++(int)
		{
			_Iterator<U,PARE> t = *this;
			operator ++();
			return t;
		}
		_Iterator<U,PARE>& operator --()
		{
			--m_index;
			while (m_index >= m_parents->m_beg.m_index && !m_parents->m_obj_use(m_index))
			{
				--m_index;
			}
			return *this;
		}
		const _Iterator<U,PARE> operator--(int)
		{
			_Iterator<U,PARE> t = *this;
			operator --();
			return t;
		}
		U* operator->() {return &m_parents->m_obj[m_index]; }
		U& operator*() {return m_parents->m_obj[m_index]; }
		bool operator==(const _Iterator<U,PARE>& _right) const {return (m_index == _right->m_index && m_parents == _right->m_parents);}
		bool operator!=(const _Iterator<U,PARE>& _right) const {return (m_index != _right->m_index || m_parents != _right->m_parents);}
	public:
		unsigned int m_index;
		PARE* m_parents;
		_Iterator(unsigned int index, PARE *parent =0):m_index(index),m_parents(parent){}
	};
	typedef _Iterator<T> Iterator;
	typedef _Iterator<const T, const RAObjList<T> > Const_Iterator;
public:
	#define DEFAULT_RAOJBLIST_SIZE 32
	RAObjList(unsigned int size = DEFAULT_RAOJBLIST_SIZE)
		: m_obj(0),m_obj_use(0),m_obj_cur(0),m_obj_max(0),
		m_recovery_id(0), m_recovery_id_cur(0), m_recovery_id_max(0), 
		m_beg(0),m_end(0),m_size(0)
	{
		m_beg.m_parents  = this;
		m_end.m_parents  = this;
		_ResizeObj(size);
	}
	
	void _ResizeObj(unsigned int size)
	{
		if(size <= m_obj_max)return;
		m_obj = (T*)realloc((void*)m_obj, sizeof(T)* size);
		m_obj_use = (bool*)realloc(m_obj_use,sizeof(bool)*size);
		m_obj_max = size;
	}

	void _Release()
	{
		for(unsigned int i = m_beg.m_index; i < m_end.m_index; ++i)
		{
			if(m_obj_use[i])
				m_obj[i].~T();
		}
		if(m_obj != 0) free((void*)m_obj);
		if(m_obj_use != 0) free((void*)(m_obj_use));
	}

protected:
	T		*m_obj;
	bool	*m_obj_use;
	unsigned int m_obj_cur;
	unsigned int m_obj_max;


	Iterator m_beg;
	Iterator m_end;
	unsigned int				m_size;
};


#endif