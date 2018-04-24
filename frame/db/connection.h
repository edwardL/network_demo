#ifndef ICONNECTION_H
#define ICONNECTION_H

class IStatement;
class ITransaction;

class IConnection
{
public:
	IConnection(){};
	virtual ~IConnection(){};

	// ��������
	virtual IConnection* Clone() = 0;
	// �������ݿ�
	virtual bool Connect() = 0;
	// �����������ݿ�
	virtual bool Reconnect() = 0;
	// �����Ƿ�
	virtual bool IsActive() = 0;
	// �����Ƿ�ʼ
	virtual bool IsBegin() = 0;
	//�ر�����
	virtual void Close() = 0;
	//�Ƿ�������
	virtual bool IsClosed() = 0;

	// �����Ƿ��Զ��ύ
	virtual bool SetAutoCommit(bool AutoCommit) = 0;
	virtual bool GetAutoCommit() = 0;


	// �����Ƿ�ʹ�û���
	virtual bool GetIsCache() = 0;

	// ��ȡ����ʵ�����ָ��,����MYSQL*
	virtual void* GetConn() = 0;

	// ��������ǰ��insert ����update ���Ϊauto_increment �����ɵ�ֵ
	virtual long long GetInsertID() = 0;

	// ����ʼ, ���������˴������Ƿ�ʹ�û�������
	virtual bool Begin(bool iscache = true) = 0;
	// �����ύ
	virtual bool Commit() = 0;
	// ����ع�
	virtual bool Rollback() = 0;

	virtual IStatement* createStatement() = 0;

	// ��ȡ�������
	virtual int GetErrNo() const = 0;
	// ��ȡ�����ַ���
	virtual const char* GetError() const = 0;
};

#endif