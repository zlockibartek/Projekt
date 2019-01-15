#include "libs/glad.h"
#include<GLFW/glfw3.h>
#include<stdlib.h>
#include<stdio.h>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{

float vertices[]={
       -0.5f, -0.5f,0.0f,
	0.5f, -0.5f,0.0f,
	0.0f,  0.5f,0.0f
};

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

unsigned int VBO;

if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
	fprintf(stderr, "Failed to initiate GLAD\n");
	return -1;
}
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
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

glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

glViewport(0,0,800,600);

while (!glfwWindowShouldClose(window))
{
	processInput(window);

	glClearColor(0.2f,0.3f,0.3f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);
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
