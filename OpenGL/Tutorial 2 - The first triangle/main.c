#include <stdio.h>
#include <stdbool.h>

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
	GLFWwindow* window = NULL; // in the accompanying source code, this variable is global for simplicity
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "title", NULL, NULL);
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
	
	// VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	// Give triangle to openGL
	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	// ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3); // starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		// swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	return 0;
}