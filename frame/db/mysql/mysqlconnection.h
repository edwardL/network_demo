#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include "../connection.h"

struct st_mysql;
typedef st_mysql MYSQL;
class ITransaction;


class MysqlConnection : public IConnection
{
public:
	MysqlConnection(const char* host,const char* dbuser, const char* dbpw, const char* dbname, unsigned short port, const char* charset);
	virtual ~MysqlConnection();

	// ��������
	virtual IConnection* Clone();

	// �������ݿ�
	virtual bool Connect();
	// �����������ݿ�
	virtual bool Reconnect();

	// �����Ƿ�
	virtual bool IsActive();
	// ʵ���Ƿ�ʼ
	virtual bool IsBegin();

	// �ر�����
	virtual void Close();

	//�����Ƿ��Զ��ύ
	virtual bool SetAutoCommit(bool AutoCommit);
	virtual bool GetAutoCommit();

	// ��ȡ�������
	virtual int GetErrNo() const;
	// ��ȡ�����ַ���
	virtual const char* GetError() const;

	virtual bool GetIsCache();

	// ��ȡ����ʵ�����ָ�룬����MYSQL*
	virtual void* GetConn();


	//����ʼ�����������˴������Ƿ�ʹ�û�������
	virtual bool Begin(bool isCache = true);
	// �����ύ
	virtual bool Commit();
	// ����ع�
	virtual bool Rollback();	

private:
	MYSQL *m_mysql;

	char m_user[64];
	char m_passwd[64];
	char m_host[64];
	char m_charset[64];
	char m_database[64];
	unsigned short m_port;

	bool m_begin;
	bool m_isCache;
	ITransaction * m_transaction;
};



#endif