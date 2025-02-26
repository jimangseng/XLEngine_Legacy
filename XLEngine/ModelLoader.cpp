#include <string>
#include <cassert>

#include "Mesh.h"
#include "ModelLoader.h"

ModelLoader::ModelLoader()
{

}

bool ModelLoader::Load(std::string& _path, XL::Components::Mesh* _mesh)
{
	pfile = _path;

	scene = importer.ReadFile(pfile, aiProcess_Triangulate);
	assert(scene);

	meshes = scene->mMeshes;
	assert(meshes);

	vertices = meshes[0]->mVertices;
	numVertices = meshes[0]->mNumVertices;

	aiVector2D texCoords;

	vector<XL::Components::aiVertex> verticesData;

	for (unsigned int i = 0; i < numVertices; ++i)
	{
		texCoords.x = meshes[0]->mTextureCoords[0][i].x;
		texCoords.y = 1 - meshes[0]->mTextureCoords[0][i].y;

		XL::Components::aiVertex tVertex;
		tVertex.vertex = vertices[i];
		tVertex.texCoord = texCoords;

		verticesData.emplace_back(tVertex);
	}

	_mesh->aiVertexdata = verticesData;

	aiFace* faces = meshes[0]->mFaces;
	unsigned int numFaces = meshes[0]->mNumFaces;
	vector<unsigned int> indicesData;


	for (unsigned int i = 0; i < numFaces; i++)
	{
		indicesData.emplace_back(faces[i].mIndices[0]);
		indicesData.emplace_back(faces[i].mIndices[1]);
		indicesData.emplace_back(faces[i].mIndices[2]);
	}

	_mesh->aiIndices = indicesData;


	return false;
}