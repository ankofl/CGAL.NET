#pragma once
#include <iostream>
#include <filesystem>
#include <vector>

void clear_dir(std::string directory) {
	for (const auto& entry : std::filesystem::directory_iterator(directory)) {
		if (entry.is_regular_file() && entry.path().extension() == ".off") {
			std::string file_path = entry.path().string();
			std::filesystem::remove(entry.path());
			std::cout << "removed " << entry.path().filename() << '\n';
		}
	}
}