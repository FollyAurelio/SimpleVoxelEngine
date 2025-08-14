#include <iostream>
#include "gfx.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyboard_callback(GLFWwindow* window, int key, int scanecode, int action, int mods);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
	if (window == NULL){
		std::cout << ("Failed to create GLFW window\n") << std::endl;
        	glfwTerminate();
        	return -1;
    	}
    	glfwMakeContextCurrent(window);
    	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << ("Failed to initialize GLAD\n") << std::endl;
        	return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyboard_callback);
	glViewport(0, 0, 800, 600);
	float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
			};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	Shader shader("shaders/vertex.vs", "shaders/fragment.fs");
	while (!glfwWindowShouldClose(window)){
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(VAO);
		shader.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboard_callback(GLFWwindow* window, int key, int scanecode, int action, int mods)
{
	if(action == GLFW_PRESS){
		switch(key){
			case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		}
	}
}
	
	
