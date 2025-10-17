#include "Shader.h"
#include "Texture.h"
#include "Threshold.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

namespace threshold
{
	GLuint vbo{};
	GLuint vao{};
	GLuint ebo{};
	//Vertex vertices[] =
	//{
	//	// positions          // colors           // texture coords
	//	{  0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f }, // top right
	//	{  0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f }, // bottom right
	//	{ -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f }, // bottom left
	//	{ -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f }  // top left 
	//};

	Vertex vertices[] = {
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

		{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

		{ -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

		{ 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },

		{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
		{  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
		{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	const int vertexCount = 36;

	Shader shader;
	Texture texture0;
	Texture texture1;

	const char* vertexPath = "./Resources/vertexShader.glsl";
	const char* fragmentPath = "./Resources/fragmentShader.glsl";

	void init()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

		//glGenBuffers(1, &ebo);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(Vertex), indices, GL_STATIC_DRAW);

		static constexpr GLuint vertex_attr_position = 0;
		static constexpr GLuint vertex_attr_color = 1;
		static constexpr GLuint vertex_attr_texCoord = 2;
		glEnableVertexAttribArray(vertex_attr_position);
		glEnableVertexAttribArray(vertex_attr_color);
		glEnableVertexAttribArray(vertex_attr_texCoord);

		glVertexAttribPointer(vertex_attr_position, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex),
			(const GLvoid*)offsetof(Vertex, position));
		glVertexAttribPointer(vertex_attr_color, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex),
			(const GLvoid*)offsetof(Vertex, color));
		glVertexAttribPointer(vertex_attr_texCoord, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex),
			(const GLvoid*)offsetof(Vertex, texCoord));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		shader.Init(vertexPath, fragmentPath);
		texture0.Init("../Resources/container.jpg");
		texture1.Init("../Resources/awesomeface.png");

		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);
	}

	void update()
	{
		// useless for now
	}

	void draw(Camera& camera)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float time = glfwGetTime();

		for (auto& cubePosition : cubePositions) {
			glm::mat4 viewMatrix = camera.GetMatrix();
			glm::mat4 projMatrix =
				glm::perspective(glm::radians(camera.GetFov()), 4.f / 3.f, 0.1f, 100.f);
			glm::mat4 modelMatrix = glm::mat4(1.f);
			//modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(0.0, 1.0, 0.0));
			modelMatrix = glm::translate(modelMatrix, cubePosition);
			modelMatrix = glm::rotate(modelMatrix, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			//modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f) * std::sinf(time / 10.0), glm::vec3(0.0, 0.0, 1.0));
			//modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0) * std::sinf(time / 10.0));
			shader.SetFloat("time", std::abs(std::sinf(time)));
			shader.SetMatrix("uMVPMatrix", projMatrix * viewMatrix * modelMatrix);
			shader.Use();
			texture0.Use(shader.Get(), "texture0", 0);
			texture1.Use(shader.Get(), "texture1", 1);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
			//glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, NULL);
			glBindVertexArray(0);
		}
	}

	void destroy()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}
}