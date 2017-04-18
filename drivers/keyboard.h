#include "../utils/Header.h"
#include "../Functions.h"

// KEYBOARD_DATA_PORT = 0x60
// KEYBOARD_STATUS_PORT = 0x64
// IDT_SIZE = 256
// INTERRUPT_GATE = 0x8e
// KERNEL_CODE_SEGMENT_OFFSET = 0x08
// ENTER_KEY_CODE = 0x1C

extern unsigned char keyboardMap[128];
extern void keyboardHandler(void);
extern char readPort(unsigned short port);
extern void writePort(unsigned short port, unsigned char data);
extern void loadIdt(unsigned long *idtPtr);

unsigned char keyboardMap[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', 0,	/* Backspace */
  ' ',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
struct IDTEntry
{
	unsigned short int offsetLowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char typeAttr;
	unsigned short int offsetHigherbits;
};
struct IDTEntry IDT[IDT_SIZE];
void kbInit()
{
	// 0xFD is 11111101 - enables only IRQ1 (keyboard)
	writePort(0x21, 0xFD);
	while(1);
	return;
}
void input()
{
	unsigned long keyboardAddress;
	unsigned long idtAddress;
	unsigned long idtPtr[2];
	/* populate IDT entry of keyboard's interrupt */
	keyboardAddress = (unsigned long)keyboardHandler;
	IDT[0x21].offsetLowerbits = keyboardAddress & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].typeAttr = INTERRUPT_GATE;
	IDT[0x21].offsetHigherbits = (keyboardAddress & 0xffff0000) >> 16;
	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/
	/* ICW1 - begin initialization */
	writePort(0x20 , 0x11);
	writePort(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	writePort(0x21 , 0x20);
	writePort(0xA1 , 0x28);
	/* ICW3 - setup cascading */
	writePort(0x21 , 0x00);
	writePort(0xA1 , 0x00);
	/* ICW4 - environment info */
	writePort(0x21 , 0x01);
	writePort(0xA1 , 0x01);
	/* Initialization finished */
	/* mask interrupts */
	writePort(0x21 , 0xff);
	writePort(0xA1 , 0xff);
	/* fill the IDT descriptor */
	idtAddress = (unsigned long)IDT ;
	idtPtr[0] = (sizeof (struct IDTEntry) * IDT_SIZE) + ((idtAddress & 0xffff) << 16);
	idtPtr[1] = idtAddress >> 16 ;
	loadIdt(idtPtr);
	kbInit();
	return;
}
void keyboardHandlerMain()
{
	unsigned char status;
	char keycode;
	/* write EOI */
	writePort(0x20, 0x20);
	status = readPort(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = readPort(KEYBOARD_DATA_PORT);
		if(keycode < 0)
		{
			return;
		}
		else if(keycode == BACKSPACE_KEY_CODE && currentPosStr == 0)
		{
			vidPtr[currentPosStr] = ' ';
		}
		else if(keycode == ENTER_KEY_CODE)
		{
			jumpNewLine();
		}
		else if(keycode == BACKSPACE_KEY_CODE)
		{
			if((currentPosStr % COLUMNS_IN_LINE != 0))
			{
				vidPtr[currentPosStr--] = keyboardMap[(unsigned char) keycode];
				vidPtr[currentPosStr--] = 0x02;
			}
			else
			{
				vidPtr[currentPosStr] = ' ';
			}
		}
		else
		{
			vidPtr[currentPosStr++] = keyboardMap[(unsigned char) keycode];
			vidPtr[currentPosStr++] = 0x02;
		}
	}
	return;
}
