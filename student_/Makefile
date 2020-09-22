CC=gcc
STD=-std=gnu99
BIN=xt.bin
FLAG=-Wall -Werror -DDEBUG
OBJ=main.o main_s.o main_t.o main_m.o student.o teacher.o master.o change.o

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ)

main.o:main.c main_s.h main_t.h main_m.h
	$(CC) $(STD) $(FLAG) -c main.c
	
main_s.o:main_s.c main_s.h student.h change.h 
	$(CC) $(STD) $(FLAG) -c main_s.c

main_t.o:main_t.c main_t.h teacher.h change.h 
	$(CC) $(STD) $(FLAG) -c main_t.c
	
	
main_m.o:main_m.c main_m.h master.h change.h 
	$(CC) $(STD) $(FLAG) -c main_m.c	
	
	
student.o:student.c student.h change.h 
	$(CC) $(STD) $(FLAG) -c student.c

teacher.o:teacher.c teacher.h change.h main_t.h
	$(CC) $(STD) $(FLAG) -c teacher.c

master.o:master.c master.h change.h
	$(CC) $(STD) $(FLAG) -c master.c

change.o:change.c change.h
	$(CC) $(STD) $(FLAG) -c change.c

clean:
	rm -rf $(BIN) $(OBJ)

