#include <iostream>
#include "gfx.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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
	glViewport(0, 0, 800, 600);
	while (!glfwWindowShouldClose(window)){
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
	}
	glfwTerminate();
	return 0;
}
