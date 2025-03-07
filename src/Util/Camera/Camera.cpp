#include "Camera.h"

Camera::Camera(unsigned int screen_width, unsigned int screen_height, glm::vec3 position, glm::vec3 direction, float pitch, float yaw, float zoom)
{
	m_near_plane = 0.1f;
	m_far_plane = 100.0f;

	if (screen_height != 0)
	{
		m_aspect_ratio = (float)screen_width / screen_height;
	}
	else
	{
		m_aspect_ratio = 0.0f;
	}

	m_position = position;
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_front = direction;

	m_view = glm::lookAt(position, position + m_front, m_up);

	m_pitch = pitch;
	m_yaw = yaw;
	m_zoom = zoom;

}

Camera::~Camera()
{
}

void Camera::move_left(float dt)
{
	m_position -= m_base_speed * dt * glm::normalize(glm::cross(m_front, m_up));
}

void Camera::move_forward(float dt)
{
	m_position += m_base_speed * dt * m_front;
}

void Camera::move_right(float dt)
{
	m_position += m_base_speed * dt * glm::normalize(glm::cross(m_front, m_up));
}

void Camera::move_backwards(float dt)
{
	m_position -= m_base_speed * dt * m_front;
}

void Camera::move_up(float dt)
{
	m_position += m_base_speed * dt * m_up;
}

void Camera::move_down(float dt)
{
	m_position -= m_base_speed * dt * m_up;
}

void Camera::rotate_horizontally(float x_offset)
{
	m_yaw += x_offset;
}

void Camera::rotate_vertically(float y_offset)
{
	m_pitch += y_offset;

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}

	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}
}

void Camera::calculate_direction()
{
	m_new_direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_new_direction.y = sin(glm::radians(m_pitch));
	m_new_direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(m_new_direction);
}

void Camera::calculate_zoom(float scroll_offset)
{
	m_zoom -= scroll_offset;
	if (m_zoom < 1.0f)
	{
		m_zoom = 1.0f;
	}

	if (m_zoom > 45.0f)
	{
		m_zoom = 45.0f;
	}
}

void Camera::calculate_view_matrix()
{
	m_view = glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::calculate_projection_matrix()
{
	m_projection = glm::perspective(glm::radians(m_zoom), m_aspect_ratio, m_near_plane, m_far_plane);
}

glm::mat4 Camera::get_view_matrix()
{
	calculate_view_matrix();
	return m_view;
}

glm::mat4 Camera::get_projection_matrix()
{
	calculate_projection_matrix();
	return m_projection;
}

glm::mat4 Camera::calculate_mvp_matrix(glm::mat4 model_matrix)
{
	calculate_view_matrix();
	calculate_projection_matrix();
	return m_projection * m_view * model_matrix;
}

glm::vec3 Camera::get_position() const
{
	return m_position;
}

glm::vec3 Camera::get_direction() const
{
	return m_front;
}

float Camera::get_near_plane() const
{
	return m_near_plane;
}

float Camera::get_far_plane() const
{
	return m_far_plane;
}
