#pragma once
#include "Mesh.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class ModelLoader
{
public:
	ModelLoader();

public:
	bool Load(std::string& _path, XL::Components::Mesh* _mesh);

private:
	Assimp::Importer importer;
	std::string pfile;

	const aiScene* scene;
	aiMesh** meshes;
	aiVector3D* vertices;

	unsigned int numVertices;
};

