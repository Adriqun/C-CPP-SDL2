#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

GLFWwindow* init(const GLint* w, const GLint* h, const char* title)
{
	// Initialize Graphics Library Framework
	glewExperimental = true;
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!\n");
		return NULL;
	}

	// Settings
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasting
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // we want opengl 3+
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // to make MacOS happy, should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we don't want the old opengl 

	// Create window
	GLFWwindow* pWindow = glfwCreateWindow(*w, *h, title, NULL, NULL);
	if (!pWindow) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Initialize OpenGL extension Wrangler Library
	glfwMakeContextCurrent(pWindow); // initialize glew
	glewExperimental = true; // needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return NULL;
	}

	return pWindow;
}

char* loadFromFile(const char* path)
{
	// Open file
	FILE* pFile = NULL;
	pFile = fopen(path, "r");
	if (!pFile) {
		fprintf(stderr, "Failed to load file from path %s!\n", path);
		fclose(pFile);
		return NULL;
	}

	// Getting the size of file
	if (fseek(pFile, 0L, SEEK_END) != 0) {
		fprintf(stderr, "Reached END while reading file from path %s!\n", path);
		fclose(pFile);
		return NULL;
	}

	unsigned size = (int)ftell(pFile);
	if (fseek(pFile, 0, SEEK_SET) != 0) {
		fprintf(stderr, "Reached BEGGINING while reading file from path %s!\n", path);
		fclose(pFile);
		return NULL;
	}

	// Read data directly
	char* data = calloc(1, (size + 1));
	if (size < fread(data, sizeof(char), size, pFile)) {
		fprintf(stderr, "Reached END while reading file from path %s!\n", path);
		fclose(pFile);
		return NULL;
	}

	fclose(pFile);
	return data; // ok
}

GLuint loadShaders(const char* v_path, const char* f_path) // vertex shader path to file, fragment shader path to file
{
	// Create shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Buffers
	char* pDataV = NULL;
	char* pDataF = NULL;
	GLuint programID = glCreateProgram();

	// Read data for vertex shader
	if (pDataV = loadFromFile(v_path))
	{
		// Read data for fragment shader
		if (pDataF = loadFromFile(f_path))
		{
			GLint result = GL_FALSE;
			int infoLogLength = 0;

			// Compile Vertex Shader
			printf("Compiling shader : %s\n", v_path);
			glShaderSource(vertexShaderID, 1, &pDataV, NULL);
			glCompileShader(vertexShaderID);

			// Check Vertex Shader
			glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
			glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 1) {
				char* errmsg = malloc(sizeof(char) * (infoLogLength + 1));
				glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, errmsg);
				printf("%s\n", errmsg);
				free(errmsg);
			}
			else {
				// Compile Fragment Shader
				printf("Compiling shader : %s\n", f_path);
				glShaderSource(fragmentShaderID, 1, &pDataF, NULL);
				glCompileShader(fragmentShaderID);

				// Check Fragment Shader
				glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
				glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
				if (infoLogLength > 1) {
					char* errmsg = malloc(sizeof(char) * (infoLogLength + 1));
					glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, errmsg);
					printf("%s\n", errmsg);
					free(errmsg);
				}
				else {
					// Link the program
					printf("Linking program\n");
					glAttachShader(programID, vertexShaderID);
					glAttachShader(programID, fragmentShaderID);
					glLinkProgram(programID);

					// Check the program
					glGetProgramiv(programID, GL_LINK_STATUS, &result);
					glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
					if (infoLogLength > 1) {
						char* errmsg = malloc(sizeof(char) * (infoLogLength + 1));
						glGetShaderInfoLog(programID, infoLogLength, NULL, errmsg);
						printf("%s\n", errmsg);
						free(errmsg);
					}
				}

				// Free fragment shader
				glDetachShader(programID, fragmentShaderID);
				glDeleteShader(fragmentShaderID);
			}

			// Free vertex shader
			glDetachShader(programID, vertexShaderID);
			glDeleteShader(vertexShaderID);
		}
	}

	free(pDataV);
	free(pDataF);
	return programID;
}

int main(int argc, char** argv)
{
	const GLint SCREEN_WIDTH = 800;
	const GLint SCREEN_HEIGHT = 600;
	GLFWwindow* pWindow = NULL;
	const char* title = "Triangle with shaders";
	if (!(pWindow = init(&SCREEN_WIDTH, &SCREEN_HEIGHT, title)))
		return -1;
	
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

	// Load shaders
	GLuint programID = loadShaders("vertex_shader.glsl", "fragment_shader.glsl");

	// ensure we can capture the escape key being pressed below
	glfwSetInputMode(pWindow, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

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
		glfwSwapBuffers(pWindow);
		glfwPollEvents();

	} // check if the ESC key was pressed or the window was closed
	while (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(pWindow) == 0);

	return 0;
}