OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
 {
   . = 0x100000;
   .text : { *(.text) }
   .text : { ../drivers/*(.text) }
   .data : { *(.data) }
   .bss  : { *(.bss)  }
 }
