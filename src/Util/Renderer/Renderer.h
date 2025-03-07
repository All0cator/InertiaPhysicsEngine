#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <string>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

class Mesh;
class Box;
class Camera;

class Renderer
{
public:
	Renderer();
	~Renderer();


	void render(Camera * camera);

	static Renderer* inst();
private:
	static Renderer* m_instance;
	
	GLuint create_program(const std::string program_name, const std::string vertex_shader_path, const std::string fragment_shader_path);
	GLuint create_shader(const std::string path, GLenum gl_shader_type);
	
	// position in world metric units and rotation in euler angles, degrees
	void create_box(glm::vec3 world_position, glm::vec3 world_rotation, glm::vec3 world_scale);

	glm::vec3 to_radians(glm::vec3 euler_angles);

private:
	GLuint m_program_shadow_mapping_depth;
	GLuint m_program_shadow_mapping_shading;
	GLuint m_program_phong_shading;

	GLuint m_texture_depth;

	static const float border_color[];

	GLuint m_framebuffer_depth;

	glm::mat4 m_light_matrix;

	std::vector<Box*> m_boxes;
	std::vector<Mesh*> m_meshes;

	glm::vec3 m_light_pos;

	int m_success;
	char m_info_log[512];
};