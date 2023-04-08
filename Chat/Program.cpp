// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Program.h"

void Basic_Program::run()
{
	while (true)
	{
		system("cls");
		if (_logined_user.expired())
		{
			std::cout << "esc - выход.\tl - войти.\ts - создать аккаунт.\n";
			char command;
			do
			{
				command = _getch();
			}
			while (command != ESCAPE &&
				   command != 'l' && command != 'L' &&
				   command != 's' && command != 'S'); // будет ждать ввода правильного символа

			if (command == ESCAPE)
			{
				break;
			}
			if (command == 'l' || command == 'L')
			{
				log_in();
			}
			if (command == 's' || command == 'S')
			{
				sign_up();
			}
		}
		else
		{
			if (_current_chat.expired())
			{
				std::cout << "esc - выход.\ts - выбрать чат.\td - удалить чат\t\tn - новый чат.\n";
				char command;
				do
				{
					command = _getch();
				}
				while (command != ESCAPE &&
					   command != 's' && command != 'S' &&
					   command != 'd' && command != 'D' &&
					   command != 'n' && command != 'N');

				if (command == ESCAPE)
				{
					log_out();
					continue;
				}
				if (command == 's' || command == 'S' ||
					command == 'd' || command == 'D')
				{
					show_chats();
					std::string number_string;
					size_t number = 0;
					bool is_continue;

					auto &user_chats = _logined_user.lock()->chats();
					auto size = user_chats.size();
					std::cout << "Введите номер: ";
					while (is_continue = get_string(number_string))
					{
						if (!sscanf_s(number_string.c_str(), "%zu", &number) || number >= size)
						{
							std::cout << "\nВведите корректный номер: ";
							continue;
						}
						break;
					}
					if (!is_continue)
					{
						continue;
					}

					auto index = size - number - 1;

					if (command == 's' || command == 'S')
					{
						_current_chat = user_chats[index];
					}
					if (command == 'd' || command == 'D')
					{
						// выходим из чата. Если чат пуст, удаляем его
						auto user_chat = user_chats[index].lock();
						auto &user_chat_users = user_chat->users();
						auto iter = std::find_if(
							user_chat_users.begin(),
							user_chat_users.end(),
							[=](std::weak_ptr<User> el) -> bool
							{
								return el.lock() == _logined_user.lock();
							});

						user_chat->new_message(std::make_shared<Message>(std::move("*Покинул беседу*"), _logined_user));
						user_chat_users.erase(iter);
						if (user_chat_users.empty())
						{
							auto chat_to_erase = std::find(
								_chats.begin(),
								_chats.end(),
								user_chat);
							_chats.erase(chat_to_erase);
						}
						user_chats.erase(user_chats.begin() + index);
					}
				}
				if (command == 'n' || command == 'N')
				{
					// Создаём новый чат с выбранным пользователем и добавляем его во все соответствующие вектора
					system("cls");
					show_users();
					std::string number_string;
					size_t number = 0;
					bool is_continue;

					std::cout << "Введите номер: ";
					while (is_continue = get_string(number_string))
					{
						if (!sscanf_s(number_string.c_str(), "%zu", &number) || number >= _users.size())
						{
							std::cout << "\nВведите корректный номер: ";
							continue;
						}

						if (_users[number] == _logined_user.lock())
						{
							std::cout <<
								"\nВ беседе не может быть два одинаковых пользователя\n"
								"Введите корректный номер: ";
							continue;
						}
						break;
					}
					if (!is_continue)
					{
						continue;
					}

					std::cout << "\nВведите название: ";
					std::string title;
					if (!get_string(title, NAME_MIN_LENGTH))
					{
						continue;
					}
					_chats.emplace_back(std::make_shared<Chat>(std::move(title)));
					_chats.back()->add_user(_logined_user.lock());
					_chats.back()->add_user(_users[number]);
					_logined_user.lock()->chats().push_back(_chats.back());
					_users[number]->chats().emplace_back(_chats.back());
					_current_chat = _chats.back();
				}
			}
			else
			{
				std::cout <<
					"Введите сообщение или одну из следующих команд:\n"
					"/add_user - добавить участника\t/show_users - показать участников беседы\n\n";
				show_messages();
				std::string message_string;
				while (true)
				{
					;
					if (!get_string(message_string, 0, false, true))
					{
						_current_chat.reset();
						break;
					}
					if (!message_string.empty())
					{
						if (message_string[0] == '/')
						{
							do_command(message_string);
							break;
						}
						else
						{
							_current_chat.lock()->new_message(std::make_shared<Message>(std::move(message_string), _logined_user));

							// Перемещаем _current_chat с новым сообщением в конец массива
							auto &user_chat = _logined_user.lock()->chats();
							if (_current_chat.lock() != user_chat.back().lock())
							{
								auto iter = std::find_if(
									user_chat.begin(),
									user_chat.end(),
									[=](std::weak_ptr<Chat> el) -> bool
									{
										return el.lock() == _current_chat.lock();
									});
								auto item = *iter;
								user_chat.erase(iter);
								user_chat.emplace_back(std::move(item));
							}

							print_message(_current_chat.lock()->messages().back());
						}
					}
				}
			}
		}
	}
}

