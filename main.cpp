#include "LogConfiguration.h"
#include "Log.h"
#include "define.h"

int main() {
	LogConfiguration& config = LogConfiguration::getInstance();
	config.SetPath("");  //파일 저장경로 세팅
	config.SetMaxSize(1000); //파일 저장 최대 사이즈 세팅

	int n = 99;

	LOG_INFO("INFO : 확인 필요");
	//LOG_DEBUG("디버그는 %d번줄에서 수행", n);
	//LOG_ERROR("여기에서 에러");

}