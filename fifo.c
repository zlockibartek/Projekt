#include <stdio.h>
#include <stdlib.h>

struct Queue
{
	int first, last, size;
	unsigned capacity;
	int* array;
};

struct Queue* createQueue(unsigned capacity)
{
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
	queue->capacity = capacity;
	queue->first = queue->size = 0;
	queue->last = capacity - 1; // This is important, see the push 
	queue->array = (int*) malloc(queue->capacity * sizeof(int));
	return queue;
}
void push(struct Queue* queue, int item)
{
	queue->last = (queue->last + 1)%queue->capacity;
	queue->array[queue->last] = item;
	queue->size = queue->size + 1;
}

int pop(struct Queue* queue)
{
	int item = queue->array[queue->first];
	queue->first = (queue->first + 1)%queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

int first(struct Queue* queue)
{
	return queue->array[queue->first];
}

int last(struct Queue* queue)
{
	return queue->array[queue->last];
}
