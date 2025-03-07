#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "Renderer.h"
#include "Mesh.h"
#include "Meshes.h"
#include "Box.h"
#include "../Camera/Camera.h"

Renderer* Renderer::m_instance = nullptr;
const float Renderer::border_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };

Renderer::Renderer()
{
	m_success = 0;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);  // Cull back-facing polygons
	glFrontFace(GL_CCW);

	glGenFramebuffers(1, &m_framebuffer_depth);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_depth);

	glGenTextures(1, &m_texture_depth);
	glBindTexture(GL_TEXTURE_2D, m_texture_depth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture_depth, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_light_pos = glm::vec3(2.0f, -4.0f, 1.0f);

	glm::mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	glm::mat4 light_view = glm::lookAt(-m_light_pos, glm::vec3(0.0, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_light_matrix = light_projection * light_view;

	m_program_shadow_mapping_depth = create_program("Shadow Mapping Depth", "../../../assets/glsl/PosVertex.glsl", "../../../assets/glsl/EmptyFragment.glsl");
	m_program_shadow_mapping_shading = create_program("Shadow Mapping Shading", "../../../assets/glsl/ShadowMappingVertex.glsl", "../../../assets/glsl/ShadowMappingFragment.glsl");

	create_box(glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 1.0f, 10.0f));
	create_box(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	create_box(glm::vec3(1.25f, 1.0f, 1.0f), glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}

Renderer::~Renderer()
{
	glDeleteProgram(m_program_shadow_mapping_depth);
	glDeleteProgram(m_program_shadow_mapping_shading);

	glDeleteTextures(1, &m_texture_depth);

	glDeleteFramebuffers(1, &m_framebuffer_depth);



	for (int i = 0; i < m_meshes.size(); ++i)
	{
		delete m_meshes[i];
	}

	m_meshes.clear(); // reduces size
	std::vector<Mesh*>().swap(m_meshes); // reduces capacity to fit size

	for (int i = 0; i < m_boxes.size(); ++i)
	{
		delete m_boxes[i];
	}

	m_boxes.clear();
	std::vector<Box*>().swap(m_boxes);
}

GLuint Renderer::create_program(const std::string program_name, const std::string vertex_shader_path, const std::string fragment_shader_path)
{
	GLuint vertex_shader = 0;
	GLuint fragment_shader = 0;

	vertex_shader = create_shader(vertex_shader_path, GL_VERTEX_SHADER);
	fragment_shader = create_shader(fragment_shader_path, GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &m_success);

	if (!m_success)
	{
		glGetProgramInfoLog(program, 512, nullptr, m_info_log);
		std::cout << "Could not link Program with name: " + program_name + "\nReason: " + m_info_log << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}

GLuint Renderer::create_shader(const std::string path, GLenum gl_shader_type)
{
	GLuint shader = glCreateShader(gl_shader_type);

	std::ifstream file(path, std::ios::ate);

	if (!file.is_open())
	{
		std::cout << "Could not open Shader file at: " << path << std::endl;
		return shader;
	}

	size_t file_size = (size_t)file.tellg();
	std::vector<char> file_content(file_size);
	file.seekg(0);
	file.read(file_content.data(), file_size);

	file.close();

	const char* shader_source = file_content.data();

	glShaderSource(shader, 1, &shader_source, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &m_success);

	if (!m_success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, m_info_log);
		std::cout << "Could not compile Shader with path name: " + path + "\nReason: " + m_info_log << std::endl;
	}
	
	return shader;
}

void Renderer::create_box(glm::vec3 world_position, glm::vec3 world_rotation, glm::vec3 world_scale)
{
	// create a cube mesh
	Mesh* mesh = new Mesh();
	if (mesh->create(cube_vertices_pos_normal, 144, cube_attribute_offsets, 2, cube_indices, 36))
	{
		m_meshes.push_back(mesh);
		Box* box = new Box(m_meshes.size() - 1, world_position, to_radians(world_rotation), world_scale);

		m_boxes.push_back(box);
	}
}

glm::vec3 Renderer::to_radians(glm::vec3 euler_angles)
{
	return euler_angles * glm::vec3(glm::pi<float>() / 180.0f);
}

void Renderer::render(Camera* camera)
{

	// Clear buffer

	glClearColor(0.82f, 0.871f, 0.992f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program_shadow_mapping_depth);

	glUniformMatrix4fv(glGetUniformLocation(m_program_shadow_mapping_depth, "vp"), 1, GL_FALSE, &m_light_matrix[0][0]);

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_depth);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Pass 1 write to depth texture
	for (int i = 0; i < m_boxes.size(); ++i)
	{
		glm::mat4 model = m_boxes[i]->get_model_matrix();
		glUniformMatrix4fv(glGetUniformLocation(m_program_shadow_mapping_depth, "model"), 1, GL_FALSE, &model[0][0]);

		Mesh* mesh = m_meshes[m_boxes[i]->get_mesh_index()];

		glBindVertexArray(mesh->m_VAO);
		glDrawElements(GL_TRIANGLES, mesh->m_num_indices, GL_UNSIGNED_INT, (const void*)0);
		glBindVertexArray(0);
	}

	glUseProgram(m_program_shadow_mapping_shading);

	glm::mat4 vp = camera->get_projection_matrix() * camera->get_view_matrix();
	glUniformMatrix4fv(glGetUniformLocation(m_program_shadow_mapping_shading, "vp"), 1, GL_FALSE, &vp[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(m_program_shadow_mapping_shading, "lightMatrix"), 1, GL_FALSE, &m_light_matrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(m_program_shadow_mapping_shading, "shadowMap"), 0);
	glBindTexture(GL_TEXTURE_2D, m_texture_depth);

	glUniform3fv(glGetUniformLocation(m_program_shadow_mapping_shading, "viewPos"), 1, &((camera->get_position())[0]));

	/*struct Material
	{
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
	};

	struct DirectionalLight
	{
		vec3 direction;

		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
	};*/

	glUniform1f(glGetUniformLocation(m_program_shadow_mapping_shading, "reverseNormals"), -1.0f);

	glUniform3f(glGetUniformLocation(m_program_shadow_mapping_shading, "material.ambient"), 0.3f, 0.3f, 0.3f);
	glUniform3f(glGetUniformLocation(m_program_shadow_mapping_shading, "material.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(m_program_shadow_mapping_shading, "material.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(m_program_shadow_mapping_shading, "material.shininess"), 32.0f);

	glUniform3fv(glGetUniformLocation(m_program_shadow_mapping_shading, "light.direction"), 1, &(-m_light_pos)[0]);
	glUniform3f(glGetUniformLocation(m_program_shadow_mapping_shading, "light.ambient"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(m_program_shadow_mapping_shading, "light.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(m_program_shadow_mapping_shading, "light.specular"), 1.0f, 1.0f, 1.0f);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Pass 2 render objects with shadow
	for (int i = 0; i < m_boxes.size(); ++i)
	{
		glm::mat4 model = m_boxes[i]->get_model_matrix();
		glm::mat4 normal_matrix = glm::transpose(glm::inverse(glm::mat3(model)));
		glUniformMatrix4fv(glGetUniformLocation(m_program_shadow_mapping_shading, "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(glGetUniformLocation(m_program_shadow_mapping_shading, "normalMatrix"), 1, GL_FALSE, &normal_matrix[0][0]);

		Mesh* mesh = m_meshes[m_boxes[i]->get_mesh_index()];

		glBindVertexArray(mesh->m_VAO);
		glDrawElements(GL_TRIANGLES, mesh->m_num_indices, GL_UNSIGNED_INT, (const void*)0);
		glBindVertexArray(0);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

Renderer* Renderer::inst()
{
	if (!m_instance)
	{
		m_instance = new Renderer();
	}

	return m_instance;
}
