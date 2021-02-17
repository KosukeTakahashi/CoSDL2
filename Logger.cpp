#include <string>
#include <iostream>
#include "Logger.h"

void Logger::log(std::string sender, std::string msg) {
	std::cout << "LOG [" << sender << "] :: " << msg << std::endl;
}

void Logger::warn(std::string sender, std::string msg) {
	std::cout << "WRN [" << sender << "] :: " << msg << std::endl;
}
