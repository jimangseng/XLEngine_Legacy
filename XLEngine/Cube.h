#pragma once

#include "Common.h"
#include <vector>
#include "IObject.h"
#include "Resources.h"

using namespace DirectX;
using namespace std;
using namespace winrt;

class Cube : public IObject
{
public:
	// 버텍스에 들어갈 데이터 구조체
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	float size = 0.1f;
	XMFLOAT4 color = { 1.0f, 1.0f, 0.0f, 1.0f };

public:
	Cube(float _size, XMFLOAT4 _color )
		: size(_size), color(_color),
		device(nullptr), deviceContext(nullptr),
		result(NULL)
	{
		vertices.push_back(Vertex{ {-1.0, 1.0, 0.0f}, color });
		vertices.push_back(Vertex{ {1.0, 1.0, 0.0f}, color });
		vertices.push_back(Vertex{ {-1.0, -1.0, 0.0f}, color });
		vertices.push_back(Vertex{ {1.0, -1.0, 0.0f}, color });
		vertices.push_back(Vertex{ {-1.0, 1.0, 1.0f}, color });
		vertices.push_back(Vertex{ {1.0, 1.0, 1.0f}, color });
		vertices.push_back(Vertex{ {-1.0, -1.0, 1.0f}, color });
		vertices.push_back(Vertex{ {1.0, -1.0, 1.0f}, color });
	}
	Cube(XMFLOAT4 _color)
		: Cube(0.1f, _color)
	{

	}

	Cube()
		: Cube(0.1f, { 1.0f, 1.0f, 1.0f, 1.0f })
	{
		
	}



public:

	void GetD3DResources();

	vector<Vertex> vertices;
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

	XMFLOAT3 localPosition{ 0.0f, 0.0f, 0.0f };
	XMFLOAT3 localRotation{ 0.0f, 0.0f, 0.0f };
	XMFLOAT3 localScale{ 0.0f, 0.0f, 0.0f };

public:
	void Translate(XMFLOAT3 _value) override;
	void Rotate(XMFLOAT3 _value) override;
	void Scale(XMFLOAT3 _value) override;

private:
	void UpdateTransform();
	HRESULT BuildVertexBuffer();
	HRESULT BuildIndexBuffer();
	HRESULT BuildInputLayout();
	void BuildShader();

public:
	void Initialize() override;
	void Build() override;
	void Draw() override;

private:
	void Bind();
	void UnBind();

public:

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	/// Buffer, InputLayout
	// Vertex Buffer
	com_ptr<ID3D11Buffer> vertexBuffer;
	vector<ID3D11Buffer*> VBs;

	// Index Buffer
	com_ptr<ID3D11Buffer> indexBuffer;
	vector<ID3D11Buffer*> IBs;

	// Input Layout
	com_ptr<ID3D11InputLayout> inputLayout;

	// vs bytecode
	com_ptr<ID3DBlob> vertexShaderByteCode; // compiled shader bytecodes
	com_ptr<ID3DBlob> pixelShaderByteCode;


	com_ptr<ID3D11VertexShader> vertexShader;
	com_ptr<ID3D11PixelShader> pixelShader;


	HRESULT result;

};


