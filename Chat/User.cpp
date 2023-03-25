#include "User.h"

size_t User::_Id_Counter { 0 };

User::User(const std::string &username, const std::string &login, const Hash &password) noexcept :
	_username(username), _login(login), _password(password), _id(++_Id_Counter)//id будет начинаться с 1. 0 - для пустой переменной User.
{
}

User::User(User &&other) noexcept :
	_username(std::move(other._username)), _login(std::move(other._login)), _password(std::move(other._password)), _id(other._id)
{
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
	_password = std::move(other._password);
	_id = other._id;
	other._id = 0;
	return *this;
}

auto &User::id() const noexcept
{
	return _id;
}

auto &User::username() const noexcept
{
	return _username;
}

auto &User::login() const noexcept
{
	return _login;
}

auto &User::password() const noexcept
{
	return _password;
}
