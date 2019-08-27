#include "Timer.h"

Timer::Timer()
{
	last = std::chrono::steady_clock::now();
}

float Timer::Mark()
{
	auto previosTP = last;

	last = std::chrono::steady_clock::now();

	std::chrono::duration<float> elaspsed = last - previosTP;
	return elaspsed.count();
}
