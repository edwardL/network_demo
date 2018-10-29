#ifndef _BYTEBUFFER_H
#define _BYTEBUFFER_H
#include<vector>

class TByteBuffer
{
public:
	const static size_t DEFAULT_SIZE = 0x1000;

	TByteBuffer() : _rpos(0) , _wpos(0){
		_storage.reserve(DEFAULT_SIZE);
	}
	TByteBuffer(size_t res): _rpos(0), _wpos(0) {
		_storage.reserve(res);
	}
	TByteBuffer(const TByteBuffer &buf): _rpos(0), _wpos(0), _storage(buf._storage){}
	virtual ~TByteBuffer() {}

	void clear() {
		_storage.clear();
		_rpos = _wpos = 0;
	}

	template<typename T> void append(T value) {
		append((unsigned char*)&value, sizeof(value));
	}

	TByteBuffer& operator<<(bool value)
	{
		append((unsigned char*)&value, sizeof(bool));
		return *this;
	}
	// unsigned 
	TByteBuffer& operator<<(unsigned char value)
	{
		append((unsigned char*)&value,sizeof(unsigned char));
		return *this;
	}

	TByteBuffer& operator<<(unsigned short value)
	{
		append((unsigned char*)&value, sizeof(unsigned short));
		return *this;
	}

	TByteBuffer& operator<<(unsigned int value)
	{
		append((unsigned char*)&value, sizeof(unsigned int));
		return *this;
	}

	TByteBuffer& operator<<(unsigned long long value)
	{
		append((unsigned char*)&value, sizeof(unsigned long long));
		return *this;
	}

	TByteBuffer& operator<<(signed char value)
	{
		append((unsigned char*)&value, sizeof(signed char));
		return *this;
	}

	TByteBuffer& operator<<(signed short value)
	{
		append((unsigned char*)&value, sizeof(signed short));
		return *this;
	}

	TByteBuffer& operator<<(signed int value)
	{
		append((unsigned char*)&value, sizeof(signed int));
		return *this;
	}

	TByteBuffer& operator<<(signed long long value)
	{
		append((unsigned char*)&value, sizeof(signed long long));
		return *this;
	}

	TByteBuffer& operator<<(float value)
	{
		append((unsigned char*)&value, sizeof(float));
		return *this;
	}
	TByteBuffer& operator<<(double value)
	{
		append((unsigned char*)&value,sizeof(double));
		return *this;
	}

	TByteBuffer& operator<<(const std::string & value)
	{
		append((unsigned char*)value.c_str(),value.length());
		append((unsigned char*)0);
		return *this;
	}

	TByteBuffer& operator<<(const char* str)
	{
		append((unsigned char*)str,strlen(str));
		append((unsigned char*)0);
		return *this;
	}


	//--------------------------------read µÄ
	TByteBuffer& operator>>(bool &value)
	{
		value = read<char>(_rpos) > 0 ? true : false;
		_rpos += sizeof(char);
		return *this;
	}
	/// unsigned
	TByteBuffer& operator>>(unsigned char value)
	{
		value = read<unsigned char>(_rpos);
		_rpos += sizeof(unsigned char);
		return *this;
	}

	TByteBuffer& operator>>(unsigned short value)
	{
		value = read<unsigned short>(_rpos);
		_rpos += sizeof(unsigned short);
		return *this;
	}
	
	TByteBuffer& operator>>(unsigned int value)
	{
		value = read<unsigned int>(_rpos);
		_rpos += sizeof(unsigned int);
		return *this;
	}

	TByteBuffer& operator>>(unsigned long long value)
	{
		value = read<unsigned long long>(_rpos);
		_rpos += sizeof(unsigned long long);
		return *this;
	}

	TByteBuffer& operator>>(signed char value)
	{
		value = read<signed char>(_rpos);
		_rpos += sizeof(signed char);
		return *this;
	}

	TByteBuffer& operator>>(signed short value)
	{
		value = read<signed short>(_rpos);
		_rpos += sizeof(signed short);
		return *this;
	}
	
	TByteBuffer& operator>>(signed int value)
	{
		value = read<signed int>(_rpos);
		_rpos += sizeof(signed int);
		return *this;
	}

	TByteBuffer& operator>>(signed long long value)
	{
		value = read<signed long long>(_rpos);
		_rpos += sizeof(signed long long);
		return *this;
	}

