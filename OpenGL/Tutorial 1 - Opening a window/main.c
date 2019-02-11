#include <stdio.h>

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

int main(int argc, char** argv)
{
	const GLint SCREEN_WIDTH = 800;
	const GLint SCREEN_HEIGHT = 600;

	glewExperimental = true;
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!\n");
		return 1;
	}

	// settings
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // we want opengl 3+
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // to make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we don't want the old opengl 

	// window
	GLFWwindow* window = nullptr; // in the accompanying source code, this variable is global for simplicity
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "title", nullptr, nullptr);
	if (!window) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return 1;
	}

	// glew
	glfwMakeContextCurrent(window); // initialize glew
	glewExperimental = true; // needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 1;
	}

	// ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// draw nothing

		// swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	return 0;
}