#ifndef BYTE_BUFFER_H_
#define BYTE_BUFFER_H_
#define BYTE_BUFFER_INIT_SIZE 1024
class ByteBuffer
{
private:
	char* _buffer;
	int _bufferSize;
	int _dataSize;

private:
	ByteBuffer(const ByteBuffer& other);
	ByteBuffer& operator= (const ByteBuffer& other);

public:
	ByteBuffer(const int len = BYTE_BUFFER_INIT_SIZE);
	ByteBuffer(const void* buf, int len);
	virtual ~ByteBuffer();

	const int getDataSize() const;

	void clear();
	void append(const void* data, int dataSize);
	void resize(size_t size);

	void readFile(const char* file);
};


#endif