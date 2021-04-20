app : main.c
	gcc -c -masm=intel -o main.o $<
	gcc main.o -o app

clean:
	rm -rf *.o *.s app