#ifndef ICONNECTION_H
#define ICONNECTION_H

class IConnection
{
public:
	IConnection(){};
	virtual ~IConnection(){}

	// 复制链接
	virtual IConnection* Clone() = 0;

	// 连接数据库
	virtual bool Connect() = 0;
	// 重新连接数据库
	virtual bool Reconnect() = 0;

	// 连接是否活动
	virtual bool IsActive() = 0;
	// 实务是否开始
	virtual bool IsBegin() = 0;

	// 关闭连接
	virtual void Close() = 0;

	//设置是否自动提交
	virtual bool SetAutoCommit(bool AutoCommit) = 0;
	virtual bool GetAutoCommit() = 0;

	virtual bool GetIsCache() = 0;
	
	// 获取连接实体对象指针，例如MYSQL*
	virtual void* GetConn() = 0;

	//事务开始，参数表明此次事务是否使用缓存事务
	virtual bool Begin(bool isCache = true) = 0;
	// 事务提交
	virtual bool Commit() = 0;
	// 事务回滚
	virtual bool Rollback() = 0;	


	// 获取错误代码
	virtual int GetErrNo() const = 0;
	// 获取错误字符串
	virtual const char* GetError() const = 0;

	//返回由以前的INSERT或UPDATE语句为AUTO_INCREMENT列生成的值
	virtual long long GetInsertID() = 0;

	
};


#endif