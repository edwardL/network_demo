#pragma once
#include <vector>
#include "singleton.hpp"

using namespace std;

class Object;

class MemPool : public SingletonBase<MemPool>
{
private:
	vector<Object*> data;
public:
	void add(Object* d) { data.push_back(d); }
	void releaseAll();
};

class Object
{
private:
	int referenceCount;

public:
	virtual ~Object(){}
	Object():referenceCount(1){}
	void retain(){ referenceCount++; }
	bool Release()
	{
		return release();
	}

	bool release()
	{
		referenceCount--;
		if(referenceCount <= 0)
		{
			delete this;
			return true;
		}
		return false;
	}
	void autoRelease()
	{
		MemPool::getInstance()->add(this);
	}
};
