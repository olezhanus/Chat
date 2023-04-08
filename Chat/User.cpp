// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "User.h"

size_t User::_Id_Counter { 0 };

User::User(std::string &&username, std::string &&login, size_t password) noexcept :
	_username(username), _login(login), _password_hash(password), _id(++_Id_Counter)//id будет начинаться с 1. 0 - для пустой переменной User.
{
}

User::User(User &&other) noexcept :
	_username(std::move(other._username)), _login(std::move(other._login)), _password_hash(other._password_hash), _id(other._id)
{
	other._password_hash = 0;
	other._id = 0;
}

User &User::operator=(User &&other) noexcept
{
	if (&other == this)
	{
		return *this;
	}
	_username = std::move(other._username);
	_login = std::move(other._login);
	_password_hash = std::move(other._password_hash);
	_id = other._id;
	other._id = 0;
	return *this;
}

auto User::id() const noexcept -> size_t
{
	return _id;
}

auto User::username() const noexcept -> const std::string &
{
	return _username;
}

auto User::login() const noexcept -> const std::string &
{
	return _login;
}

auto User::password_hash() const noexcept -> size_t
{
	return _password_hash;
}

auto User::chats() noexcept -> std::vector<std::weak_ptr<Chat>> &
{
	return _chats;
}

void User::set_username(const std::string &new_username) noexcept
{
	if (_username == new_username)
	{
		return;
	}
	_username = new_username;
}
