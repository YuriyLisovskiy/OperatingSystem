#ifndef SIMPLE_OS_UTILS_H
#define SIMPLE_OS_UTILS_H

#include "../utils/header.h"

char *vidPtr = (char *) 0xb8000;
unsigned int currentPosStr = 0;

// info:
// Prints string on the screen.
void print(const char *str)
{
	unsigned int i = 0;

	// This loop writes the string to video memory.
	while (str[i] != '\0') {
		// The character's ascii.
		vidPtr[currentPosStr++] = str[i++];
		// Attribute-byte: give character black background and light grey fg.
		vidPtr[currentPosStr++] = 0x02;
	}
	return;
}

// info:
// Clear screen.
void clear(void)
{
	unsigned int i = 0;

	// This loop clears the screen.
	// There are 25 lines each of 80 columns; each element takes 2 bytes.
	while (i < SCREENSIZE) {
		// Blank character.
		vidPtr[i++] = ' ';
		// Attribute-byte - light grey on black screen.
		vidPtr[i++] = 0x07;
	}
	// Position of printing strings starts from the beginning.
	currentPosStr = 0;
	return;
}

// info:
// Moves cursor to the next line.
void jumpNewLine(void)
{
	unsigned int lineSize = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	currentPosStr = currentPosStr + (lineSize - currentPosStr % (lineSize));
	return;
}

// info:
// Prints string and moves cursor to the next line.
void printLine(const char *str)
{
	print(str);
	jumpNewLine();
	return;
}

#endif
