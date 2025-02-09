#pragma once

#include "Common.h"
#include <vector>
#include "IObject.h"
#include "IRenderable.h"
#include "Resources.h"

using namespace DirectX;
using namespace std;
using namespace winrt;

class Cube : public IObject, public IRenderable
{
public:
	float size;
	XMFLOAT4 color;

public:
	Cube(float _size, XMFLOAT4 _color );

	Cube(XMFLOAT4 _color)
		: Cube(0.1f, _color)
	{
	}

	Cube()
		: Cube(0.1f, { 1.0f, 1.0f, 1.0f, 1.0f })
	{	
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


	XMFLOAT3 wPosition{ 0.0f, 0.0f, 0.0f };

public:
	void SetPosition(XMFLOAT3 _value) override;
	void Translate(XMFLOAT3 _value) override;
	//void Yaw(float _angle) override;
	//void Pitch(float _angle) override;
	//void Roll(float _angle) override;
	void Scale(XMFLOAT3 _value) override;

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
	virtual HRESULT BuildInputLayout() override;
	virtual void BuildShader() override;
};


