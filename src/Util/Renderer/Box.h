#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Box
{
public:
	Box(unsigned int mesh_index, 
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	~Box();

	// Prohibit usage of assignment, copy, move constructors
	Box& operator=(const Box& other) = delete;
	Box(const Box& other) = delete;
	Box(Box&& other) = delete;

	unsigned int get_mesh_index();

	void set_position(glm::vec3 new_position);
	void set_rotation(glm::vec3 new_rotation);

	glm::vec3 get_position();
	glm::vec3 get_rotation();

	void translate(glm::vec3 dx);
	void rotate(glm::vec3 dr);

	glm::mat4 get_model_matrix();

private:
	glm::vec3 m_position;
	unsigned int m_mesh_index;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};