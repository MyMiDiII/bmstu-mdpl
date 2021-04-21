app : main.o tests.o astrcpy.o asmstr.o
	gcc $^ -o $@

main.o : main.c tests.h asmstr.h
	gcc -c $<

tests.o : tests.c tests.h
	gcc -c $<

asmstr.o : asmstr.c asmstr.h
	gcc -c -masm=intel $<

astrcpy.o : astrcpy.asm
	nasm -f elf64 $<

clean:
	rm -rf *.o *.s app