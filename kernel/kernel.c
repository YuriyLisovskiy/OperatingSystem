#include "../drivers/keyboard.h"

void kmain(void)
{
	clear();
	printLine("Operating system [Version 1.0]");
	printLine("(c) 2017 Yuriy Lisovskiy.");
	jumpNewLine();

	input();
	printLine("Helloooooooooo!!!!!");
	jumpNewLine();
	input();
}
