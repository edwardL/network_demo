/*
* MMORPG Server
* Copyright (C) 
*
*/

#ifndef _STRINGBUFFER_H
#define _STRINGBUFFER_H

#include<string>

#define STR_NUM 32

class StringBuffer
{
public:
	const static size_t DEFAULT_SIZE = 1024;

	StringBuffer()
	{
		_str.reserve(DEFAULT_SIZE);
	}
	StringBuffer(size_t res)
	{
		_str.reserve(res);
	}
	StringBuffer(const StringBuffer& buf): _str(buf._str) {}
	virtual ~StringBuffer(){}

	void clear()
	{
		_str.clear();
	}

	// unsigned 
	StringBuffer& operator<<(unsigned char value)
	{
		char* current = uintToString(value);
		_str += current;
		return *this;
	}

	StringBuffer& operator<<(unsigned short value)
	{
		char* current = uintToString(value);
		_str += current;
		return *this;
	}
	StringBuffer& operator<<(unsigned int value)
	{
		char* current = uintToString(value);
		_str += current;
		return *this;
	}
	StringBuffer& operator<<(unsigned long long value)
	{
		char* current = uint64ToString(value);
		_str += current;
		return *this;
	}

		StringBuffer & operator<<(signed char value)
		{
			char* current = intToString(value);
			_str += current;
			return *this;
		}
		StringBuffer & operator<<(signed short value)
		{
			char* current = intToString(value);
			_str += current;
			return *this;
		}
		StringBuffer & operator<<(signed int value)
		{
			char* current = intToString(value);
			_str += current;
			return *this;
		}
		StringBuffer & operator<<(signed long long value)
		{
			char* current = int64ToString(value);
			_str += current;
			return *this;
		}

		StringBuffer & operator<<(float value)
		{
			char* current = doubleToString(value);
			_str += current;
			return *this;
		}
		StringBuffer & operator<<(double value)
		{
			char* current = doubleToString(value);
			_str += current;
			return *this;
		}

		StringBuffer& operator<<(const std::string& value)
		{
			_str += value;
			return *this;
		}

	const std::string& str() const {return _str;}
	const char* c_str() const {return _str.c_str();}
	inline size_t size() const {return _str.size();}

	char* uint64ToString(long long value)
	{
		char *current = _strnum+ STR_NUM;
		--current = '\0';
		do
		{
			*--current = (value % 10) + '0';
		}
		while(value);
		return current;
	}

	char* uintToString(unsigned int value)
	{
		char* current = _strnum + STR_NUM;
		--current = 0;
		do
		{
			*--current = (value % 10) + '0';
			value /= 10;
		}
		while(value);
		return current;
	}

	char* int64ToString(signed long long value)
	{
		char* current = _strnum + STR_NUM;
		bool isNegative = value < 0;
		if(isNegative)
			value = -value;
		current = uint64ToString((long long)value);
		if(isNegative)
			*--current = '-';
		return current;
	}

	char* intToString(int value)
	{
		char* current = _strnum + STR_NUM;
		bool isNegative = value < 0;
		if(isNegative)
			value = -value;
		current = uintToString((int)value);
		if(isNegative)
			*--current = '-';
		return current;
	}

	char* doubleToString(double value,int accuracy = 4)
    {
        char *current = _strnum + STR_NUM;
        int time = 1; 
        while(accuracy--)
            time *=10;

        bool negative = false;
        bool hasNoZero = false;

        int interger = int(value);

        int decimal = 0;
        if(interger < 0)
        {	
            decimal = int(-(value - interger) * time + 0.5);
            interger = - interger;
            negative = true;
        }
        else
        {
            decimal = int((value - interger) * time + 0.5);
        }
        int decimal_temp = decimal;
        char decimal_digits  = 0;
        *--current = 0;

        while (decimal)
        {
            if(hasNoZero)
            {
                *--current = (decimal % 10) + '0';
            }
            else
            {
                decimal_digits = (decimal % 10) + '0';
                if(decimal_digits != '0')
                {
                    *--current = decimal_digits;
                    hasNoZero = true;
                }

            }
            decimal /= 10;
        } 

        if(decimal_temp)
            *--current = '.';

        do
        {
            *--current = (interger % 10) + '0';
            interger /= 10;
        } while (interger);

        if(negative)
            *--current = '-';
        return current;
    }

protected:
	char _strnum[STR_NUM];
	std::string _str;
};



#endif