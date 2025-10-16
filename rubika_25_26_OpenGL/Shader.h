#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();

	// Read both file to init the vertex shader and the fragment shader
	bool Init(const char* vertexPath, const char* fragmentPath);

	// Use the corresponding program
	void Use();

	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

private:
	GLuint ProgramID;
};