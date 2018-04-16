#pragma once

#ifndef TLVPROTOCAL_H
#define TLVPROTOCAL_H

/*
	TLV Protocol (Type-Length-Value Э��)

	���ļ���Ŀ�����ṩһ�����õ� �����ֽڵ�Э�鹹�켰�������ܡ�
	ʹ��TLV�ı��뷽�����ṩ�������͵����л��ͷ����л�������Ƕ���Ա�֤��������걸��

	TLVSerializer		���л���
	TLVUnserializer		�����л��࣬�ַ����ķ����л���δ�������ƣ��û������н����ݸ���

	Serialize			����format�ַ����������л�
	Unserialize			����format�ַ������з����л�

	TLVTypeTraits		�������ԡ���ʹ�ø����ӵļ��ɣ����Լ��ٴ����ظ�����������������������ѣ��ݻ���

	ʾ�������testtlvprotocol.cpp
*/

#include <string.h>
#include<stdarg.h>

namespace TLVType
{
	enum
	{
		NULL_TYPE,
		INT8,
		INT16,
		INT32,
		INT64,
		FLOAT32,
		FLOAT64,
		STRING,
		SEQUENCE,
	};
}

typedef char TLVType_t;
typedef unsigned int TLVLength_t;

enum
{
	FixLength,
	DynLength,
};

class TLVSerializer;
class TLVUnserializer;

struct TLVNull;

template<class T>
struct TLVTypeTraits;

template<>
struct TLVTypeTraits<TLVNull>
{
	enum
	{
		TypeId = TLVType::NULL_TYPE,
		LengthType = FixLength,
	};
	
	static unsigned int Length(const TLVNull &)
	{
		return 0;
	}
	static const void* Ptr(const TLVNull& v)
	{
		return 0;
	}
	static bool Set(TLVNull* s,const void* data, unsigned int length)
	{
		return true;
	}
};

template<>
struct TLVTypeTraits<float>
{
	enum
	{
		TypeId = TLVType::FLOAT32,
		LengthType = FixLength,
	};

	static unsigned int Length(float)
	{
		return sizeof(float);
	}
	static const void* Ptr(const float& v)
	{
		return &v;
	}
	static bool Set(float* s, const void* data, unsigned int length)
	{
		*s = *(float*)data;
		return true;
	}
};

template<>
struct TLVTypeTraits<bool>
{
	enum
	{
		TypeId = TLVType::INT8,
		LengthType = FixLength,
	};

	static unsigned int Length(bool)
	{
		return sizeof(bool);
	}
	static const void* Ptr(const bool& v)
	{
		return &v;
	}
	static bool Set(bool* s,const void* data, unsigned int length)
	{
		*s = *(bool*)data;
		return true;
	}
};

template<>
struct TLVTypeTraits<unsigned char>
{
	enum
	{
		TypeId = TLVType::INT8,
		LengthType = FixLength,
	};

	static unsigned int Length(unsigned char)
	{
		return sizeof(unsigned char);
	}
	static const void* Ptr(const unsigned char& v)
	{
		return &v;
	}
	static bool Set(unsigned char* s,const void* data, unsigned int length)
	{
		*s = *(unsigned char*)data;
		return true;
	}
};

template<>
struct TLVTypeTraits<signed char>
{
	enum
	{
		TypeId = TLVType::INT8,
		LengthType = FixLength,
	};

	static unsigned int Length(signed char)
	{
		return sizeof(signed char);
	}
	static const void* Ptr(const signed char& v)
	{
		return &v;
	}
	static bool Set(signed char* s,const void* data, unsigned int length)
	{
		*s = *(signed char*)data;
		return true;
	}
};

template<>
struct TLVTypeTraits<char>
{
	enum
	{
		TypeId = TLVType::INT8,
		LengthType = FixLength,
	};

	static unsigned int Length(char)
	{
		return sizeof(char);
	}
	static const void* Ptr(const char& v)
	{
		return &v;
	}
	static bool Set(char* s,const void* data, unsigned int length)
	{
		*s = *(char*)data;
		return true;
	}
};

template<>
struct TLVTypeTraits<short>
{
	enum
	{
		TypeId = TLVType::INT16,
		LengthType = FixLength,
	};

	static unsigned int Length(short)
	{
		return sizeof(short);
	}
	static const void* Ptr(const short& v)
	{
		return &v;
	}
	static bool Set(short* s,const void* data, unsigned int length)
	{
		*s = *(short*)data;
		return true;
	}
};

template<>
struct TLVTypeTraits<unsigned short>
{
	enum
	{
		TypeId = TLVType::INT16,
		LengthType = FixLength,
	};

