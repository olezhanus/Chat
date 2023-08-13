#pragma once
#include <boost/mysql.hpp>

class SQL
{
public:
	SQL();
	SQL(const SQL &other) = delete;
	SQL(SQL &&other);
	SQL &operator=(const SQL &other) = delete;
	SQL &operator=(SQL &&other);
	~SQL();

private:

};