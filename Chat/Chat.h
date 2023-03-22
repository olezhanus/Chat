#pragma once
#include <memory>
#include <vector>
#include "User.h"
#include "Message.h"
class Chat : public std::enable_shared_from_this<Chat>
{
public:
	Chat();
	Chat(const Chat &other) = delete;
	Chat(Chat &&other);
	Chat &operator=(const Chat &other) = delete;
	Chat &operator=(Chat &&other);
	~Chat();
private:
	std::vector<std::shared_ptr<User>> _users;
	std::vector<std::shared_ptr<Message>> _messages;
};

