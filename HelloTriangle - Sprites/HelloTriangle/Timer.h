#pragma once
#include <thread>
#include <chrono>
#include <cTime>

class Timer
{
public:

	Timer() {};

	void Start() { begin = std::chrono::system_clock::now(); }
	void Finish() { end = std::chrono::system_clock::now(); }

	double getElapsedTimeMs()
	{
		std::chrono::duration<double> elapsed_seconds = end - begin;
		return elapsed_seconds.count() * 1000;
	}
	
	
	double getElapsedTime()
	{
		std::chrono::duration<double> elapsed_seconds = end - begin;
		return elapsed_seconds.count();
	}

	double calcWaitingTime(int fps, double elapsedTime) 
	{
		double wt = 1000 / (double)fps - elapsedTime;
		return wt;
	}

protected:
	// Using time point and system_clock
	std::chrono::time_point<std::chrono::system_clock> begin,
		end;

};

