#include "LogConfiguration.h"

LogConfiguration& LogConfiguration::getInstance() {
	static LogConfiguration instance;
	return instance;
}

void LogConfiguration::SetMaxSize(int size) {
	maxSize = size;
}

void  LogConfiguration::SetPath(const std::string& p) {
	path = p;
}

std::string  LogConfiguration::GetPath() const {
	return path;
}

int LogConfiguration::GetMaxSize() const {
	return maxSize;
}