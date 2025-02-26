#pragma once

#include "Mesh.h"

namespace XL
{
	namespace Components
	{
		class IRenderable
		{
		public:
			inline XL::Components::Mesh* GetMesh() { return mesh; }

		public:
			XL::Components::Mesh* mesh = nullptr;
			
			std::vector<UINT> indices;
			std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
			const wchar_t* texturePath;

		};
	}
}