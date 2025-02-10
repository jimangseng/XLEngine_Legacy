#pragma once

#include "../XLMath/XLMath.h"

using namespace DirectX;

// todo:
class IObject
{
public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Finish() = 0;

public:
	virtual void SetPosition(float x, float y, float z) = 0;
	virtual void Translate(float x, float y, float z) = 0;
	//virtual void Yaw(float _angle) = 0;
	//virtual void Pitch(float _angle) = 0;
	//virtual void Roll(float _angle) = 0;
	virtual void Rotate(float x, float y, float z) = 0;
	virtual void Scale(float x, float y, float z) = 0;

protected:
	XMMATRIX transfom = DirectX::XMMatrixIdentity();
};

