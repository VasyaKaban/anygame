#include "Timer.h"
#include <chrono>

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::TimerStart()
{
	start = std::chrono::high_resolution_clock::now();
}

void Timer::TimerEnd()
{
	end = std::chrono::high_resolution_clock::now();
	DeltaT = end - start;
	DeltaT = DeltaT * 1000;
}

float Timer::GetDeltaT()
{
	return DeltaT.count();
}

float Timer::GetFramesRatio()
{
	return 20.0f / DeltaT.count();
}