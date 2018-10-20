#ifndef GAME_DYNLIB_H
#define GAME_DYNLIB_H

#include<string>

class DynLib{
public:
	DynLib(const char* libfilename = "");
	~DynLib();

	bool Load();
	void Close();

	void* GetAddressForSymbol(const char* symbol);
	bool Error(){
		bool lasterror = error;
		error = false;
		return lasterror;
	}

	std::string GetName(){
		return filename;
	}

private:
	std::string filename;
	void *lptr;	//pointer to the opened library
	bool error;	//last error state
};


#endif