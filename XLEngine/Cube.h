#pragma once

#include <vector>
#include <DirectXMath.h>



class Cube
{
public :
	// 버텍스에 들어갈 데이터 구조체
	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};

	// 한 변의 길이
	float tSize = 0.1f;

	// 버텍스 컬러
	DirectX::XMFLOAT4 tColor = { 1.0f, 1.0f, 0.0f, 1.0f };

public:
	Cube()
	{
		vertices.push_back(Vertex{ {-tSize, tSize, 0.0f}, tColor });
		vertices.push_back(Vertex{ {tSize, tSize, 0.0f}, tColor });
		vertices.push_back(Vertex{ {-tSize, -tSize, 0.0f}, tColor });
		vertices.push_back(Vertex{ {tSize, -tSize, 0.0f}, tColor });
		vertices.push_back(Vertex{ {-tSize, tSize, 1.0f}, tColor });
		vertices.push_back(Vertex{ {tSize, tSize, 1.0f}, tColor });
		vertices.push_back(Vertex{ {-tSize, -tSize, 1.0f}, tColor });
		vertices.push_back(Vertex{ {tSize, -tSize, 1.0f}, tColor });
	}

private:

	std::vector<Vertex> vertices;
	int indices[3 * 2 * 6]
	{
		0, 3, 2,
		0, 1, 3,

		0, 4, 1,
		4, 5, 1,

		3, 1, 7,
		1, 5, 7,

		4, 0, 6,
		6, 0, 2,

		5, 4, 7,
		7, 4, 6,

		6, 2, 3,
		6, 3, 7
	};

private:
	int VBSize = 0;
	int IBSize = 0;

public:
	int GetVBSize();
	int GetIBSize();

	const void* GetVBData();
	const void* GetIBData();
};



