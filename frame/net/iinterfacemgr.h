#pragma once

#ifndef IINTERFACEMGR_H
#define IINTERFACEMGR_H

class IModule;

class IInterfaceMgr
{
public:
	virtual ~IInterfaceMgr(){}

	/* 注册模块到IInterfaceMgr 中。
	@name  模块名，要求是静态字符串， 每个IModule 的实现都必须声明一个静态字符串名，用来作为该模块的标志符
	@module 被注册的模块
	@Return 是否注册成功
	*/
	virtual bool RegisterModule(const char* name, IModule *module) = 0;

	/* 查询模块
	*/
	virtual IModule* QueryModule(const char* name) = 0;

	/* 阻塞运行至停止
	@loop_interval 每次循环间隙时间
	*/
	virtual void Run(unsigned long loop_interval) = 0;

	virtual void Stop() = 0;

	virtual int GetWorkPath(char* path, int max_len)const = 0;

	enum GameState
	{
		GS_STOP = 0;
		GS_RUNNING,
		GS_STOPPING,
	};
	
	virtual int Update() = 0;
};


#endif