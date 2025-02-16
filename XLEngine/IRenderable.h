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

		protected:
			XL::Components::Mesh* mesh;

		};
	}
}