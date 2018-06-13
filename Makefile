all: build clean run

install-requirements:
	sudo apt-get install gcc
	sudo apt-get install nasm
	sudo apt-get install qemu-system

build:
	mkdir -p bin
	nasm -f elf32 kernel/kernel.asm -o bin/kasm.o
	gcc -fno-stack-protector -m32 -c kernel/kernel.c -o bin/kc.o
	ld -m elf_i386 -T kernel/link.ld -o bin/kernel bin/kasm.o bin/kc.o

clean:
	rm -r bin/*.o

run:
	qemu-system-i386 -kernel bin/kernel
