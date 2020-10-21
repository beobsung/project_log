#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <stdarg.h>
#include "Timestamp.h"

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

	Log(IState* which, std::string messa, std::string fn, std::string fcn, int lnum);
	void Command(const std::string& timestamp);
	int GetSize(const std::string& s);
	void Write(const std::string& filePath);
	void Checkfilesize(const std::string& where, const std::string& text, const int& max_size);
};



//void Info(const char* fmt, ...) {
//	char buf[512];
//	va_list ptr;
//	va_start(ptr, fmt);
//	vsprintf_s(buf, fmt, ptr);
//	do {
//		InfoState s;
//		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
//	} while (0);
//}
//
//void Debug(const char* fmt, ...) {
//	char buf[512];
//	va_list ptr;
//	va_start(ptr, fmt);
//	vsprintf_s(buf, fmt, ptr);
//	do {
//		DebugState s;
//		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
//	} while (0);
//}
//
//void Error(const char* fmt, ...) {
//	char buf[512];
//	va_list ptr;
//	va_start(ptr, fmt);
//	vsprintf_s(buf, fmt, ptr);
//	do {
//		ErrorState s;
//		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
//	} while (0);
//}
//
//#define LOG_INFO(fmt, ...)  Info(fmt, __VA_ARGS__)
//#define LOG_DEBUG(fmt, ...) Debug(fmt, __VA_ARGS__)
//#define LOG_ERROR(fmt, ...) Error(fmt, __VA_ARGS__)