void Basic_Program::log_in()
{
	std::string login, password;
	while (true)
	{
		system("cls");
		std::cout << "Логин: ";
		if (!get_string(login))
		{
			break;
		}
		auto iter = _users.empty() ? _users.end() : std::find_if(
			_users.begin(),
			_users.end(),
			[=](std::shared_ptr<User> el) -> bool
			{
				return el->login() == login;
			});

		if (iter == _users.end())
		{
			std::cout << "\nПользователя с таким логином не существует";
			_getch();
			continue;
		}
		std::cout << "\nПароль: ";
		if (!get_string(password, PASSWORD_MIN_LENGTH, true))
		{
			continue;
		}
		if (std::hash<std::string> {}(password) != (*iter)->password_hash())
		{
			std::cout << "\nНеправильный пароль";
			_getch();
			continue;
		}
		_logined_user = *iter;
		break;
	}
}

void Basic_Program::sign_up()
{
	std::string login, password, username;
	while (true)
	{
		system("cls");
		std::cout << "Логин: ";
		if (!get_string(login, LOGIN_MIN_LENGTH))
		{
			break;
		}
		auto iter = _users.empty() ? _users.end() : std::find_if(
			_users.begin(), _users.end(),
			[=](std::shared_ptr<User> el) -> bool
			{
				return el->login() == login;
			});
		if (iter != _users.end())
		{
			std::cout << "\nПользователь с таким логином уже существует";
			_getch();
			continue;
		}
		std::cout << "\nПароль: ";
		if (!get_string(password, PASSWORD_MIN_LENGTH, true))
		{
			continue;
		}
		std::cout << "\nВведите имя пользователя: ";
		if (!get_string(username, NAME_MIN_LENGTH))
		{
			continue;
		}
		_users.emplace_back(std::make_shared<User>(std::move(username), std::move(login), std::hash<std::string>{}(password)));
		_logined_user = *(_users.end() - 1);
		break;
	}
}

void Basic_Program::log_out() noexcept
{
	_logined_user.reset();
}

void Basic_Program::show_chats()
{
	auto size = _logined_user.lock()->chats().size();
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << i << '\t' <<
			_logined_user.lock()->chats()[size - i - 1].lock()->title() << "\n\n";
	}
}

void Basic_Program::show_users()
{
	for (size_t i = 0; i < _users.size(); ++i)
	{
		std::cout << i << '\t' << _users[i]->username() << "\n\n";
	}
}

void Basic_Program::show_messages() noexcept
{
	for (auto &mes : _current_chat.lock()->messages())
	{
		print_message(mes);
	}
}

void Basic_Program::print_message(const std::shared_ptr<Message> &mes) noexcept
{
	tm _tm;
	time_t t = mes->date();
	localtime_s(&_tm, &t);
	auto date = std::put_time(&_tm, "%Y %T");
	std::cout <<
		(mes->from().lock() == _logined_user.lock() ? "Вы" : mes->from().lock()->username()) << ":\n" <<
		mes->message() << "\n" <<
		date << "\n\n\n";
}

void Basic_Program::do_command(const std::string &command)
{
	if (command == "/add_user")
	{
		system("cls");
		show_users();
		std::string number_string;
		size_t number = 0;
		bool is_return;

		auto &chat_users = _current_chat.lock()->users();
		std::cout << "Введите номер: ";
		while (is_return = get_string(number_string))
		{
			if (!sscanf_s(number_string.c_str(), "%zu", &number) || number >= _users.size())
			{
				std::cout << "\nВведите корректный номер: ";
				continue;
			}

			if (std::find_if(
				chat_users.begin(),
				chat_users.end(),
				[=](std::weak_ptr<User> el) -> bool
				{
					return el.lock() == _users[number];
				}) != chat_users.end())
			{
				std::cout <<
					"\nВ беседе не может быть два одинаковых пользователя\n"
					"Введите корректный номер: ";
				continue;
			}
				break;
		}
		if (!is_return)
		{
			return;
		}

		_current_chat.lock()->add_user(_users[number]);
		_users[number]->chats().emplace_back(_current_chat);
	}
	else if (command == "/show_users")
	{
		system("cls");
		for (auto &user : _current_chat.lock()->users())
		{
			std::cout << user.lock()->username() << "\n\n";
		}
		_getch();
	}
	else
	{
		std::cout << "\nНеизвестная команда\n";
	}
}

bool Basic_Program::get_string(std::string &out, size_t min_length, bool is_password, bool need_to_erase, char enter, char escape) noexcept
{
	std::string str;
	while (true)
	{
		const char ch = _getch();
		if (ch == BACKSPACE)
		{
			if (!str.empty())
			{
				str.pop_back();
				std::cout << "\b \b";
			}
		}
		else if (ch == enter)
		{
			if (str.length() >= min_length)
			{
				if (need_to_erase)
				{
					for (auto &c : str)
					{
						std::cout << "\b \b";
					}
				}
				out = std::move(str);
				return true;
			}
			else
			{
				std::cout << "\nВведите минимум " << min_length << " символов\n";
				str.clear();
			}
		}
		else if (ch == escape)
		{
			return false;
		}
		else
		{
			str += ch;
			std::cout << (is_password ? '*' : ch); // Русский язык не завезли
		}
	}
}