#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(unsigned int screen_width, unsigned int screen_height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f),
		float pitch = 0.0f, float yaw = -90.0f, float zoom = 45.0f);
	~Camera();

	void move_left(float dt);
	void move_forward(float dt);
	void move_right(float dt);
	void move_backwards(float dt);
	void move_up(float dt);
	void move_down(float dt);

	void rotate_horizontally(float x_offset);
	void rotate_vertically(float y_offset);

	void calculate_direction();
	void calculate_zoom(float scroll_offset);

	void calculate_view_matrix();
	void calculate_projection_matrix();

	glm::mat4 get_view_matrix();
	glm::mat4 get_projection_matrix();

	glm::mat4 calculate_mvp_matrix(glm::mat4 model_matrix=glm::mat4(1.0f));

	glm::vec3 get_position() const;
	glm::vec3 get_direction() const;

	float get_near_plane() const;
	float get_far_plane() const;

	// Prohibit usage of assignment, copy, move constructors
	Camera& operator=(const Camera& other) = delete;
	Camera(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
private:
	float m_aspect_ratio;
	const float m_base_speed = 2.5f;
	glm::vec3 m_position;
	float m_pitch;
	glm::vec3 m_front;
	float m_yaw;
	glm::vec3 m_up;
	float m_zoom;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	float m_near_plane;
	float m_far_plane;

	glm::vec3 m_new_direction;
};