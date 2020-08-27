#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include "Mesh.h"

#include "stb_image/stb_image.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

// #include "VertexArray.h"
// #include "VertexBuffer.h"
// #include "IndexBuffer.h"

class Model
{
public:
	Model(const char* path, bool gamma = false);
	void draw(Shader& shader) const;

	// model data 
	std::vector<MeshTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

private:
	void loadModel(std::string const &path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh *mesh, const aiScene* scene);
	std::vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif