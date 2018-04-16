#ifndef ICONNECTION_H
#define ICONNECTION_H

class IConnection
{
public:
	IConnection(){};
	virtual ~IConnection(){}

	// ��������
	virtual IConnection* Clone() = 0;

	// �������ݿ�
	virtual bool Connect() = 0;
	// �����������ݿ�
	virtual bool Reconnect() = 0;

	// �����Ƿ�
	virtual bool IsActive() = 0;
	// ʵ���Ƿ�ʼ
	virtual bool IsBegin() = 0;

	// �ر�����
	virtual void Close() = 0;

	//�����Ƿ��Զ��ύ
	virtual bool SetAutoCommit(bool AutoCommit) = 0;
	virtual bool GetAutoCommit() = 0;

	virtual bool GetIsCache() = 0;
	
	// ��ȡ����ʵ�����ָ�룬����MYSQL*
	virtual void* GetConn() = 0;

	//����ʼ�����������˴������Ƿ�ʹ�û�������
	virtual bool Begin(bool isCache = true) = 0;
	// �����ύ
	virtual bool Commit() = 0;
	// ����ع�
	virtual bool Rollback() = 0;	


	// ��ȡ�������
	virtual int GetErrNo() const = 0;
	// ��ȡ�����ַ���
	virtual const char* GetError() const = 0;

	//��������ǰ��INSERT��UPDATE���ΪAUTO_INCREMENT�����ɵ�ֵ
	virtual long long GetInsertID() = 0;

	
};


#endif