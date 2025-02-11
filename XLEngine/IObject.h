#pragma once

#include "XLMath.h"

using namespace DirectX;

// todo: namespace 도입
// 여긴 할 것은 별로 없다
// 순수 가상함수를 써야하는지 고민해볼 것
// 모든 오브젝트에 공통적으로 들어갈 로직이라면 오히려 쓰지 않고 정의해버리는 것이 좋다?
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

