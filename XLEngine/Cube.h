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
	Cube(float _size, XMFLOAT4 _color )
		: size(_size), color(_color)
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


	XMFLOAT3 localPosition{ 0.0f, 0.0f, 0.0f };
	XMFLOAT3 localRotation{ 0.0f, 0.0f, 0.0f };
	XMFLOAT3 localScale{ 0.0f, 0.0f, 0.0f };

public:
	void Translate(XMFLOAT3 _value) override;
	void Rotate(XMFLOAT3 _value) override;
	void Scale(XMFLOAT3 _value) override;

private:
	void UpdateTransform();
;

public:
	void Start() override;
	void Update() override;
	void Finish() override;



/////////////////////////Render ฐüทร

public:
	virtual void Build() override;
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


