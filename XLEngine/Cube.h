#pragma once

#include "Common.h"
#include <vector>
#include "GameObject.h"
#include "Renderable.h"
#include "Resources.h"

using namespace DirectX;
using namespace std;
using namespace winrt;

namespace XL
{
	namespace GameObjects
	{
		struct Vertex
		{
			XL::Math::Vector3 localPosition;
			XMFLOAT2 UV;
		};

		class Cube : public GameObject, public Components::Renderable<Vertex>
		{
		public:
			Cube();
			~Cube() = default;

			Cube(const Cube& _cube) = delete;
			Cube& operator= (const Cube& _cube) = delete;

			Cube(Cube&& _cube) = default;
			Cube& operator= (Cube&& _cube) = default;

			Cube(float _size);

		public:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void Finalize() override;

		private:
			void UpdateMatrices();

		public:
			float size;

		private:
			XL::Graphics::D3D11::Resources& resources = XL::Graphics::D3D11::Resources::GetInstance();
		};
	}
}