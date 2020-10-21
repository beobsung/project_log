#include <string>
#include "Timestamp_header.h"

#define LOG_INFO(MESSAGE)  do { InfoState s;  new Log(&s, MESSAGE, __FILE__, __FUNCTION__, __LINE__); } while (0)
#define LOG_DEBUG(MESSAGE) do { DebugState s; new Log(&s, MESSAGE, __FILE__, __FUNCTION__, __LINE__); } while (0)
#define LOG_ERROR(MESSAGE) do { ErrorState s; new Log(&s, MESSAGE, __FILE__, __FUNCTION__, __LINE__); } while (0)

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

	Log(IState* which, std::string messa, std::string fn, std::string fcn, int lnum) {   //생성자

		information = which->getLevelString();
		message = messa;
		file_name = fn;
		func_name = fcn;
		line_num = lnum;

		std::string timestamp = TimeStamp::current();

		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num)
			         + " " + "[" + timestamp + "]" + " <<" + message;   //기록내용
		Command(timestamp);
	}

	void Command(const std::string& timestamp);
	int GetSize(const std::string& s);
	void Write(const std::string& filePath);
	void check_filesize(const std::string& where, const std::string& text, const int& max_size);
};

//#include <string>
//#include <iostream>
//using namespace std;
//
//std::string foo(const char* fmt, ...) {
//	char buf[512];
//	va_list ptr;
//	va_start(ptr, fmt);
//
//	vsprintf(buf, fmt, ptr);
//	return buf;
//}
//
//#define FOO(fmt, ...) foo(fmt, __VA_ARGS__)
//
//int main() {
//	int n = 10;
//	char c = 'A';
//
//	std::string s = FOO("hello - %d %c\n", n, c);
//	cout << s << endl;
//}
