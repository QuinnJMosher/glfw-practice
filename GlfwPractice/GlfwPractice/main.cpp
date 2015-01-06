#include <GLFW/glfw3.h>

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

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}