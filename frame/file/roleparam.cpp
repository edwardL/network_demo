#include "../base/tlvprotocol.h"
#include "roleparam.h"
#include <stdio.h>

RoleParam::RoleParam()
	:role_id(1)
//	,role_name("helloworld")
	,avatar('c')
{

}

bool RoleParam::Serialize(TLVSerializer &outstream) const
{
	bool ret = outstream.Push(role_id);
//	ret = outstream.Push(role_name);
	ret = outstream.Push(avatar);
	return true;
}

bool RoleParam::Unserialize(TLVUnserializer &instream)
{
	bool ret = instream.Pop(&role_id);
//	ret = instream.Pop(&role_name);
	ret = instream.Pop(&avatar);

	printf("asss %d, %c",role_id,avatar);
	return true;
}