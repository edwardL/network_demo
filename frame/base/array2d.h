#ifndef ARRAY_2D_H
#define ARRAY_2D_H

// 一个简易的二维数组
template<class T>
class Array2D
{
public:
	Array2D()
	{
		m_data = 0;
		m_row = 0;
		m_colomn = 0;
	}

	~Array2D()
	{
		delete [] m_data;
	}

	int GetSize(){ return m_row * m_colomn; }
	int GetRow() { return m_row; }
	int GetColomn() { return m_colomn; }

	T* GetData() { return m_data; }

	T* GetDataEnd() { return &m_data[m_row * m_colomn]; }
	void SetData(T* pData , int r, int c)
	{
		Allocate(r,c);
		memcpy(m_data,pData, c * r * sizeof(T));
	}

	void Allocate(int row, int c)
	{
		if(row == m_row && m_colomn == c)
		{
			memset(m_data,0,m_row * m_colomn);
			return;
		}
		if(m_data)
			delete [] m_data;
		m_row = row;
		m_colomn = c;
		m_data = new T [m_row * m_colomn];
		memset(m_data,0,m_colomn * m_row);
	}

	void Reset()
	{
		delete [] m_data;
		m_data = 0;
		m_row = 0;
		m_colomn = 0;
	}
	T Get(int row, int colomn)
	{
		return m_data[(row)* colomn + row];
	}
	T* operator[] (const int & nPos) const
	{
		return &m_data[nPos * m_colomn]
	}

	void operator = (const Array2D& other)
	{
		Allocate(other.m_row,other.m_colomn);
		memcpy(m_data,other.m_data,m_row * m_colomn * sizeof(T));
	}

public:
	T* m_data;
	int m_row;
	int m_colomn;
};

#endif
