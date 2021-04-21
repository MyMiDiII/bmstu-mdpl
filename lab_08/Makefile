app : main.c astrcpy.asm
	nasm -f elf64 astrcpy.asm
	gcc -c -masm=intel -o main.o $<
	gcc main.o astrcpy.o -o app

clean:
	rm -rf *.o *.s app