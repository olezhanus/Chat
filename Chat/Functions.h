#pragma once
#include <string>
#include <conio.h>
#define ESCAPE 27

bool get_string(std::string out, char enter = '\n', char escape = ESCAPE);