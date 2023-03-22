#pragma once
#include <chrono>
#include <memory>
#include <string>
class User;
class Chat;

class Message : public std::enable_shared_from_this<Message>
{
public:
	friend class User;

	~Message() noexcept = default;
	auto &date() const noexcept;
	auto &message() const noexcept;
private:
	Message(const std::string &message, std::weak_ptr<User> from, std::weak_ptr<Chat> _to) noexcept;
	Message(std::string &&message, std::weak_ptr<User> from, std::weak_ptr<Chat> _to) noexcept;
	Message(const Message &other) = delete;
	Message(Message &&other) noexcept;
	Message &operator=(const Message &other) = delete;
	Message &operator=(Message &&other) noexcept;

	std::chrono::time_point<std::chrono::system_clock> _date;
	std::string _message;
	std::weak_ptr<User> _from;
	std::weak_ptr<User> _to;
};

