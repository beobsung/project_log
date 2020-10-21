#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

//��� �Ǵ� �ҽ� ������ � �Լ�, � ��ġ���� �߻��� �������� �� �� �־�� �Ѵ�.
//�α� ������ �پ��� �������� ���� / ���� �� �� �־�� �Ѵ�.
//�α��� ��� ������ ������ �� �־�� �Ѵ�.
//�α��� ��Ȯ�� ��¥�� �ð��� ����� �� �־�� �Ѵ�.
//�α��� ��¥�� �ð����� �ٸ� ���Ϸ� ����� ��.
//�α� ������ ������ ũ�⸦ �Ѿ ���, �ڵ����� �ٸ� ���Ͽ� ����� �� �־�� �Ѵ�.

#define LOG_INFO(MESSAGE)  do { InfoState s;  new Log(&s, MESSAGE, __FILE__, __FUNCTION__, __LINE__); } while (0)
#define LOG_DEBUG(MESSAGE) do { DebugState s; new Log(&s, MESSAGE, __FILE__, __FUNCTION__, __LINE__); } while (0)
#define LOG_ERROR(MESSAGE) do { ErrorState s; new Log(&s, MESSAGE, __FILE__, __FUNCTION__, __LINE__); } while (0)

//////////////////////////////////////////////////////////////////////
//�̱���
class LogConfiguration {
	std::string path;
	int maxSize;
	LogConfiguration(const LogConfiguration&) = delete;
	LogConfiguration& operator=(const LogConfiguration&) = delete;
public:
	LogConfiguration() : path(""), maxSize(300) {}
	static LogConfiguration& getInstance();
	void SetMaxSize(int size);
	void SetPath(const std::string& p);
	std::string GetPath() const;
	int GetMaxSize() const;
};
//----------------------------------------------------------
LogConfiguration& LogConfiguration::getInstance() {
	static LogConfiguration instance;
	return instance;
}
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

	Log(IState* which, const std::string& messa, const std::string& fn, const std::string& fcn, const int& lnum) {

		information = which->getLevelString();
		message = messa;
		file_name = fn;
		func_name = fcn;
		line_num = lnum;

		std::string timestamp = TimeStamp::current();

		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num)
			       + " " + "[" + timestamp + "]" + " <<" + message;   //��ϳ���
		Command(timestamp);
	}

	inline void Command(const std::string& timestamp);
	inline int GetSize(const std::string& s);
	inline void Write(const std::string& filePath);
	inline void check_filesize(const std::string& where, const std::string& text, const int& max_size);
};

//----------------------------------------------------------
inline void Log::Command(const std::string& timestamp) {
	std::string where_file = LogConfiguration::getInstance().GetPath();
	std::string text_name = information + "_" + "[" + timestamp + "]" + ".txt";
	int max_size = LogConfiguration::getInstance().GetMaxSize();
	check_filesize(where_file, text_name, max_size);
}
inline int Log::GetSize(const std::string& s) {
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
inline void  Log::Write(const std::string& filePath) {
	FILE* fp = fopen(filePath.c_str(), "a");
	if (fp == nullptr) {
		fprintf(stderr, "File Open Error\n");
	};
	std::cout << log_info << std::endl;
	fprintf(fp, "%s\n", log_info.c_str());
	fflush(fp);

}
inline void  Log::check_filesize(const std::string& where, const std::string& text, const int& max_size) {
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

int main() {

	LogConfiguration& config = LogConfiguration::getInstance();
	config.SetPath("");
	config.SetMaxSize(1000);
	while (1) {
		getchar();
		LOG_INFO("��ϳ����");
		getchar();
		LOG_DEBUG("���� �����");
		getchar();
		LOG_ERROR("���� ����");
	}

}