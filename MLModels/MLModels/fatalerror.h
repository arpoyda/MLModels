#pragma once
#include <iostream>
#include <exception>


inline void fatal_error(std::string msg) {
	std::cout << "Fatal Error: " << msg << "\n";
	std::terminate();
}
