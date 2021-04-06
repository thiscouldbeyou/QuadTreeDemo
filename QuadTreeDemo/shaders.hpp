#pragma once
#include <vector>
#include <GL/glew.h>

static const char* vsShader = R"(
#version 330 core
		
layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out vec3 out_color;

void main() {
	gl_Position = vec4(position, 1);
	out_color = color;
}
		
)";

static const char* fsShader = R"(
#version 330 core

in vec3 out_color;

out vec4 frag_color;

void main(){

  frag_color = vec4(out_color, 1);

}
		
)";

static GLuint createShader(GLenum type, const char const* src)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint result = GL_FALSE;
	int infolength;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infolength);
	if (infolength > 0) {
		std::vector<char> VertexShaderErrorMessage(infolength + 1);
		glGetShaderInfoLog(shader, infolength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	return shader;

}

static GLuint loadShader()
{
	GLuint vertex = createShader(GL_VERTEX_SHADER, vsShader);
	GLuint fragment = createShader(GL_FRAGMENT_SHADER, fsShader);

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertex);
	glAttachShader(ProgramID, fragment);
	glLinkProgram(ProgramID);

	GLint result = GL_FALSE;
	int infolength;

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infolength);
	if (infolength > 0) {
		std::vector<char> ProgramErrorMessage(infolength + 1);
		glGetProgramInfoLog(ProgramID, infolength, nullptr, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, vertex);
	glDetachShader(ProgramID, fragment);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return ProgramID;
}