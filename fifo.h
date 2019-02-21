struct Queue
{
	int val;
	float vertices[12];
	struct Queue* next;
};
struct Queue* create(int val);
struct Queue* push(struct Queue* queue, int item);
struct Queue* pop(struct Queue* queue);
