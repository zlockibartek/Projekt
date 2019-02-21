
snake:  main.c snake.h snake.c glad.c fifo.h fifo.c
	gcc main.c snake.h snake.c glad.c fifo.c -o snake -lglfw -lGL -ldl `pkg-config --libs --cflags glfw3`
main.o: main.c
snake.o: snake.c snake.h
glad.o: glad.c glad.h
fifo.o: fifo.c fifo.h
