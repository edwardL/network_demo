#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "../base/vector.h"
typedef void (*event_func)(void* arg);

class Event
{
private:
	unsigned int event_id;
	unsigned int bind_id_count;
	Vector<event_func> event_func_list;

public:
	void Execute()
	{
		for(int i = 0; i < bind_id_count; i++)
		{
			event_func_list[i](NULL);
		}
	}
};


#endif