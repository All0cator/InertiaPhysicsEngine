#include "Box.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

Box::Box(unsigned int mesh_index, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	m_mesh_index = mesh_index;
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}

Box::~Box()
{
}

unsigned int Box::get_mesh_index()
{
	return m_mesh_index;
}

void Box::set_position(glm::vec3 new_position)
{
	m_position = new_position;
}

void Box::set_rotation(glm::vec3 new_rotation)
{
	m_rotation = new_rotation;
}

glm::vec3 Box::get_position()
{
	return glm::vec3();
}

glm::vec3 Box::get_rotation()
{
	return glm::vec3();
}

void Box::translate(glm::vec3 dx)
{
	m_position += dx;
}

void Box::rotate(glm::vec3 dr)
{
	m_rotation += dr;
}

glm::mat4 Box::get_model_matrix()
{
	return glm::scale(glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(glm::quat(m_rotation)), m_scale);
}
