#include "Crypto.h"

Hash::Hash(const std::string &data) : _data(data)
{
}

Hash::Hash(const Hash &other) : _data(other._data)
{
}

Hash::Hash(Hash &&other) : _data(std::move(other._data))
{
}

Hash &Hash::operator=(const Hash &other)
{
	if (&other == this)
	{
		return *this;
	}
	_data = other._data;
	return *this;
}

Hash &Hash::operator=(Hash &&other)
{
	if (&other == this)
	{
		return *this;
	}
	_data = std::move(other._data);
	return *this;
}

bool Hash::operator==(const Hash &other)
{
	return _data == other._data;
}
