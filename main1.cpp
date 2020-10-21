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



//헤더시작---------------------------------------------------------------
#define LOG(WHAT,MESSAGE) new Log(WHAT,MESSAGE, __FILE__, __FUNCTION__, __LINE__);

enum level {
	INFO,
	DEBUG,
	ERROR
};

class Log {
	std::string log_info;
	std::string information;
	std::string file_name;
	std::string func_name;
	std::string message;
	int line_num;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	Log(int which_log, std::string messa, std::string fn, std::string fcn, int lnum) {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);

		std::string s;
		if (which_log == 0) {
			s = "INFO";
		}
		else if (which_log == 1) {
			s = "DEBUG";
		}
		else if (which_log == 2) {
			s = "ERROR";
		}
		information = s;
		message = messa;
		file_name = fn;
		func_name = fcn;
		line_num = lnum;

		year = tm.tm_year + 1900;
		month = tm.tm_mon + 1;
		day = tm.tm_mday;
		hour = tm.tm_hour;
		minute = tm.tm_min;
		second = tm.tm_sec;


		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num) + " " +
			"[" + std::to_string(year) + "년" + std::to_string(month) + "월" + std::to_string(day) + "일" + std::to_string(hour) +
			"시" + std::to_string(minute) + "분" + std::to_string(second) + "초" + "]" + " <<" + message;
		Command();
	}

	//선언부
	void Command();
	int GetSize(std::string s);
	void Write(std::string filePath);
	void check_filesize(std::string where, std::string text, int max_size);
};
//헤더끝---------------------------------------------------------------

//구언부 시작----------------------------------------------------------
void Log::Command() {
	std::string where_file = "";

	std::string text_name = information + "_" + "[" + std::to_string(year) + "년" + std::to_string(month) +
		"월" + std::to_string(day) + "일" + "]" + ".txt";
	int max_size = 300;

	check_filesize(where_file, text_name, max_size);
}

int Log::GetSize(std::string s) {

	int size = 0;
	FILE* fp = fopen(s.c_str(), "r");
	if (fp == nullptr) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
	size = ftell(fp);          // 파일 포인터의 현재 위치를 얻음

	fclose(fp);
	return size;
}

void  Log::Write(std::string filePath) {   //입력
	FILE* fp = fopen(filePath.c_str(), "a");
	if (fp == nullptr) {
		fprintf(stderr, "File Open Error\n");
	};
	std::cout << log_info << std::endl;
	fprintf(fp, "%s\n", log_info.c_str());
	fflush(fp);

}
void  Log::check_filesize(std::string where, std::string text, int max_size) {  //파일용량 관리
	int rev = 0;
	while (1) {
		std::string make_text = std::to_string(rev) + "." + text;
		std::string where_save = where + make_text;
		if (GetSize(where_save) < max_size) {
			Write(where_save);
			break;
		}
		rev += 1;
	}
}
//구언부 끝----------------------------------------------------------

int main() {

	while (1) {
		getchar();
		LOG(INFO, "기록남기기");
		getchar();
		LOG(DEBUG, "여기 디버그");
		getchar();
		LOG(ERROR, "여기 에러");
	}
}