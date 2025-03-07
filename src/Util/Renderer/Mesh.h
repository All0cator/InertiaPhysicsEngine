#pragma once

#include <GLFW/glfw3.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool create(float* vertices, unsigned int num_vertices,
		unsigned int* attribute_offsets, unsigned int num_attribute_offsets,
		unsigned int* indices, unsigned int num_indices);

	// Prohibit usage of assignment, copy, move constructors
	Mesh& operator=(const Mesh& other) = delete;
	Mesh(const Mesh& other) = delete;
	Mesh(Mesh&& other) = delete;

private:
	
public:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;

	float* m_vertices;
	unsigned int m_num_vertices;
	unsigned int m_num_indices;

private:
	// do not touch indices as they are not copied
	unsigned int* m_indices;
};