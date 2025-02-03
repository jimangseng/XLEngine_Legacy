#pragma once

#include "DirectXMath.h"

using namespace DirectX;

class IObject
{
public:
	virtual void Initialize() = 0;
	virtual void Build() = 0;
	virtual void Draw() = 0;

public:
	virtual void Translate(XMFLOAT3 _value) = 0;
	virtual void Rotate(XMFLOAT3 _value) = 0;
	virtual void Scale(XMFLOAT3 _value) = 0;

protected:
	XMMATRIX transfom = DirectX::XMMatrixIdentity();
};

