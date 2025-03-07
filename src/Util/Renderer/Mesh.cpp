#include <cstring>
#include <iostream>
#include <GL/glew.h>

#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);

	delete[] m_vertices;
}

bool Mesh::create(float* vertices, unsigned int num_vertices, 
	unsigned int* attribute_offsets, unsigned int num_attribute_offsets, 
	unsigned int* indices, unsigned int num_indices)
{
	if (num_vertices == 0 || num_attribute_offsets == 0 || num_indices == 0)
	{
		std::cout << "Num Vertices or Num Attribute Offsets or Num Indices is 0" << std::endl;
		return false;
	}

	m_vertices = new float[num_vertices];
	std::memcpy((void*)m_vertices, (const void*)vertices, num_vertices * sizeof(float));

	m_indices = indices;

	m_num_vertices = num_vertices;
	m_num_indices = num_indices;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(float), (const void*)vertices, GL_STATIC_DRAW);

	unsigned int vertex_size = 0;
	for (int i = 0; i < num_attribute_offsets; ++i)
	{
		vertex_size += attribute_offsets[i];
	}

	vertex_size *= sizeof(float);

	unsigned int accumulated_stride = 0;

	for (int i = 0; i < num_attribute_offsets; ++i)
	{
		glVertexAttribPointer(i, attribute_offsets[i], GL_FLOAT, GL_FALSE, vertex_size, (const void*)(accumulated_stride * sizeof(float)));
		glEnableVertexAttribArray(i);
		accumulated_stride += attribute_offsets[i];
	}

	// assume there are indices
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(unsigned int), (const void*)indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	return true;
}
