all: 
	nasm -f elf32 kernel/kernel.asm -o kernel/kasm.o
	gcc -fno-stack-protector -m32 -c kernel/kernel.c -o kernel/kc.o
	gcc -m32 -c Functions.h -o Functions.o
	gcc -m32 -c utils/Header.h -o utils/Header.o
	gcc -m32 -c drivers/keyboard.h -o drivers/keyboard.o
	ld -m elf_i386 -T kernel/link.ld -o bin/kernel.bin kernel/kasm.o kernel/kc.o
	$(RM) kernel/*.o kernel/*~ utils/*.o ustils/*~ drivers/*.o drivers/*~ *.o *~
clean:
	$(RM) kernel/*.o kernel/*~ utils/*.o utils/*~ drivers/*.o drivers/*~ *.o *~
run:
	qemu-system-i386 -kernel bin/kernel.bin
