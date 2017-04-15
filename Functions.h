#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

char *vidPtr = (char*)0xb8000;
unsigned int currentPosStr = 0;

void print(const char* str)
{
	unsigned int i = 0;
	
	// This loop writes the string to video memory.
	while(str[i] != '\0')
	{
		// The character's ascii.
		vidPtr[currentPosStr++] = str[i++];
		// Attribute-byte: give character black background and light grey fg.
		vidPtr[currentPosStr++] = 0x02;
	}
	return;
}
void clear(void)
{
	unsigned int i = 0;
	
	// This loop clears the screen.
	// There are 25 lines each of 80 columns; each element takes 2 bytes.
	while(i < SCREENSIZE)
	{
		// Blank character.
		vidPtr[i++] = ' ';
		// Attribute-byte - light grey on black screen.
		vidPtr[i++] = 0x07;
	}
	return;
}
void printNewLine(void)
{
	unsigned int lineSize = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	currentPosStr = currentPosStr + (lineSize - currentPosStr % (lineSize));
}
