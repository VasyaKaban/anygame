#pragma once

#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();

	void TimerStart();

	void TimerEnd();

	float GetDeltaT();

	float GetFramesRatio();

private:
	 std::chrono::time_point<std::chrono::high_resolution_clock> start;

	 std::chrono::time_point<std::chrono::high_resolution_clock> end;

	 std::chrono::duration<float> DeltaT;

};



