#include "LogConfiguration_header.h"
#include "Log_header.h"

int main() {

	LogConfiguration& config = LogConfiguration::getInstance();
	config.SetPath("");
	config.SetMaxSize(1000);
	while (1) {
		getchar();
		LOG_INFO("기록남기기");
		getchar();
		LOG_DEBUG("여기 디버그");
		getchar();
		LOG_ERROR("여기 에러");
	}

}