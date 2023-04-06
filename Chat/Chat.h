#pragma once
#include <memory>
#include <vector>
#include "User.h"
#include "Message.h"

class Chat : public std::enable_shared_from_this<Chat>
{
public:

	Chat(std::string &&title) noexcept;
	Chat(const Chat &other) = delete;
	Chat(Chat &&other) noexcept;
	Chat &operator=(const Chat &other) = delete;
	Chat &operator=(Chat &&other) noexcept;
	auto users() noexcept -> std::vector<std::weak_ptr<User>> &;
	auto messages() noexcept -> std::vector<std::shared_ptr<Message>> &;
	auto title() const noexcept -> const std::string &;
	void add_user(std::shared_ptr<User> user);
	void new_message(std::shared_ptr<Message> message);
	~Chat() noexcept = default;
private:
	std::vector<std::weak_ptr<User>> _users;
	std::vector<std::shared_ptr<Message>> _messages;
	std::string _title;
};