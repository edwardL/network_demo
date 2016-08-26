#include "DreamXFile.h"
#include <cerrno>
#include <iostream>

#ifdef WIN32
#include<io.h>
#else
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<limits.h>
#include<string.h>
#include<stdio.h>
#endif

#include<vector>

unsigned int XReadStream::Read(std::string &str)
{
	unsigned int len;
	Read(&len,sizeof(len));
	if(len != 0)
	{
		char* buf = new char[len];
		if(buf)
		{
			len = Read(buf,len);
			str  = std::string(buf,len);
			delete []buf;
			return len + sizeof(len);
		}
	}
	return 0;
}

unsigned int XWriteStream::Write(const std::string &str)
{
	unsigned int len = (unsigned int)str.size();
	Write(&len,sizeof(unsigned int));
	Write(str.c_str(),len);
	return sizeof(len) + len;
}

XFile::XFile(void)
{
	m_file = NULL;
	m_file_size = -1;
}

XFile::~XFile(void)
{
	Close();
}

bool XFile::Open(const std::string &filename, const char* mode)
{
	return Open(filename.c_str(),mode);
}

bool XFile::Open(const char *filename, const char *mode)
{
	Close();
	m_file = fopen(filename,mode);
	if(NULL != m_file)
	{
		m_file_size = GetFileSize();
		return true;
	}
	return false;
}

void XFile::Close()
{
	if(m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
		m_file_size = -1;
	}
}

unsigned int XFile::Read(void *buf, unsigned int maxsize)
{
	unsigned int read_bytes;
	read_bytes = (unsigned int)min(maxsize,(GetFileSize() - GetCurrentPos()));
	return (unsigned int)fread(buf,read_bytes,1,m_file);
}

unsigned int XFile::ReadAll(char* buf)
{
	SeektoBegin();
	unsigned int count = 0;
	unsigned int bytes_read = 0;
	do
	{
		count = Read(buf + bytes_read, 128 * 1024);
		bytes_read += count;
	} while( count != 0);
	return bytes_read;
}

unsigned int XFile::Write(const void *buf, unsigned int maxsize)
{
	unsigned int ret = (unsigned int)fwrite(buf,maxsize,1,m_file) * maxsize;
	return ret;
}

bool XFile::SeektoBegin()
{
	if(!fseek(m_file,0,SEEK_SET))
	{
		return true;
	}
	return false;
}

bool XFile::Seek(unsigned int offset)
{
	if(!fseek(m_file,offset,SEEK_SET))
	{
		return true;
	}
	return false;
}

bool XFile::SeektoEnd()
{
	if(!fseek(m_file,0,SEEK_END))
	{
		return true;
	}
	return false;
}

unsigned int XFile::GetFileSize()
{
	if(m_file == 0)
		return -1;
	if(m_file_size != -1)
		return m_file_size;
	unsigned int pos = GetCurrentPos();
	SeektoEnd();
	unsigned int size = GetCurrentPos();
	Seek(pos);
	return size;
}

unsigned int XFile::GetCurrentPos()
{
	return (unsigned int)ftell(m_file);
}

XMemFileReadOnly::XMemFileReadOnly()
{
	m_buffer = 0;
	m_current = 0;
	m_buffer_size = 0;
}

XMemFileReadOnly::XMemFileReadOnly(char* buffer, unsigned int buffer_size)
{
	m_buffer = buffer;
	m_current = buffer;
	m_buffer_size = buffer_size;
}

XMemFileReadOnly::~XMemFileReadOnly()
{

}

void XMemFileReadOnly::SetBufferInfo(char* buffer,unsigned int buffer_size)
{
	m_buffer = buffer;
	m_buffer_size = buffer_size;
	m_current = buffer;
}

unsigned int XMemFileReadOnly::Read(void* buff, unsigned int maxsize)
{
	if(m_buffer == 0)
	{
		return 0;
	}
	unsigned int count = min(maxsize,GetSpace());
	memcpy(buff,m_current,count);
	m_current += count;
	return count;
}

bool XMemFileReadOnly::SeektoBegin()
{
	m_current = m_buffer;
	return true;
}

bool XMemFileReadOnly::Seek(unsigned int offset)
{
	if(offset > m_buffer_size)
	{
		return false;
	}
	m_current = m_buffer + offset;
	return true;
}

bool XMemFileReadOnly::SeektoEnd()
{
	m_current = m_buffer + m_buffer_size;
	return true;
}

unsigned int XMemFileReadOnly::GetFileSize()
{
	return m_buffer_size;
}

unsigned int XMemFileReadOnly::GetCurrentPos()
{
	return (unsigned int)(m_current - m_buffer);
}

char* XMemFileReadOnly::GetData()
{
	return m_buffer;
}


//------------------------------------
XMemFile::XMemFile(void)
{
	m_alloc_size = 0;
}

XMemFile::~XMemFile(void)
{
	if(m_buffer)
	{
		free(m_buffer);
	}
}

unsigned int XMemFile::Write(const void *buf, unsigned int maxsize)
{
	if(m_alloc_size - GetCurrentPos() < maxsize)
	{
		if(!AllocMemory((unsigned int)GetCurrentPos() + maxsize))
		{
			return 0;
		}
	}
	memcpy((void *)m_buffer, buf, maxsize);
	m_current += maxsize;

	if(GetCurrentPos() > m_buffer_size)
	{
		m_buffer_size = GetCurrentPos();
	}
	return maxsize;
}

bool XMemFile::SetCapacity(unsigned int size)
{
	return AllocMemory(size);
}

bool XMemFile::LoadFromFile(const std::string &filename)
{
	XFile file;
	if(!file.Open(filename.c_str(),"rb"))
	{
		return false;
	}
	unsigned int filesize = file.GetFileSize();
	SetCapacity(filesize);
	file.Read(m_buffer,(unsigned int)filesize);
	m_buffer_size = filesize;

	file.Close();
	return true;
}

bool XMemFile::SaveToFile(const std::string &filename)
{
	XFile file;
	if(!file.Open(filename.c_str(),"w+"))
	{
		std::cout<<"can not open file to write"<<std::endl;
		return false;
	}
	file.Write((void*)GetData(),(unsigned int)GetFileSize());
	file.Close();
	return true;
}

bool XMemFile::AllocMemory(unsigned int size)
{
	if(m_buffer != NULL && m_alloc_size > size)
	{
		return true;
	}
	if(m_buffer == NULL)
	{
		m_buffer = (char*)malloc(sizeof(char) * size);
		m_current = m_buffer;
		m_alloc_size = size;
		if(m_buffer != NULL)
			return true;
	}
	else
	{
		unsigned int pos = GetCurrentPos();
		m_buffer = (char*) realloc(m_buffer,size);
		m_current = NULL;
		if(m_buffer != NULL)
		{
			m_current = m_buffer + pos;
			m_alloc_size = size;
			return true;
		}
	}
	return false;
}

