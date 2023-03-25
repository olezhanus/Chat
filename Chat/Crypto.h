#pragma once
#include <string>
class Hash // Типа хэш-функция (потом надо бы заменить на что-то нормальное, например sha256)

{
public:
	Hash(const std::string &data = "") noexcept;
	Hash(const Hash &other) noexcept;
	Hash(Hash &&other) noexcept;
	Hash &operator=(const Hash &other) noexcept;
	Hash &operator=(Hash &&other) noexcept;

	bool operator==(const Hash &other) noexcept;
private:
	std::string _data;
};
