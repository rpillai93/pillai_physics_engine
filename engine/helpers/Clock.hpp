#pragma once
#include <chrono>
#include <iostream>
class Clock {
public:

	void start() {
		m_StartTime = std::chrono::high_resolution_clock::now();
	}

	void stop() {
		m_StopTime = std::chrono::high_resolution_clock::now();
		m_Timer = std::chrono::duration<float>(m_StopTime - m_StartTime).count();
	}

	float GetTimerInSeconds() {
		return m_Timer;
	}

	float GetFps() {
		return (float)1e9 / (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(m_StopTime - m_StartTime).count());
	}

private:
	std::chrono::steady_clock::time_point m_StartTime;
	std::chrono::steady_clock::time_point m_StopTime;
	float m_Timer = 0.0f;
};