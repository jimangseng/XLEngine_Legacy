#pragma once

#include "../XLMath/XLMath.h"
#include "Mesh.h"

using namespace DirectX;

// ���� �����Լ��� ����ϴ��� ����غ� ��
// ��� ������Ʈ�� ���������� �� �����̶�� ������ ���� �ʰ� �����ع����� ���� ����?
namespace XL
{
	namespace GameObjects
	{
		class GameObject
		{
		public:
			// Transform ����
			void SetPosition(float x, float y, float z);
			void Translate(float x, float y, float z);
			void Rotate(float x, float y, float z);
			void Scale(float x, float y, float z);

			// todo: ���� ���̺귯�� �����
			//void Yaw(float _angle);
			//void Pitch(float _angle);
			//void Roll(float _angle);

		public:
			// GameScene ����
			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void Finalize() = 0;

		protected:
			// Transform ���� ��� ������
			XMMATRIX translation = XMMatrixIdentity();
			XMMATRIX rotation = XMMatrixIdentity();
			XMMATRIX scale = XMMatrixIdentity();

			XMMATRIX worldMatrix = XMMatrixIdentity();
			XMMATRIX viewMatrix = XMMatrixIdentity();
			XMMATRIX projectionMatrix = XMMatrixIdentity();

			XMMATRIX WVPMatrix = XMMatrixIdentity();

			// todo: ���� ���̺귯�� �����
			// XL::Math::Matrix translation;
			// XL::Math::Matrix rotation;
			// XL::Math::Matrix scale;
		};
	}
}