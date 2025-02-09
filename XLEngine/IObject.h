#pragma once

#include "DirectXMath.h"

using namespace DirectX;

// todo:
class IObject
{
public:
	// 버텍스에 들어갈 데이터 구조체
	struct Vertex
	{
		XMFLOAT3 localPosition;
		XMFLOAT3 worldPosition;
		XMFLOAT4 color;
	};

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Finish() = 0;

public:
	virtual void SetPosition(XMFLOAT3 _value) = 0;
	virtual void Translate(XMFLOAT3 _value) = 0;
	//virtual void Yaw(float _angle) = 0;
	//virtual void Pitch(float _angle) = 0;
	//virtual void Roll(float _angle) = 0;
	virtual void Scale(XMFLOAT3 _value) = 0;

protected:
	XMMATRIX transfom = DirectX::XMMatrixIdentity();
};

