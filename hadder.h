#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

//모듈 또는 소스 파일의 어떤 함수, 어떤 위치에서 발생한 정보인지 알수 있어야 한다.
// OK
//로깅 정보가 다양한 목적지로 저장 / 전송 될 수 있어야 한다.
//OK
//로깅의 출력 레벨을 조정할 수 있어야 한다.
//OK??
//로깅의 정확한 날짜와 시간을 기록할 수 있어야 한다.
//OK
//로깅을 날짜별 시간별로 다른 파일로 기록할 것.
//OK??
//로그 파일이 지정된 크기를 넘어설 경우, 자동으로 다른 파일에 기록할 수 있어야 한다.
//OK

//일단 동작 구현은 어느정도...
//인터페이스 설정이 필요해지고 있다.
//그전데 동작이 잘 되나 계속 확인 필요=>좀더 좋은 동작으로

enum level {
	INFO,
	DEBUG,
	ERROR
};

#define LOG(WHAT,MESSAGE)  Factory(WHAT, MESSAGE ,__FILE__,__FUNCTION__,__LINE__);  


class Log {
	std::string log_info;
	std::string filePath;
	std::string information;
	std::string file_name;
	std::string func_name;
	std::string text_name;
	std::string message;
	std::string wherefile;
	int line_num;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	Log(std::string info, std::string messa,std::string new_filePath, std::string fn, std::string fcn, int lnum) {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		information = info;
		year = tm.tm_year + 1900;
		month = tm.tm_mon + 1;
		day = tm.tm_mday;
		hour = tm.tm_hour;
		minute = tm.tm_min;
		second = tm.tm_sec;
		file_name = fn;
		func_name = fcn;
		line_num = lnum;
		message = messa;
		wherefile = new_filePath;

		text_name = information + "_" + "[" + std::to_string(year) + "년" + std::to_string(month) +
			"월" + std::to_string(day) + "일" + "]" + ".txt";

		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num) + " " +
			"[" + std::to_string(year) + "년" + std::to_string(month) + "월" + std::to_string(day) + "일" + std::to_string(hour) +
			"시" + std::to_string(minute) + "분" + std::to_string(second) + "초" + "]" + " <<"+ message;
	}
	void Command();
	int GetSize(std::string s);
	void Write(std::string filePath);
	void check_filesize(std::string text);
};