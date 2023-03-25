#pragma once
#include <string>
#include "Crypto.h"
#include "Message.h"
class User : public std::enable_shared_from_this<User>
{
public:
	User(const std::string &username, const std::string &login, const Hash &password) noexcept;
	User(const User &other) = delete;
	User(User &&other) noexcept;
	User &operator=(const User &other) = delete;
	User &operator=(User &&other) noexcept;
	auto &id() const noexcept;
	auto &username() const noexcept;
	auto &login() const noexcept;
	auto &password() const noexcept;
	~User() noexcept = default;
private:
	static size_t _Id_Counter;
	size_t _id { 0 };
	std::string _username {};
	std::string _login {};
	Hash _password;
};

