#pragma once
#include <chrono>

typedef std::chrono::steady_clock::time_point TimePoint;

TimePoint Start(const char* msg) {
	std::cout << msg << std::endl;
	return std::chrono::high_resolution_clock::now();
}

TimePoint Msg(TimePoint start_time, const char* msg) {
	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << msg << '\n' << duration << '\n';
	start_time = std::chrono::high_resolution_clock::now();
	return std::chrono::high_resolution_clock::now();
}