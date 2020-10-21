#include "LogConfiguration.h"
#include "Log.h"

int main() {
	LogConfiguration& config = LogConfiguration::getInstance();
	config.SetPath("");
	config.SetMaxSize(1000);

	int n = 10;
	char c = 'A';

	while (1) {
		getchar();
		LOG_INFO("INFO는 - %d %c\n", n, c);
		getchar();
		LOG_DEBUG("디버그는 - %d %c\n", n, c);
		getchar();
		LOG_ERROR("에러는는 - %d %c\n", n, c);
	}
}