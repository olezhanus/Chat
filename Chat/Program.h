#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include "User.h"
#include "Chat.h"
#define ENTER '\r'
#define ESCAPE 27
#define BACKSPACE 8
#define LOGIN_MIN_LENGTH 1
#define PASSWORD_MIN_LENGTH 1
#define NAME_MIN_LENGTH 1

class Basic_Program // Базовый класс программы с консольным интерфейсом. от него можно наследовать другие реализации UI
{
public:
	Basic_Program() noexcept = default;
	Basic_Program(const Basic_Program &other) = delete;
	Basic_Program(Basic_Program &&other) = delete;
	Basic_Program &operator=(const Basic_Program &other) = delete;
	Basic_Program &operator=(Basic_Program &&other) = delete;
	virtual void run();
	
	virtual ~Basic_Program() = default;
protected:
	std::vector<std::shared_ptr<User>> _users;
	std::vector<std::shared_ptr<Chat>> _chats; // Список всех чатов
	std::weak_ptr<User> _logined_user;
	std::weak_ptr<Chat> _current_chat;
	virtual void log_in();
	virtual void sign_up();
	virtual void log_out() noexcept;
	virtual void show_chats();
	virtual void show_users();
	virtual void show_messages() noexcept;
	virtual void print_message(const std::shared_ptr<Message> &mes) noexcept;

	virtual void do_command(const std::string &command);
	virtual bool get_string(std::string &out, size_t min_length = 0, bool is_password = false, bool need_to_erase = false, char enter = ENTER, char escape = ESCAPE) noexcept;
};

