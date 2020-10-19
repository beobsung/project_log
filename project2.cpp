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
		//시간적 부분
		YEAR = tm.tm_year + 1900;
		MONTH = tm.tm_mon + 1;
		DAY = tm.tm_mday;
		HOUR = tm.tm_hour;
		MINUTE = tm.tm_min;
		SECOND = tm.tm_sec;	
		//file이름
		file_name = fn;
		func_name =fcn;
		line_num = lnum;
		//뭐가 왔는지
		information = info;
	}
	void write() {
		if (information == "INFO") {
			std::string filePath = "INFO.txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << "[" << information << " " << file_name << " " << func_name << " " << line_num << "] ";
				writeFile << YEAR << '-' << MONTH << '-' << DAY << '-' << HOUR << '-' << MINUTE << '-' << SECOND << std::endl;
				writeFile.close();
			}
		}
		else if (information == "DEBUG") {
			std::string filePath = "DEBUG.txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << "[" << information << " " << file_name << " " << func_name << " " << line_num << "] ";
				writeFile << YEAR << '-' << MONTH << '-' << DAY << '-' << HOUR << '-' << MINUTE << '-' << SECOND << std::endl;
				writeFile.close();
			}
		}
		else if (information == "WARNING") {
			std::string filePath = "WARNING.txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << "[" << information << " " << file_name << " " << func_name << " " << line_num << "] ";
				writeFile << YEAR << '-' << MONTH << '-' << DAY << '-' << HOUR << '-' << MINUTE << '-' << SECOND << std::endl;
				writeFile.close();
			}
		}
		else if (information == "ERROR") {
			std::string filePath = "ERROR.txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << "[" << information << " " << file_name << " " << func_name << " " << line_num << "] ";
				writeFile << YEAR << '-' << MONTH << '-' << DAY << '-' << HOUR << '-' << MINUTE << '-' << SECOND << std::endl;
				writeFile.close();
			}
		}
		else if (information == "CRITICAL") {
			std::string filePath = "CRITICAL.txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << "[" << information << " " << file_name << " " << func_name << " " << line_num << "] ";
				writeFile << YEAR << '-' << MONTH << '-' << DAY << '-' << HOUR << '-' << MINUTE << '-' << SECOND << std::endl;
				writeFile.close();
			}
		}
	}

};

int main() {
	LOG a("INFO", __FILE__, __FUNCTION__,__LINE__);
	a.write();
	LOG a1("DEBUG", __FILE__, __FUNCTION__, __LINE__);
	a1.write();
	LOG a2("WARNING", __FILE__, __FUNCTION__, __LINE__);
	a2.write();
	LOG a3("ERROR", __FILE__, __FUNCTION__, __LINE__);
	a3.write();
	LOG a4("CRITICAL", __FILE__, __FUNCTION__, __LINE__);
	a4.write();

}