#pragma once

#include <iostream>
#include <limits>

inline void Exit() {
    std::cout << "Press Enter to exit234...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}