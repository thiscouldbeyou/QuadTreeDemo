#include <chrono>
#include <thread>
#include <cstdio>

#include "initialization.hpp"
#include "shaders.hpp"
#include "handle_vbo_update.hpp"

#define SLEEP(FPS) std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS  ));

static GLuint setupVertexArrayObject(GLuint &vbo)
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	const int MAX_NUM_OF_FACES = 384;
	glBufferData(GL_ARRAY_BUFFER, MAX_NUM_OF_FACES * sizeof(Face), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		6 * sizeof(GLfloat),                  // stride
		(void*)0            // array buffer offset
	);

	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		6 * sizeof(GLfloat),                  // stride
		(void*)(3 * sizeof(GLfloat))            // array buffer offset
	);
	return VertexArrayID;
}

static void startShader(GLuint shaderID)
{
	glUseProgram(shaderID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

static void stopShader()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
}

int main(void)
{
	GLFWwindow* window = initialize(720, 720, "QuadTreeDemo");

	GLuint vbo{};
	GLuint VertexArrayID = setupVertexArrayObject(vbo);

	GLuint shader_program = loadShader();

	startShader(shader_program);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int numOfTriangles = regenerateVBO({ mx, my }, vbo);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(Triangle) / sizeof(Vertex) * numOfTriangles);

		glfwSwapBuffers(window);
		glfwPollEvents();

		SLEEP(60);
	}
	stopShader();

	glfwTerminate();
	return 0;
}