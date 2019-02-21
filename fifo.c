#include <stdio.h>
#include <stdlib.h>

struct Queue
{
	int val;
	float vertices[12];
	struct Queue* next;
};

struct Queue* create(int val)
{
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));	
	queue->val=val;
	queue->next=NULL;
	return queue;
}
struct Queue* push(struct Queue* queue, int item)
{
	struct Queue *new=create(item),*pom;
	if (queue==NULL){
		new->next=queue;
		return new;}
	else {
	pom=queue;
	while (pom->next!= NULL)
	pom=pom->next;
	new->next=pom->next;
	pom->next=new;
	return queue;
	}
}
struct Queue* pop(struct Queue* queue)
{
	struct Queue* pom=queue;
	queue=queue->next;
	free(pom);
	return queue;

}
