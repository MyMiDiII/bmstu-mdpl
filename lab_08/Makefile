app : main.c asmstrcpy.asm
	nasm -f elf64 asmstrcpy.asm
	gcc -c -masm=intel -o main.o $<
	gcc main.o asmstrcpy.o -o app

clean:
	rm -rf *.o *.s app