	static unsigned int Length(unsigned short)
	{
		return sizeof(unsigned short);
	}
	static const void* Ptr(const unsigned short& v)
	{
		return &v;
	}
	static bool Set(unsigned short* s,const void* data, unsigned int length)
	{
		*s = *(unsigned short*)data;
		return true;
	}
};


template<>
struct TLVTypeTraits<int>
{
	enum
	{
		TypeId = TLVType::INT32,
		LengthType = FixLength,
	};

	static unsigned int Length(int)
	{
		return sizeof(int);
	}
	static const void* Ptr(const int& v)
	{
		return &v;
	}
	static bool Set(int* s,const void* data, unsigned int length)
	{
		*s = *(int*)data;
		return true;
	}
};

template<>
struct TLVTypeTraits<unsigned int>
{
	enum
	{
		TypeId = TLVType::INT32,
		LengthType = FixLength,
	};

	static unsigned int Length(unsigned int)
	{
		return sizeof(unsigned int);
	}
	static const void* Ptr(const unsigned int& v)
	{
		return &v;
	}
	static bool Set(unsigned int* s,const void* data, unsigned int length)
	{
		*s = *(unsigned int*)data;
		return true;
	}
};

/*
* ���л���ͷ����л���
* TLVSerializer  TLVUnserializer
*/

class TLVSerializer
{
public:
	TLVSerializer()
		:m_buffer(0),m_max_size(0),m_size(0)
	{

	}

	void Reset(void* buffer,unsigned int length)
	{
		m_buffer = (char*)buffer;
		m_max_size = length;
		m_size = 0;
	}
	void Reset()
	{
		m_size = 0;
	}

	template<class T>
	bool Push(const T& value)
	{
		const void *ptr = TLVTypeTraits<T>::Ptr(value);
		bool ret = Push(TLVTypeTraits<T>::TypeId,(int)TLVTypeTraits<T>::LengthType == (int)FixLength,
			TLVTypeTraits<T>::Length(value),ptr);
		return ret;
	}
	bool Push(TLVType_t type, bool fixLength, TLVLength_t length,const void* value)
	{
		unsigned int total;
		fixLength ? (total = sizeof(TLVType_t) + length) : (total = sizeof(TLVType_t) + sizeof(TLVLength_t) + length);
		if (m_size + total > m_max_size)
		{
			return false;
		}
		char* current = m_buffer + m_size;
		// Type
		*(TLVType_t*)(current) = type;
		current += sizeof(TLVType_t);

		/// Length
		if(!fixLength)
		{
			/// �Ƕ������Ͳ���Ҫд����
			*(TLVLength_t*)(current) = length;
			current += sizeof(TLVLength_t);
		}
		//Value
		memcpy(current,value,length);
		current += length;
		m_size = (unsigned int)(current - m_buffer);
		
		return true;
	}



	const void* Ptr()const
	{
		return (void*)m_buffer;
	}

	const unsigned int Size() const
	{
		return m_size;
	}

	void MoveCurPos(unsigned int offset)
	{
		m_size += offset;
	}

	void Clear()
	{
		m_size = 0;
		m_buffer = 0;
		m_max_size = 0;
	}

private:
	char* m_buffer;
	unsigned int m_max_size;
	unsigned int m_size;
};

class TLVUnserializer
{
public:
	TLVUnserializer()
		:m_data(0),m_size(0),m_current_ptr(0)
	{

	}

	void Reset(const void* data,unsigned int length)
	{
		m_data = (const char*)data;
		m_size = length;
		m_current_ptr = m_data;
	}

	void Reset()
	{
		m_current_ptr = m_data;
	}

	template<class T>
	bool Pop(T* value)
	{
		if(*(TLVType_t*)m_current_ptr == TLVTypeTraits<T>::TypeId)
		{
			TLVLength_t length;
			m_current_ptr += sizeof(TLVType_t);
			if((int)TLVTypeTraits<T>::LengthType == (int)FixLength)
			{
				length = TLVTypeTraits<T>::Length(*value);
			}
			else
			{
				length = *(TLVLength_t*)m_current_ptr;
				m_current_ptr += sizeof(TLVLength_t);
			}
			if(TLVTypeTraits<T>::Set(value,m_current_ptr,length))
			{
				m_current_ptr += length;
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	unsigned int Size()const
	{
		return m_size;
	}
	
	const void* Ptr() const
	{
		return m_data;
	}
private:
	const char* m_data;
	unsigned int m_size;
	const char* m_current_ptr;
};

#endif

