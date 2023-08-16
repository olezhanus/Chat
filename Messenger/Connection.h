#pragma once
#include <boost/asio.hpp>

class Connection
{
public:
	Connection();
	Connection(const Connection &other) = delete;
	Connection(Connection &&other);
	Connection &operator=(const Connection &other) = delete;
	Connection &operator=(Connection &&other);
	~Connection();

	boost::asio::io_context io_context;
private:
	
};