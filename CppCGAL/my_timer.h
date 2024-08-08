#pragma once
#include <chrono>
#include <string>
#include <iostream>

typedef std::chrono::steady_clock::time_point TimePoint;

TimePoint start(const char* msg) {
	std::cout << msg;
	return std::chrono::high_resolution_clock::now();
}

void msg(const std::string& msg, TimePoint& start_time, bool rn = false) {
	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << msg << "(mc" << duration << ")";	
	if (rn) {
		std::cout << '\n';
	}
	start_time = std::chrono::high_resolution_clock::now();
}