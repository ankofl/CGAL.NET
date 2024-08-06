#pragma once
#include <chrono>

typedef std::chrono::steady_clock::time_point TimePoint;

TimePoint Start(const char* msg) {
	std::cout << msg;
	return std::chrono::high_resolution_clock::now();
}

TimePoint Msg(const char* msg, TimePoint start_time) {
	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << msg << "(mc" << duration << ") ";
	start_time = std::chrono::high_resolution_clock::now();
	return std::chrono::high_resolution_clock::now();
}