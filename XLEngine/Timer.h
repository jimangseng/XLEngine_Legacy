#pragma once
#include <chrono>

using namespace std::chrono;

namespace XL
{
	namespace GamePlay
	{
		class Timer
		{

		public:
			Timer() = default;
			Timer(const Timer& _rhs) = delete;
			Timer& operator=  (const Timer& _rhs) = delete;

		public:

			void Initialize()
			{
				startTime = system_clock::now();
			}

			void Update()
			{
				currentTime = system_clock::now();

				deltaTime = duration<float>(currentTime - prevTime).count();
				time = duration<float>(currentTime - startTime).count();
				frateRate = 1.0f / deltaTime;

				prevTime = currentTime;
			}

		public:
			static float time;
			static float deltaTime;
			static float frateRate;

		private:
			time_point<system_clock, duration<double>> startTime;
			time_point<system_clock, duration<double>> prevTime;
			time_point<system_clock, duration<double>> currentTime;
		};
	}
}