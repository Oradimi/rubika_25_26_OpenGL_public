#include "Shader.h"
#include "Threshold.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

namespace threshold
{
	GLuint vbo{};
	GLuint vao{};
	GLuint ebo{};
	Vertex vertices[] =
	{
		{ 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f },   // bottom right
		{ -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f },	// bottom left
		{ 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f }    // top 
	};
	unsigned int indices[] = {
		0, 1, 2,   // first triangle
	};
	const int vertexCount = 3;

	const int vertexSize = 3;

	Shader shader;

	const char* vertexPath = "./Resources/vertexShader.glsl";
	const char* fragmentPath = "./Resources/fragmentShader.glsl";

	void init()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(Vertex), indices, GL_STATIC_DRAW);

		static constexpr GLuint vertex_attr_position = 0;
		static constexpr GLuint vertex_attr_color = 1;
		glEnableVertexAttribArray(vertex_attr_position);
		glEnableVertexAttribArray(vertex_attr_color);

		glVertexAttribPointer(vertex_attr_position, vertexSize, GL_FLOAT, GL_FALSE,
			sizeof(Vertex),
			(const GLvoid*)offsetof(Vertex, position));
		glVertexAttribPointer(vertex_attr_color, vertexSize, GL_FLOAT, GL_FALSE,
			sizeof(Vertex),
			(const GLvoid*)offsetof(Vertex, color));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		shader.Init(vertexPath, fragmentPath);
	}

	void update()
	{
		// useless for now
	}

	void draw()
	{
		float time = glfwGetTime();
		shader.SetFloat("time", std::abs(std::sinf(time)));
		shader.Use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}

	void destroy()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}
}