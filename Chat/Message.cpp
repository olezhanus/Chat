#include "Message.h"

auto &Message::date() const noexcept
{
	return _date;
}

auto &Message::message()const noexcept
{
	return _message;
}

Message::Message(const std::string &message, std::weak_ptr<User> from, std::weak_ptr<Chat> _to) noexcept :
	_message(message), _date(std::chrono::system_clock::now())
{
}

Message::Message(std::string &&message, std::weak_ptr<User> from, std::weak_ptr<Chat> _to) noexcept :
	_message(message), _date(std::chrono::system_clock::now())
{
}

Message::Message(Message &&other) noexcept :
	_date(std::move(other._date)),_message(std::move(other._message))
{
}

Message &Message::operator=(Message &&other)
{
	if (&other == this)
	{
		return *this;
	}
	_date = std::move(other._date);
	_message = std::move(other._message);
	_date = std::chrono::time_point<std::chrono::system_clock>();
	_message = std::string();
	return *this;
}
