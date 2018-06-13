bits 32
section .text
		;multiboot spec
		align 4
		dd 0x1BADB002              ;magic number
		dd 0x00                    ;flags
		dd - (0x1BADB002 + 0x00)   ;checksum. m+f+c should be zero

global start
global keyboardHandler
global readPort
global writePort
global loadIdt

extern kmain 		;this is defined in the c file
extern keyboardHandlerMain

readPort:
	mov edx, [esp + 4]
			;al is the lower 8 bits of eax
	in al, dx	;dx is the lower 16 bits of edx
	ret

writePort:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

loadIdt:
	mov edx, [esp + 4]
	lidt [edx]
	sti		;turn on interrupts
	ret

keyboardHandler:                 
	call    keyboardHandlerMain
	iretd

start:
	cli 		;block interrupts
	mov esp, stack_space
	call kmain
;	hlt 		;halt the CPU

section .bss
resb 8192; 8KB for stack
stack_space:
