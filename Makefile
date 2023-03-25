CPP = gcc
FLAGS = -std=gnu17 -Wall -Wextra

transport: Makefile transport.o receive.o send.o
		$(CPP) $(FLAGS) -o transport receive.o send.o transport.o

receive.o: Makefile receive.c
		$(CPP) $(FLAGS) -c receive.c -o receive.o

send.o: Makefile send.c
		$(CPP) $(FLAGS) -c send.c -o send.o

transport.o: Makefile transport.c transport.h
		$(CPP) $(FLAGS) -c transport.c -o transport.o

clean :
	rm -rf *.o

distclean :
	rm -rf *.o transport