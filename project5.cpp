#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <map>

//DEBUG,INFO,WARNING,ERROR,CRITICAL

time_t t = time(NULL);
struct tm tm = *localtime(&t);

std::vector<std::string> DEBUG_VECTOR;
std::vector<std::string> INFO_VECTOR;
std::vector<std::string> WARNING_VECTOR;
std::vector<std::string> ERROR_VECTOR;
std::vector<std::string> CRITICAL_VECTOR;


class LOG {
	std::string TOTAL;
	std::string YEAR;
	std::string MONTH;
	std::string DAY;
	std::string HOUR;
	std::string MINUTE;
	std::string SECOND;
	std::string information;
	std::string file_name;
	std::string func_name;
	std::string line_num;
public:
	LOG(std::string info, std::string fn, std::string fcn, int lnum) {
		information = info;
		YEAR = std::to_string(tm.tm_year + 1900);
		MONTH = std::to_string(tm.tm_mon + 1);
		DAY = std::to_string(tm.tm_mday);
		HOUR = std::to_string(tm.tm_hour);
		MINUTE = std::to_string(tm.tm_min);
		SECOND = std::to_string(tm.tm_sec);
		file_name = fn;
		func_name = fcn;
		line_num = std::to_string(lnum);

		//출력값을 다 합침
		TOTAL = "["+information+"] "+ file_name + " "+ func_name + " "+ line_num + " "+
			"[" + YEAR + " " + MONTH + " " + DAY + " " + HOUR + " " + MINUTE + " " + SECOND +"]";
	}

	void Command() {
		if (information == "INFO") {
			INFO_VECTOR.push_back(TOTAL);
			std::string filePath = information + ".txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << TOTAL;
			}
		}
		else if (information == "DEBUG") {
			DEBUG_VECTOR.push_back(TOTAL);
			std::string filePath = information + ".txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << TOTAL;
			}

		}
		else if (information == "WARNING") {
			WARNING_VECTOR.push_back(TOTAL);
			std::string filePath = information + ".txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << TOTAL;
			}
		}
		else if (information == "ERROR") {
			ERROR_VECTOR.push_back(TOTAL);
			std::string filePath = information + ".txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << TOTAL;
			}
		}
		else if (information == "CRITICAL") {
			CRITICAL_VECTOR.push_back(TOTAL);
			std::string filePath = information + ".txt";
			std::ofstream writeFile(filePath.data());
			if (writeFile.is_open()) {
				writeFile << TOTAL;
			}
		}
		std::cout << TOTAL << std::endl;
	}


};

int main() {
	LOG a("INFO", __FILE__, __FUNCTION__, __LINE__);
	a.Command();
	a.Command();
	a.Command();

	LOG a1("DEBUG", __FILE__, __FUNCTION__, __LINE__);
	a1.Command();
	LOG a2("WARNING", __FILE__, __FUNCTION__, __LINE__);
	a2.Command();
	LOG a3("ERROR", __FILE__, __FUNCTION__, __LINE__);
	a3.Command();
	LOG a4("CRITICAL", __FILE__, __FUNCTION__, __LINE__);
	a4.Command();

}