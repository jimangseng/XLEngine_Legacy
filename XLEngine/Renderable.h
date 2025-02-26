#pragma once

#include "IRenderable.h"

namespace XL
{
	namespace Components
	{
		template <typename TVertex>
		class Renderable : public IRenderable
		{

		public:
			std::vector<TVertex> vertices;

		};
	}
}