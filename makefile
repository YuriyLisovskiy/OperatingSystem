all: 
	nasm -f elf32 kernel/kernel.asm -o kernel/kasm.o
	gcc -m32 -c kernel/kernel.c -o kernel/kc.o
	gcc -m32 -c Functions.h -o Functions.o
	ld -m elf_i386 -T kernel/link.ld -o bin/kernel kernel/kasm.o kernel/kc.o
	qemu-system-i386 -kernel bin/kernel
	$(RM) kernel/*.o kernel/*~ *.o *~
clean:
	$(RM)bin/kernel kernel/*.o kernel/*~ *.o *~
