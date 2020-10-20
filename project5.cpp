#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
time_t t = time(NULL);
struct tm tm = *localtime(&t);

#define LOG_INFO     Factory("INFO",__FILE__,__FUNCTION__,__LINE__);  
#define LOG_DEBUG    Factory("DEBUG",__FILE__,__FUNCTION__,__LINE__);
#define LOG_WARNING  Factory("WARNING",__FILE__,__FUNCTION__,__LINE__);
#define LOG_ERROR    Factory("ERROR",__FILE__,__FUNCTION__,__LINE__);

#define LOG(WHAT)                                             \
	std::string s = ##WHAT                                    \
	if(s == "INFO"){                                          \
		Factory("INFO", __FILE__, __func__, __LINE__);        \
	} 



int GetSize(std::string s) {
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


class Log {
	std::string log_info;
	std::string filePath;
	std::string information;
	std::string file_name;
	std::string func_name;
	int line_num;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	Log(std::string info, std::string fn, std::string fcn, int lnum) {
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

		filePath = information + "_" + "[" + std::to_string(year) + "년" + std::to_string(month) +
			"월" + std::to_string(day) + "일" + "]" + ".txt";

		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num) + " " +
			"[" + std::to_string(year) + "년" + std::to_string(month) + "월" + std::to_string(day) + "일" + std::to_string(hour) +
			"시" + std::to_string(minute) + "분" + std::to_string(second) + "초" + "]";
	}

	void Command() {

		Write(filePath);

	}

	void Write(std::string filePath) {
		std::ofstream writeFile(filePath.data(), std::ios::app);
		if (writeFile.is_open()) {
			writeFile << log_info << "\n";
		}
		std::cout << log_info << std::endl;
	}

};

void Factory(const char* which_log, const char* filename, const char* funcname, const int& linenum) {
	Log* m = new Log(which_log, filename, funcname, linenum);
	m->Command();
}


int main() {
	int n;
	std::cout << "반복수 : ";
	std::cin >> n;
	while (n--) {
		LOG(INFO);
	}
}