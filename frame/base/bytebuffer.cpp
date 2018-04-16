#include "bytebuffer.h"
#include<memory.h>
#include<string.h>
#include<stdlib.h>
#include "fstream"

ByteBuffer::ByteBuffer(const int len /* = BYTE_BUFFER_INIT_SIZE */)
	:_dataSize(0),_buffer(NULL),_bufferSize(0)
{
	if(len != 0)
	{
		_buffer = (char*)malloc(len);
		if(_buffer != NULL)
		{
			
		}
	}
}

ByteBuffer::ByteBuffer(const void* buf, int len)
{
	_buffer = (char*)buf;
	_bufferSize = len;
	_dataSize = len;
}

ByteBuffer::~ByteBuffer()
{
	if(_buffer != NULL)
	{
		free(_buffer);
	}
	_buffer = NULL;
}

const int ByteBuffer::getDataSize() const
{
	return _dataSize;
}

void ByteBuffer::clear()
{
	_dataSize = 0;
	if(_buffer)
	{
		free(_buffer);
		_buffer = NULL;
	}
}

void ByteBuffer::readFile(const char* file)
{
	clear();
	std::ifstream ifs(file,std::istream::binary);

	if(!ifs.is_open())
	{
		return;
	}
	char buf[1024 * 4];
	while(!ifs.eof())
	{
		ifs.read(buf,sizeof(buf));
		append(buf,ifs.gcount());
	}
}

void ByteBuffer::append(const void* data, int dataSize)
{
	memcpy(_buffer + _dataSize , data, dataSize);
	_dataSize += dataSize;
}

void ByteBuffer::resize(size_t size)
{
	if(size < (size_t)_bufferSize)
	{
		_dataSize = (int)size;
		return;
	}
	_dataSize = (int)size;
}

