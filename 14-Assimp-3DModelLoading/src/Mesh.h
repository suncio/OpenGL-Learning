#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <vector>

#include "Shader.h"

struct MeshVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct MeshTexture
{
	GLuint id;
	// aiTextureType type;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	//Mesh() : VAOId(0), VBOId(0), EBOId(0) {}
	Mesh(std::vector<MeshVertex> vertData,
		std::vector<GLuint> indices,
		std::vector<MeshTexture> textures);

	void draw(Shader& shader) const;
	void final() const;

private:
	std::vector<MeshVertex> vertData;
	std::vector<GLuint> indices;
	std::vector<MeshTexture> textures;
	//  render data
	GLuint VAO, VBO, EBO;

	void setupMesh();
};

#endif 