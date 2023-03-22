#pragma once
#include <string>
class Hash
{
public:
	Hash(const std::string &data);
	Hash(const Hash &other);

	bool operator==(const Hash &other);
private:
	std::string _data;
};

const Hash &hash(const std::string &data); // ���� ���-������� (����� ���� �� �������� �� ���-�� ����������, �������� sha256)
