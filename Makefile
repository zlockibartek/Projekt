# Wpisz "make all", aby skompilowac program
CC=gcc moje.c glad.c -lglfw -lGL -ldl `pkg-config --libs --cflags glfw3`

all: test.o  glad.o
	$(CC) test.o glad.o -o test
test.o
