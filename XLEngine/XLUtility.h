#pragma once

#include <iostream>

namespace XL
{
	namespace Utility
	{
		class Debug
		{
		public:
			template <typename T>
			static void Log(T _value)
			{
				std::cout << _value << std::endl;
			}
		};
	}
}
