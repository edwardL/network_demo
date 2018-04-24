#ifndef ITRANSACTION_H
#define ITRANSACTION_H

class ITransaction
{
public:
	ITransaction() {};
	virtual ~ITransaction(){};

	virtual bool Begin() = 0;
	virtual bool Commit() = 0;
	virtual bool Rollback() = 0;
	virtual bool IsBegin() = 0;
	virtual ITransaction* Clone() = 0;
};

#endif