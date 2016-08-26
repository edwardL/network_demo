#ifndef CC_XFILE_HEADER
#define CC_XFILE_HRADER

#include <string>
#include <set>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

typedef std::set<std::string> XDir;

/// 输入流
class  XReadStream
{
public:
	virtual unsigned int Read(void *buf, unsigned int maxsize) = 0;
	virtual unsigned int Read(std::string &str);

	template<class T>
	inline XReadStream& operator >> (T &value)
	{
		Read(&value,sizeof(T));
		return *this;
	}
	inline XReadStream& operator >> (std::string &value)
	{
		Read(value);
		return *this;
	}
};

/// 输出流
class XWriteStream
{
public:
	virtual unsigned int Write(const void *buf, unsigned int maxsize) = 0;
	virtual unsigned int Write(const std::string &str);

	inline XWriteStream& operator << (const std::string &value)
	{
		Write(value);
		return *this;
	}
	template<class T>
	inline XWriteStream& operator << (const T &value)
	{
		Write(&value, sizeof(value));
		return *this;
	}
};

/// 文件操作类， 以文件作为输出或者读入的介质
class XFile : public XReadStream, public XWriteStream
{
public:
	XFile(void);
	~XFile(void);

	virtual bool Open(const std::string &filename, const char* mode);
	virtual bool Open(const char *filename, const char *mode);
	virtual void Close();

	virtual unsigned int Read(void *buf, unsigned int maxsize);
	virtual unsigned int ReadAll(char *buf);
	virtual unsigned int Write(const void *buf, unsigned int maxsize);

	virtual bool SeektoBegin();
	virtual bool Seek(unsigned int offset);
	virtual bool SeektoEnd();
	
	virtual unsigned int GetFileSize();
	virtual unsigned int GetCurrentPos();
private:
	FILE* m_file;
	unsigned int m_file_size;
};

// 内存数据操作类， 以内存作为数据读入。
class XMemFileReadOnly : public XReadStream
{
public:
	XMemFileReadOnly();
	XMemFileReadOnly(char* buffer, unsigned int buffer_size);
	~XMemFileReadOnly();

	void SetBufferInfo(char* buffer,unsigned int buffer_size);
	
	virtual unsigned int Read(void* buff, unsigned int maxsize);

	virtual bool SeektoBegin();
	virtual bool Seek(unsigned int offset);
	virtual bool SeektoEnd();

	virtual unsigned int GetFileSize();
	virtual unsigned int GetCurrentPos();
	char* GetData();

	inline unsigned int GetSpace() const
	{
		return (unsigned int)m_buffer_size - (m_current - m_buffer);
	}
	
protected:
	char* m_buffer;
	char* m_current;
	unsigned int m_buffer_size;
};

class XMemFile : public XMemFileReadOnly , public XWriteStream
{
public:
	XMemFile(void);
	~XMemFile(void);

	void Reset();

	virtual unsigned int Write(const void *buf, unsigned int maxsize);

	bool SetCapacity(unsigned int size);

	bool LoadFromFile(const std::string &filename);
	bool SaveToFile(const std::string &filename);

protected:
	bool AllocMemory(unsigned int size);

	unsigned int m_alloc_size;
};


#endif