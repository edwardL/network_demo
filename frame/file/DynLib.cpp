#include "DynLib.h"
#include <Windows.h>

DynLib::DynLib(const char* libfilename)
{
	if(libfilename == NULL)
		throw "DynLib::DynLib() encountered NULL library filename";
	filename = libfilename;
	lptr = NULL;
	error = false;
}

DynLib::~DynLib()
{
	Close();
}

bool DynLib::Load()
{
	lptr = LoadLibrary((LPCWSTR)filename.c_str());
	if(lptr != NULL)
	{
		return true;
	}
	else
	{
		error = true;
		return false;
	}
}

void* DynLib::GetAddressForSymbol(const char* symbol)
{
	void* address = NULL;
	address = GetProcAddress( reinterpret_cast< HMODULE >(lptr), symbol );
	if(address == NULL)
		error = true;

	return address;
}

void DynLib::Close()
{
	if(lptr != NULL)
	{
		int err = 0;
		err = FreeLibrary(reinterpret_cast<HMODULE>(lptr));
		
		if(err != 0)
			error = true;
	}
}


