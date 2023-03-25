#pragma once
#include <memory>
#include <vector>
#include "User.h"
#include "Message.h"
class Chat : public std::enable_shared_from_this<Chat>
{
public:
	Chat() noexcept;
	Chat(const Chat &other) = delete;
	Chat(Chat &&other) noexcept;
	Chat &operator=(const Chat &other) = delete;
	Chat &operator=(Chat &&other) noexcept;
	auto &users() const noexcept;
	auto &messages() const noexcept;
	~Chat() noexcept;
private:
	std::vector<std::weak_ptr<User>> _users;
	std::vector<std::shared_ptr<Message>> _messages;
};

