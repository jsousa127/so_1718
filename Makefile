CC = gcc

OBJ_FILES := $(patsubst ./%.c, obj/%.o, $(wildcard ./*.c))

CFLAGS = -Wall -std=c11 -g

program: setup $(OBJ_FILES)
	$(CC) $(CFLAGS) -o program  $(OBJ_FILES)

setup:
	mkdir -p obj

debug: CFLAGS := -g -O0
debug: program


obj/%.o: ./%.c
	$(CC) $(CFLAGS) -o $@ -c $<

obj/main.o: headers/struct.h headers/parser.h
obj/struct.o: headers/struct.h
obj/parser.o: headers/parser.h headers/struct.h
obj/runner.o: headers/runner.h
obj/utilities.o: headers/utilities.h

clean:
	-@rm -rf obj
	-@rm program


