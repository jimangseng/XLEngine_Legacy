#pragma once

#include "Common.h"
#include <vector>
#include "IObject.h"
#include "IRenderable.h"
#include "Resources.h"
#include "iostream"

using namespace DirectX;
using namespace std;
using namespace winrt;

// 버텍스에 들어갈 데이터 구조체
struct Vertex
{
	XL::Math::Vector3 localPosition;
	XL::Math::Vector3 worldPosition;
	XL::Math::Vector4 color;
};

class Cube : public IObject, public IRenderable
{


public:
	float size;
	XL::Math::Vector4 color;

public:
	~Cube() = default;

	Cube(const Cube& _cube) = delete;
	Cube& operator= (const Cube& _cube) = delete;

	Cube(Cube&& _cube)
	{
		size = _cube.size;
		color = _cube.color;
		vertices = std::move(_cube.vertices);
		wPosition = std::move(_cube.wPosition);

		translation = std::move(_cube.translation);
		rotation = std::move(_cube.rotation);
		scale = std::move(_cube.scale);
	}

	Cube()
		: Cube(0.1f, { 1.0f, 1.0f, 1.0f, 1.0f })
	{
	}

	Cube(XL::Math::Vector4 _color)
		: Cube(0.1f, _color)
	{
	}

	Cube(float _size, XL::Math::Vector4 _color )
		: size(_size), color(_color)
	{
		vertices.emplace_back(std::move( Vertex{ {-1.0, 1.0, 0.0f}, {}, color } ));
		vertices.emplace_back(std::move( Vertex{ {1.0, 1.0, 0.0f}, {}, color } ));
		vertices.emplace_back(std::move( Vertex{ {-1.0, -1.0, 0.0f}, {}, color } ));
		vertices.emplace_back(std::move( Vertex{ {1.0, -1.0, 0.0f}, {}, color } ));
		vertices.emplace_back(std::move( Vertex{ {-1.0, 1.0, 1.0f}, {}, color } ));
		vertices.emplace_back(std::move( Vertex{ {1.0, 1.0, 1.0f}, {}, color } ));
		vertices.emplace_back(std::move( Vertex{ {-1.0, -1.0, 1.0f}, {}, color } ));
		vertices.emplace_back(std::move( Vertex{ {1.0, -1.0, 1.0f}, {}, color } ));

		// 이해하기
	}

public:
	vector<Vertex> vertices;
	const int indices[3 * 2 * 6]
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
	XL::Math::Vector3 wPosition;
	
private:
	//XL::Math::Matrix translation;
	//XL::Math::Matrix rotation;
	//XL::Math::Matrix scale;
	
	XMMATRIX translation = XMMatrixIdentity();
	XMMATRIX rotation = XMMatrixIdentity();
	XMMATRIX scale = XMMatrixIdentity();

	XMMATRIX worldMatrix;

public:
	void SetPosition(float x, float y, float z) override;
	void Translate(float x, float y, float z) override;
	//void Yaw(float _angle) override;
	//void Pitch(float _angle) override;
	//void Roll(float _angle) override;
	void Rotate(float x, float y, float z) override;
	void Scale(float x, float y, float z) override;

public:
	void Start() override;
	void Update() override;
	void Finish() override;

/////////////////////////Render 관련
// todo: 자원 생성, 렌더링 관련 로직이 여기 있는 것이 불합리하게 느껴지므로 수정할 것
private:
	XL::D3D11::Resources& resources = XL::D3D11::Resources::GetInstance();

public:
	virtual void Initialize() override;
	virtual void Build() override;
	virtual void RenderUpdate() override;
	virtual void Draw() override;

protected:
	virtual void Bind() override;
	virtual void Unbind() override;

protected:
	virtual void GetD3DResources() override;
	virtual HRESULT BuildVertexBuffer() override;
	virtual HRESULT BuildIndexBuffer() override;
			HRESULT BuildConstantBuffer();
	virtual HRESULT BuildInputLayout() override;
	virtual void BuildShader() override;
};


