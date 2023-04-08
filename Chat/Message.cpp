// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Message.h"

auto Message::date() const noexcept -> time_t
{
	return _date;
}

auto Message::message()const noexcept -> const std::string &
{
	return _message;
}

auto Message::from() const noexcept -> const std::weak_ptr<User>
{
	return _from;
}

Message::Message(std::string &&message, std::weak_ptr<User> from) noexcept :
	_date(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
	_message(message), _from(std::move(from))
{
}

Message::Message(Message &&other) noexcept :
	_message(std::move(other._message)), _date(other._date), _from(std::move(other._from))
{
	other._date = 0;
}

Message &Message::operator=(Message &&other) noexcept
{
	if (&other == this)
	{
		return *this;
	}
	_date = std::move(other._date);
	_message = std::move(other._message);
	_date = other._date;
	other._date = 0;
	return *this;
}