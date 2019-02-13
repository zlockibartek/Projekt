#include "libs/glad.h"
#include<GLFW/glfw3.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Queue
{
	int first, last, size;
	unsigned capacity;
	int* array;
};
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void leftMovement(float *tab,int *tab1,int x);
void rightMovement(float *tab,int *tab1,int x);
void bottomMovement(float *tab,int *tab1,int x);
void topMovement(float *tab,int *tab1,int x);
void spawnFood(int *tab);
struct Queue* createQueue(unsigned capacity);
int isEmpty(struct Queue* queue);
void push(struct Queue* queue, int item);
int pop(struct Queue* queue);
int first(struct Queue* queue);
int last(struct Queue* queue);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.5f, 0.6f, 1.0f);\n"
    "}\n\0";

int main()
{
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

GLFWwindow* window=glfwCreateWindow(800,600,"Learn OpenGL",NULL,NULL);
if (window==NULL)
{
	printf("Failed to create window\n");
	glfwTerminate();
	return -1;
}
glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

float vertices[]={
        -0.9f,  1.0f, 0.0f,  // top right
        -0.9f,  0.9f, 0.0f,  // bottom right
        -1.0f,  0.9f, 0.0f,  // bottom left
        -1.0f,  1.0f, 0.0f   // top left
};
struct Queue* queue = createQueue(400);
push(queue,0);
int board[400]={0}; // board
int xTail,yTail; // tail location
int xHead=0,yHead=0; // head location
unsigned int indices[]={
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
	fprintf(stderr, "Failed to initiate GLAD\n");
	return -1;
}

unsigned int VBO,VAO,EBO;
glGenVertexArrays(1,&VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);
glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STREAM_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STREAM_DRAW);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);

int success;
char infoLog[512];


unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);

glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
if(!success)
{
	glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
	fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED");
}

unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
glCompileShader(fragmentShader);

glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
if(!success)
{
	glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
	fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
}

unsigned int shaderProgram = glCreateProgram();
glAttachShader(shaderProgram,vertexShader);
glAttachShader(shaderProgram,fragmentShader);
glLinkProgram(shaderProgram);

glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success)
{
	glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
	fprintf(stderr,"ERROR::SHADER::ATTACH::FAILED");
}


glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

glViewport(0,0,800,600);
int key=0, last_key=0,isFood=0;
float seconds =0.25;
int timer=0;
float start_time;
while (!glfwWindowShouldClose(window))
{
	if (timer==0)
	{
		start_time=glfwGetTime();
		timer=1;
	}
	for (int i=0; i<20; i++)
	{
		for (int j=0; j<20; j++)
		{
			printf("%d",board[i*20+j]);
		}
		printf("\n");
	}
	printf("\n");
	processInput(window);
	if (glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS) // right movement
	{
		if (last_key!=1)
			key=0;
	}
	if (glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS) // left movement
	{
		if (last_key!=0)
			key=1;
	}
	if (glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS) // bottom movement
	{
		if (last_key!=3)
			key=2;
	}
	if (glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS) // top movement
	{
		if (last_key!=2)
			key=3;
	}
	if (isFood==0){
	spawnFood(&board[0]);
	isFood=1;
	}
	if (glfwGetTime()>start_time+seconds)
	{
	switch(key)
	{
		case 0:
		xHead+=1;
		if (xHead>19)
			xHead=0;
		if (board[yHead*20+xHead]==2)
			isFood=0;
		push(queue,yHead*20+xHead);
		board[first(queue)]=0;
		if (board[yHead*20+xHead]==1)
			glfwSetWindowShouldClose(window,1);
		if (board[yHead*20+xHead]!=2)
			pop(queue);
		rightMovement(&vertices[0],&board[0],yHead*20+xHead);
		break;
		case 1:
		xHead-=1;
		if (xHead<0)
			xHead=19;
		if (board[yHead*20+xHead]==2)
			isFood=0;
		push(queue,yHead*20+xHead);
		board[first(queue)]=0;
		if (board[yHead*20+xHead]==1)
			glfwSetWindowShouldClose(window,1);
		if (board[yHead*20+xHead]!=2)
			pop(queue);
		leftMovement(&vertices[0],&board[0],yHead*20+xHead);
		break;
		case 2:
		yHead+=1;
		if (yHead>19)
			yHead=0;
		if (board[yHead*20+xHead]==2)
			isFood=0;
		push(queue,yHead*20+xHead);
		board[first(queue)]=0;
		if (board[yHead*20+xHead]==1)
			glfwSetWindowShouldClose(window,1);
		if (board[yHead*20+xHead]!=2)
			pop(queue);
		bottomMovement(&vertices[0],&board[0],yHead*20+xHead);
		break;
		case 3:
		yHead-=1;
		if (yHead<0)
			yHead=19;
		if (board[yHead*20+xHead]==2)
			isFood=0;
		push(queue,yHead*20+xHead);
		board[first(queue)]=0;
		if (board[yHead*20+xHead]==1)
			glfwSetWindowShouldClose(window,1);
		if (board[yHead*20+xHead]!=2)
			pop(queue);

		topMovement(&vertices[0],&board[0],yHead*20+xHead);
		break;
	}
	last_key = key;
	timer=0;
	}
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STREAM_DRAW);
	glClearColor(0.2f,0.3f,0.3f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

	glfwSwapBuffers(window);
	glfwPollEvents();

}
	glDeleteBuffers(1,&VBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height);
}
void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
		glfwSetWindowShouldClose(window,1);
}
void spawnFood(int *tab)
{
	int x;
	while (1) {
	x=(int)(glfwGetTime()*400)%400;
	if (tab[x]==0)
		break;
	}
	tab[x]=2;
}
