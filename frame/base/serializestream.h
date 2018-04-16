#ifndef _SERIALIZESTREAM_H
#define _SERIALIZESTREAM_H

#include "bytebuffer.h"

#include <string>
#include <vector>

#ifndef byte
typedef unsigned char byte;
#endif

class SerializeStream
	: public ByteBuffer
{
public:
	typedef ByteBuffer super;
	SerializeStream();
	SerializeStream(int len);
	SerializeStream(const void* buf, int len);
	~SerializeStream();
};

#endif
