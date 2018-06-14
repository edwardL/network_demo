#include "object.h"

void MemPool::releaseAll()
{
	vector<Object*>::const_iterator it;
	for(it = data.begin(); it != data.end(); it++)
	{
		(*it)->Release();
	}
	data.clear();
}