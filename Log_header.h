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
