#pragma once

#include "XLMath.h"

using namespace DirectX;

// 순수 가상함수를 써야하는지 고민해볼 것
// 모든 오브젝트에 공통적으로 들어갈 로직이라면 오히려 쓰지 않고 정의해버리는 것이 좋다?
namespace XL
{
	namespace GameObjects
	{
		class GameObject
		{
		public:
			// Transform 관련
			// 자식 클래스에서 상속받아 사용
			virtual void SetPosition(float x, float y, float z);
			virtual void Translate(float x, float y, float z);
			virtual void Rotate(float x, float y, float z);
			virtual void Scale(float x, float y, float z);

			// todo: 수학 라이브러리 만들기
			//virtual void Yaw(float _angle);
			//virtual void Pitch(float _angle);
			//virtual void Roll(float _angle);

		public:
			// GameScene 관련
			virtual void InitializeGameObject() = 0;
			virtual void UpdateGameObject() = 0;
			virtual void FinalizeGameObject() = 0;

		protected:
			// Transform 관련 멤버 변수들
			XMMATRIX translation = XMMatrixIdentity();
			XMMATRIX rotation = XMMatrixIdentity();
			XMMATRIX scale = XMMatrixIdentity();

			XMMATRIX worldMatrix = XMMatrixIdentity();
			XMMATRIX viewMatrix = XMMatrixIdentity();
			XMMATRIX projectionMatrix = XMMatrixIdentity();

			XMMATRIX WVPMatrix = XMMatrixIdentity();

			// todo: 수학 라이브러리 만들기
			// XL::Math::Matrix translation;
			// XL::Math::Matrix rotation;
			// XL::Math::Matrix scale;
		};
	}
}