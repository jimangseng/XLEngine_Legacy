#include "Cube.h"
#include "../XLMath/XLMath.h"
#include "DirectXMath.h"
#include "Mesh.h"
#include "Camera.h"

using namespace XL::Math;

XL::GameObjects::Cube::Cube()
	: Cube(0.1f)
{
}

XL::GameObjects::Cube::Cube(float _size)
	: size(_size)
{
	mesh = new XL::Components::Mesh();

	vertices =
	{
		// Front face
		{ { -1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },  // 0
		{ { 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f} },  // 1
		{ {-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f} },  // 2
		{ { 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f} },  // 3

			// Back face
		{ {-1.0f,  1.0f,  0.0f}, {1.0f, 0.0f} },  // 4
		{ { 1.0f,  1.0f,  0.0f}, {0.0f, 0.0f} },  // 5
		{ {-1.0f, -1.0f,  0.0f}, {1.0f, 1.0f} },  // 6
		{ { 1.0f, -1.0f,  0.0f}, {0.0f, 1.0f} },  // 7

			// Top face
		{ {-1.0f,  1.0f,  0.0f}, {1.0f, 0.0f} },  // 8
		{ { 1.0f,  1.0f,  0.0f}, {0.0f, 0.0f} },  // 9
		{ {-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f} },  // 10
		{ { 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f} },  // 11

			// Bottom face (스플릿)
		{ {-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f} },  // 12
		{ { 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f} },  // 13
		{ {-1.0f, -1.0f,  0.0f}, {0.0f, 1.0f} },  // 14
		{ { 1.0f, -1.0f,  0.0f}, {1.0f, 1.0f} },  // 15

			// Left face
		{ {-1.0f,  1.0f,  1.0f}, {1.0f, 0.0f} },  // 16
		{ {-1.0f,  1.0f,  0.0f}, {0.0f, 0.0f} },  // 17
		{ {-1.0f, -1.0f,  1.0f}, {1.0f, 1.0f} },  // 18
		{ {-1.0f, -1.0f,  0.0f}, {0.0f, 1.0f} },  // 19

			// Right face
		{ { 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f} },  // 20
		{ { 1.0f,  1.0f,  0.0f}, {0.0f, 0.0f} },  // 21
		{ { 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f} },  // 22
		{ { 1.0f, -1.0f,  0.0f}, {0.0f, 1.0f} },  // 23
	};

	indices =
	{
		// Front face
		0, 2, 1,  1, 2, 3,

		// Back face
		4, 5, 6,  6, 5, 7,

		// Top face
		8, 10, 9,  9, 10, 11,

		//// Bottom face (스플릿)
		12, 14, 13,  13, 14, 15,

		// Left face
		16, 17, 18,  18, 17, 19,

		// Right face
		20, 22, 21,  21, 22, 23
	};

	inputElementDesc =
	{
		{ "LOCALPOSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	texturePath = TEXT("../Textures/1.jpg");
}

void XL::GameObjects::Cube::Initialize()
{
	for (auto& vertex : vertices)
	{
		vertex.localPosition *= size;
	}

	mesh->SetVertexBufferData(vertices);
	mesh->SetIndexBufferData(indices);
	mesh->SetInputLayout(inputElementDesc);
	mesh->SetTexturePath(texturePath);

	UpdateMatrices();
	mesh->SetMatrix(WVPMatrix);
}

void XL::GameObjects::Cube::Update()
{
	UpdateMatrices();
	mesh->SetMatrix(WVPMatrix);
}

void XL::GameObjects::Cube::Finalize()
{
}

void XL::GameObjects::Cube::UpdateMatrices()
{
	float aspectRatio = static_cast<float>(resources.ScreenWidth / resources.ScreenHeight);

	worldMatrix = XMMatrixMultiply(scale, XMMatrixMultiply(rotation, translation));
	viewMatrix = Camera::viewMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(20.0f, aspectRatio, 0.0001f, 100.0f);

	WVPMatrix = XMMatrixMultiply(worldMatrix, XMMatrixMultiply(viewMatrix, projectionMatrix));
	//WVPMatrix = XMMatrixMultiply(worldMatrix, viewMatrix);

}