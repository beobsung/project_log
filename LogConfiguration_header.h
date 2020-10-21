#include <string>

class LogConfiguration {
	std::string path;
	int maxSize;
	LogConfiguration(const LogConfiguration&) = delete;
	LogConfiguration& operator=(const LogConfiguration&) = delete;

public:
	LogConfiguration() : path(""), maxSize(300) {}
	static LogConfiguration& getInstance();

	void SetMaxSize(int size);
	void SetPath(const std::string& p);
	std::string GetPath() const;
	int GetMaxSize() const;
};