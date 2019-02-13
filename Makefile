# Wpisz "make all", aby skompilowac program
snake:  moje.c snake.c glad.c fifo.c
	gcc moje.c snake.c glad.c fifo.c -o snake -lglfw -lGL -ldl `pkg-config --libs --cflags glfw3`
moje.o: moje.c
snake.o: snake.c
glad.o: glad.c glad.h
fifo.o: fifo.c