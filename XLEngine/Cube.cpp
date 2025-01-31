#include "Cube.h"

int Cube::GetVBSize()
{
	return vertices.size() * sizeof(Vertex);
}

int Cube::GetIBSize()
{
	return sizeof(indices);
}

const void* Cube::GetVBData()
{
	return vertices.data();
}

const void* Cube::GetIBData()
{
	return indices;
}
