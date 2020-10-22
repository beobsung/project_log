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
	std::string loginfo;
	std::string information;
	std::string filename;
	std::string funcname;
	std::string message;
	int linenum;
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