// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Chat.h"

Chat::Chat(std::string &&title) noexcept : 
	_title(title)
{
}

Chat::Chat(Chat &&other) noexcept :
	_users(std::move(other._users)), _messages(std::move(other._messages)), _title(std::move(other._title))
{
}

Chat &Chat::operator=(Chat &&other) noexcept
{
	if (&other == this)
	{
		return *this;
	}
	_users = std::move(other._users);
	_messages = std::move(other._messages);
	_title = std::move(other._title);
	return *this;
}

auto Chat::users() noexcept -> std::vector<std::weak_ptr<User>> &
{
	return _users;
}

auto Chat::messages() noexcept -> std::vector<std::shared_ptr<Message>> &
{
	return _messages;
}

auto Chat::title() const noexcept -> const std::string &
{
	return _title;
}

void Chat::add_user(std::shared_ptr<User> user)
{
	if (user->id() != 0)
	{
		_users.emplace_back(std::move(user));
	}
}

void Chat::new_message(std::shared_ptr<Message> message)
{
	_messages.emplace_back(std::move(message));
}
