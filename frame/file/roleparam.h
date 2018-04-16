#ifndef ROLEPARAM_H
#define ROLEPARAM_H

#include <string>

class TLVSerializer;
class TLVUnserializer;

class RoleParam
{
public:
	RoleParam();

	bool Serialize(TLVSerializer &outstream) const;
	bool Unserialize(TLVUnserializer &instream);

	int role_id;
//	std::string role_name;
	char avatar;
	long long create_time;
};

#endif