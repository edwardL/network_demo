#pragma once

#ifndef IINTERFACEMGR_H
#define IINTERFACEMGR_H

class IModule;

class IInterfaceMgr
{
public:
	virtual ~IInterfaceMgr(){}

	/* ע��ģ�鵽IInterfaceMgr �С�
	@name  ģ������Ҫ���Ǿ�̬�ַ����� ÿ��IModule ��ʵ�ֶ���������һ����̬�ַ�������������Ϊ��ģ��ı�־��
	@module ��ע���ģ��
	@Return �Ƿ�ע��ɹ�
	*/
	virtual bool RegisterModule(const char* name, IModule *module) = 0;

	/* ��ѯģ��
	*/
	virtual IModule* QueryModule(const char* name) = 0;

	/* ����������ֹͣ
	@loop_interval ÿ��ѭ����϶ʱ��
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