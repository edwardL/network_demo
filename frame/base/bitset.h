#ifndef BITSET_H
#define BITSET_H
#include <string>
#include <sstream>
class Bitset
{
public:
	Bitset(){}
	 Bitset(int n)
	{
		maxn = n;
		m_data = 0;
	}
	// b 中是否存在值为1的二进制位
	bool any()
	{
		unsigned long tmp = m_data;
		for(int i = 0; i <= maxn; i++)
		{
			if(tmp % 2 != 0 ) return true;
			if(tmp != 0) tmp = tmp >> 1;
		}
		return false;
	}

	bool test(int pos)
	{
		unsigned int tmp = m_data >> pos;
		return (tmp % 2) == 1;
	}

	void set(int pos)
	{
		unsigned long tmp = 1 << pos;
		m_data = m_data | tmp;
	}

	int size()
	{
		return maxn;
	}

	std::string toString()
	{
		for(int i = 0; i < maxn; i++)
		{

		}
		return "";
	//	return stream.str();
		
	}

private:
	int maxn;
	unsigned long m_data;
};

#endif