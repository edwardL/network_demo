#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
template<typename T>
class Vector
{
public:
	Vector()
	{
		m_data = (T*)malloc(DEFAULT_CAPACITY * sizeof(T));
		m_max_size = DEFAULT_CAPACITY;
		m_size = 0;
	}

	T back()
	{
		if(m_size == 0) return 0;
		return m_data[m_size];
	}

	T front()
	{
		if(m_size == 0) return 0;
		return m_data[0];
	}

	void push_front(T val)
	{
		//push_back(val);
		// bug
		if(true)return;
		if(m_size >= m_max_size)
			resize();
		for(size_t i = m_size; i > 0; i--)
			m_data[i+1] = m_data[i];
		m_data[0] = val;
		m_size++;
	}

	void printf_list()
	{
		for(size_t i = 0; i < m_size; i++)
		{
			printf("%d	",m_data[i]);
		}
		printf("\n");
	}

	void push_back(T val)
	{
		if(m_size >= m_max_size)
			resize();
		m_data[m_size++] = val;
	}

	T pop_back()
	{
		T tmp = m_data[--m_size];
		return tmp;
	}


	size_t size()
	{
		return m_size;
	}


	void resize()
	{
		size_t old_size = m_max_size;
		m_max_size = m_max_size * 2;
		T* tmp = (T*)malloc( m_max_size * sizeof(T));
		memcpy(tmp,m_data, m_size * sizeof(T));
		free(m_data);
		m_data = tmp;	
	}

	void erase(int index)
	{
		if(index < 0 || index > m_size)
			return;
		for(size_t i = index; i < m_size; i++)
			m_data[i-1] = m_data[i];
		m_size--;	
	}

	T operator[] (int index)
	{
		if(index < 0 || index > m_size )
			return T();
		return m_data[index];
	}
private:
	T* m_data;
	size_t m_size;
	size_t m_max_size;
	static const int DEFAULT_CAPACITY = 10;
};


#endif