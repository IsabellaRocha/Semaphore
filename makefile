ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: sem.o write.o
	$(CC) -o sem sem.o
	$(CC) -o write write.o

sem.o: sem.c
	$(CC) -c sem.c

write.o: write.c
	$(CC) -c write.c

clean:
	rm *.o
	rm *~
