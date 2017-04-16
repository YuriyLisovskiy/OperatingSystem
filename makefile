all: 
	nasm -f elf32 kernel/kernel.asm -o kernel/kasm.o
	gcc -fno-stack-protector -m32 -c kernel/kernel.c -o kernel/kc.o
	gcc -m32 -c Functions.h -o Functions.o
	gcc -m32 -c utils/Header.h -o utils/Header.o
	gcc -m32 -c drivers/keyboard.h -o drivers/keyboard.o
	ld -m elf_i386 -T kernel/link.ld -o bin/kernel kernel/kasm.o kernel/kc.o
	qemu-system-i386 -kernel bin/kernel
	$(RM)
clean:
	$(RM)bin/kernel kernel/*.o kernel/*~ utils/*.o utils/*~ drivers/*.o drivers/*~ *.o *~
