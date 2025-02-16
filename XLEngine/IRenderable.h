#pragma once

#include "Mesh.h"

namespace XL
{
	namespace Components
	{
		class IRenderable
		{
		public:
			virtual XL::Components::Mesh* GetMesh() = 0;

		protected:
			XL::Components::Mesh* mesh;

		};
	}
}