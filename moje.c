#include "libs/glad.h"
#include<GLFW/glfw3.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void leftMovement(float *tab);
void rightMovement(float *tab);
void bottomMovement(float *tab);
void topMovement(float *tab);
void delay(int k);
void spawnFood();

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
    "   FragColor = vec4(1.0f, 0.3f, 0.6f, 1.0f);\n"
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
float board[100][2];
for (int i=0; i<10; i++)
{
	for (int j=0; j<10; j++)
	{
		board[i*10+j][0]=i*(0.1f);
		board[i*10+j][1]=j*(0.1f);
	}
}
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
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
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
int key=0;
int miliseconds = 1000;
while (!glfwWindowShouldClose(window))
{
	processInput(window);
	if (glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS)
	{
		if (key!=1)
			key=0;	
	}
	if (glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS)
	{
		if (key!=0)
			key=1;
	}
	if (glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS)
	{
		if (key!=3)
			key=2;
	}
	if (glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS)
	{
		if (key!=2)
			key=3;
	}
	delay(70);
	switch(key)
	{
		case 0:
		rightMovement(&vertices[0]);
		break;
		case 1:				
		leftMovement(&vertices[0]);
		break;
		case 2:
		bottomMovement(&vertices[0]);
		break;
		case 3:
		topMovement(&vertices[0]);
		break;
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
void leftMovement(float *tab)
{
		tab[0]-=0.1;	// top right
		tab[3]-=0.1;	// bottom right
		tab[6]-=0.1;	// bottom left
		tab[9]-=0.1;	// top left
		if(tab[6]<-1.0f)
		{
		tab[0]=1.0f;
		tab[3]=1.0f;
		tab[6]=0.9f;
		tab[9]=0.9f;
		}
}
void bottomMovement(float *tab)
{
		tab[1]-=0.1;	// top right
		tab[4]-=0.1;	// bottom right
		tab[7]-=0.1;	// bottom left
		tab[10]-=0.1;	// top left
		if(tab[4]<-1.0f)
		{
		tab[1]=1.0f;
		tab[4]=0.9f;
		tab[7]=0.9f;
		tab[10]=1.0f;
		}
}
void topMovement(float *tab)
{
		tab[1]+=0.1;	// top right
		tab[4]+=0.1;	// bottom right
		tab[7]+=0.1;	// bottom left
		tab[10]+=0.1;	// top left
		if(tab[1]>1.0f)
		{
		tab[1]=-0.9f;
		tab[4]=-1.0f;
		tab[7]=-1.0f;
		tab[10]=-0.9f;
		}
}
void rightMovement(float *tab)
{
		tab[0]+=0.1;	// top right
		tab[3]+=0.1;	// bottom right
		tab[6]+=0.1;	// bottom left
		tab[9]+=0.1;	// top left
		if(tab[3]>1.0f)
		{
		tab[0]=-0.9f;
		tab[3]=-0.9f;
		tab[6]=-1.0f;
		tab[9]=-1.0f;
		}
}
void delay(int k)
{
		int milli_seconds=1000*k;
		clock_t start_time = clock();
		while (clock() < start_time + milli_seconds) 
        ; 
}
void spawnFood()
{
	srand(time(NULL));
	
}
