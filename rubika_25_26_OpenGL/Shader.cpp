#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader() : ProgramID(0U)
{

}

Shader::~Shader()
{
	glDeleteProgram(ProgramID);
}

// Read both file to init the vertex shader and the fragment shader
bool Shader::Init(const char* vertexPath, const char* fragmentPath)
{
	GLuint vertexShader;
	GLuint fragmentShader;

	std::ifstream vertexShaderFile(vertexPath);
	if (!vertexShaderFile.is_open()) {
		std::cerr << "Failed to open file: " << vertexPath << '\n';
		return false;
	}

	std::string vertexShaderSourceString{ std::istreambuf_iterator<char>(vertexShaderFile), std::istreambuf_iterator<char>() };

	const char* vertexShaderSource = vertexShaderSourceString.c_str();

	std::ifstream fragmentShaderFile(fragmentPath);
	if (!fragmentShaderFile.is_open()) {
		std::cerr << "Failed to open file: " << fragmentPath << '\n';
		return false;
	}

	std::string fragmentShaderSourceString{ std::istreambuf_iterator<char>(fragmentShaderFile), std::istreambuf_iterator<char>() };

	const char* fragmentShaderSource = fragmentShaderSourceString.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShader);
	glAttachShader(ProgramID, fragmentShader);
	glLinkProgram(ProgramID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	vertexShaderFile.close();
	fragmentShaderFile.close();

	return true;
}

// Use the corresponding program
void Shader::Use()
{
	glUseProgram(ProgramID);
}

GLuint Shader::Get()
{
	return ProgramID;
}

void Shader::SetInt(const std::string& name, int value) const
{
	GLint location = glGetUniformLocation(ProgramID, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	GLint location = glGetUniformLocation(ProgramID, name.c_str());
	glUniform1f(location, value);
}

void Shader::SetMatrix(const std::string& name, glm::mat4 value) const
{
	GLint location = glGetUniformLocation(ProgramID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}