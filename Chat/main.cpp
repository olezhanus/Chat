#include <vector>
#include <iostream>
#include <conio.h>
#include "Program.h"
int main()
{
	setlocale(LC_ALL, "");
	auto program = std::make_unique<Basic_Program>();
	program->run();
	return 0;
}