	TByteBuffer& operator>>(float& value)
	{
		value = read<float>(_rpos);
		_rpos += sizeof(float);
		return *this;
	}

	TByteBuffer& operator>>(double& value)
	{
		value = read<double>(_rpos);
		_rpos += sizeof(double);
		return *this;
	}

	TByteBuffer& operator>>(std::string &value)
	{
		value.clear();
		while(true)
		{
			char c = read<char>();
			if(c == 0)
				break;
			value += c;
		}
		return *this;
	}

	unsigned operator[](size_t pos)
	{
		return read<unsigned char>(pos);
	}

	///----- read end

	size_t rpos()
	{
		return _rpos;
	}
	size_t rpos(size_t rpos)
	{
		_rpos = rpos;
		return _rpos;
	}
	size_t wpos()
	{
		return _wpos;
	}
	size_t wpos(size_t wpos)
	{
		_wpos = wpos;
		return _wpos;
	}

	template<class T> T read()
	{
		T r = read<T>(_rpos);
		_rpos += sizeof(T);
		return r;
	}
	template<typename T> T read(size_t pos) const
	{
		if(pos + sizeof(T) > sizeof())
		{
			return (T)0;
		}
		else
		{
			return *((T*)&_storage[pos]);
		}
	}
	void read(unsigned char* desc, size_t len)
	{
		if(_rpos + len <= size())
		{
			memcpy(desc,&_storage[_rpos],len);
		}
		else
		{
			memset(desc,0,len);
		}
		_rpos += len;
	}

	inline size_t size() const {return _storage.size();}
	inline size_t capacity() const {return _storage.capacity();}

	void resize(size_t newsize) {
		_storage.resize(newsize);
		_rpos = 0;
		_wpos = size();
	}

	void reserve(size_t ressize)
	{
		if(ressize > size()) _storage.reserve(ressize);
	}

	void append(const std::string& str){
		append((unsigned char*)str.c_str(), str.size() + 1);
	}
	
	void append(const char* src, size_t cnt) {
		return append((const unsigned char*)src, cnt);
	}

	void append(const unsigned char* src, size_t cnt) {
		if(!cnt) return;
		if(_storage.size() < _wpos + cnt)
			_storage.resize(_wpos + cnt);
		if(_storage.size() > _wpos)
		{
			memcpy(&_storage[_wpos], src , cnt);
			_wpos += cnt;
		}
	}

protected:
	size_t _rpos, _wpos;
	std::vector<unsigned char> _storage;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
template<typename T> TByteBuffer& operator<<(TByteBuffer &b, std::vector<T> v)
{
	b << (unsigned int)v.size();
	for(typename std::vector<T>::iterator i = v.begin(); i != v.end(); i++) {
		b << *i;
	}
	return b;
}

template<typename T> TByteBuffer& operator>>(TByteBuffer &b, std::vector<T> &v)
{
	unsigned int vsize;
	b >> vsize;
	v.clear();
	while(vsize--)
	{
		T t;
		b >> t;
		v.push_back(t);
	}
	return b;
}

template<typename T>TByteBuffer& operator<<(TByteBuffer& b, std::list<T> v)
{
	b << (unsigned int)v.size();
	for(typename std::list<T>::iterator i = v.begin(); i != v.end(); ++i)
	{
		b << *i;
	}
	return b;
}

template<typename T>TByteBuffer& operator>>(TByteBuffer& b, std::list<T> &v)
{
	unsigned int vsize;
	b >> bsize;
	v.clear();
	while(vsize--)
	{
		T t;
		b >> t;
		v.push_back(t);
	}
	return v;
}

template<typename K, typename V>TByteBuffer& operator<<(TBypeBuffer& b, std::map<K,V> &m)
{
	b << (unsigned int)m.size();
	for(typename std::map<K,V>::iterator i = m.begin(); i != m.end(); i++)
	{
		b << i->first << i->second;
	}
	return b;
}

template<typename K, typename V>TByteBuffer& operator<<(TBypeBuffer& b, std::map<K,V>& m)
{
	unsigned int msize;
	b >> msize;
	m.clear();
	while(msize--)
	{
		K k;
		V v;
		b >> k >> v;
		m.insert(make_pair(k,v));
	}
	return b;
}


#endif