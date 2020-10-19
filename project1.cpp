#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

//DEBUG,INFO,WARING,ERROR,CRITICAL

time_t t = time(NULL);
struct tm tm = *localtime(&t);


class LOG {
	int YEAR;
	int MONTH;
	int DAY;
	int HOUR;
	int MINUTE;
	int SECOND;
	std::string information;
	std::string file_name;
	std::string func_name;
	int line_num;
public:
	LOG(std::string info, std::string fn,std::string fcn,int lnum) {
		YEAR = tm.tm_year + 1900;
		MONTH = tm.tm_mon + 1;
		DAY = tm.tm_mday;
		HOUR = tm.tm_hour;
		MINUTE = tm.tm_min;
		SECOND = tm.tm_sec;	
		information = info;
		file_name = fn;
		func_name =fcn;
		line_num = lnum;
	}
	void write() {
		std::string filePath = "test.txt";

		// write File
		std::ofstream writeFile(filePath.data());
		if (writeFile.is_open()) {
			writeFile << information << '-' << file_name << '-' << func_name << '-' << line_num << '-';
			writeFile << YEAR << '-' << MONTH << '-' << DAY << '-' << HOUR << '-' << MINUTE << '-' << SECOND << std::endl;
			writeFile.close();
		}

	}

};


int main() {
	LOG a("DEBUG", __FILE__, __FUNCTION__,__LINE__);
	a.write();

}