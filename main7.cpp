#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

//모듈 또는 소스 파일의 어떤 함수, 어떤 위치에서 발생한 정보인지 알수 있어야 한다.
//로깅 정보가 다양한 목적지로 저장 / 전송 될 수 있어야 한다.
//로깅의 출력 레벨을 조정할 수 있어야 한다.
//로깅의 정확한 날짜와 시간을 기록할 수 있어야 한다.
//로깅을 날짜별 시간별로 다른 파일로 기록할 것.
//로그 파일이 지정된 크기를 넘어설 경우, 자동으로 다른 파일에 기록할 수 있어야 한다.


#define LOG(WHAT,MESSAGE)  new Log(WHAT,MESSAGE, __FILE__, __FUNCTION__, __LINE__);
#define INFO &is
#define DEBUG &ds
#define ERROR &es

//////////////////////////////////////////////////////////////////////

class LogConfiguration {
	std::string path;
	int maxSize;
	LogConfiguration(const LogConfiguration&) = delete;
	LogConfiguration& operator=(const LogConfiguration&) = delete;

public:
	static LogConfiguration& getInstance() {
		static LogConfiguration instance;
		return instance;
	}

	LogConfiguration() : path(""), maxSize(300) {}
	void SetMaxSize(int size);
	void SetPath(const std::string& p);
	std::string GetPath() const;
	int GetMaxSize() const;
};
//----------------------------------------------------------
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
//////////////////////////////////////////////////////////////////////
class TimeStamp {
public:
	static std::string current();
};
//----------------------------------------------------------
std::string TimeStamp::current() {
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;

	char buf[512];
	sprintf(buf, "%d.%d.%d_%dh%dmin%dsec",
		year, month, day, hour, minute, second
	);
	return buf;
}
//////////////////////////////////////////////////////////////////////

struct IState {
	virtual ~IState() {}
	virtual std::string getLevelString() const = 0;

};
class InfoState : public IState {
public:
	std::string getLevelString() const override {
		return "INFO";
	}
};
class DebugState : public IState {
public:
	std::string getLevelString() const override {
		return "DEBUG";
	}
};

class ErrorState : public IState {
public:
	std::string getLevelString() const override {
		return "ERROR";
	}
};
//////////////////////////////////////////////////////////////////////
class Log {
public:
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

	Log(IState* which, std::string messa, std::string fn, std::string fcn, int lnum) {

		std::string s;
		s = which->getLevelString();


		information = s;
		message = messa;
		file_name = fn;
		func_name = fcn;
		line_num = lnum;

		std::string timestamp = TimeStamp::current();

		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num)
			+ " " + "[" + timestamp + "]" + " <<" + message;   //기록내용
		Command(timestamp);
	}


	void Command(std::string timestamp);
	int GetSize(std::string s);
	void Write(std::string filePath);
	void check_filesize(std::string where, std::string text, int max_size);
};

//----------------------------------------------------------
void Log::Command(std::string timestamp) {
	std::string where_file = LogConfiguration::getInstance().GetPath();
	std::string text_name = information + "_" + "[" + timestamp + "]" + ".txt";

	int max_size = LogConfiguration::getInstance().GetMaxSize();

	check_filesize(where_file, text_name, max_size);
}
int Log::GetSize(std::string s) {

	int size = 0;
	FILE* fp = fopen(s.c_str(), "r");
	if (fp == nullptr) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fclose(fp);
	return size;
}
void  Log::Write(std::string filePath) {
	std::cout << filePath << std::endl;
	FILE* fp = fopen(filePath.c_str(), "a");
	if (fp == nullptr) {
		fprintf(stderr, "File Open Error\n");
	};
	std::cout << log_info << std::endl;
	fprintf(fp, "%s\n", log_info.c_str());
	fflush(fp);

}
void  Log::check_filesize(std::string where, std::string text, int max_size) {
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
//////////////////////////////////////////////////////////////////////

InfoState is;
DebugState ds;
ErrorState es;

int main() {

	LogConfiguration& config = LogConfiguration::getInstance();
	config.SetPath("");
	config.SetMaxSize(1000);
	LOG(DEBUG, "여기 디버그");
	LOG(ERROR, "여기 에러");
	//while (1) {
	//	getchar();
	//	LOG(INFO, "기록남기기");
	//	getchar();
	//	LOG(DEBUG, "여기 디버그");
	//	getchar();
	//	LOG(ERROR, "여기 에러");
	//}
}