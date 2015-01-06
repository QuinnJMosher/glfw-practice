#include "GL/glew.h"
#include "GL/wglew.h"
#include "GLFW/glfw3.h"

int main() {
	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "hello", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}