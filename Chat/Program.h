#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Chat.h"
class Program
{
public:
	Program();
	Program(const Program &other) = delete;
	Program(Program &&other) = delete;
	Program &operator=(const Program &other) = delete;
	Program &operator=(Program &&other) = delete;
	void run();
	~Program() = default;
private:
	std::vector<std::shared_ptr<User>> _users;
	std::vector<std::shared_ptr<Chat>> _chats;
	
};

