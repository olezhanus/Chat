#include "Crypto.h"

Hash::Hash(const std::string &data) : _data(data)
{
}

Hash::Hash(const Hash &other) : _data(other._data)
{
}

bool Hash::operator==(const Hash &other)
{
	return _data == other._data;
}

const Hash &hash(const std::string &data)
{
	return Hash(data);
}
