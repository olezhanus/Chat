// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <vector>
#include <iostream>
#include "Program.h"
int main()
{
	auto program = std::make_unique<Basic_Program>();
	program->run();
	return 0;
}