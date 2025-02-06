#pragma once

#include "DirectXMath.h"

using namespace DirectX;

class IObject
{
public:
	// 버텍스에 들어갈 데이터 구조체
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Finish() = 0;

public:
	virtual void Translate(XMFLOAT3 _value) = 0;
	virtual void Rotate(XMFLOAT3 _value) = 0;
	virtual void Scale(XMFLOAT3 _value) = 0;

protected:
	XMMATRIX transfom = DirectX::XMMatrixIdentity();
};

