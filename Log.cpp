#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include "Log.h"
#include "LogConfiguration.h"

Log::Log(IState* which, std::string messa, std::string fn, std::string fcn, int lnum) {
	information = which->getLevelString();
	message = messa;
	file_name = fn;
	func_name = fcn;
	line_num = lnum;
	std::string timestamp = TimeStamp::current();
	log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num)
		+ " " + "[" + timestamp + "]" + " <<" + message;
	Command(timestamp);
}

void Log::Command(const std::string& timestamp) {
	std::string where_file = LogConfiguration::getInstance().GetPath();
	std::string text_name = information + "_" + "[" + timestamp + "]" + ".txt";
	int max_size = LogConfiguration::getInstance().GetMaxSize();
	Checkfilesize(where_file, text_name, max_size);
}
int Log::GetSize(const std::string& s) {
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

void  Log::Write(const std::string& filePath) {
	FILE* fp = fopen(filePath.c_str(), "a");
	if (fp == nullptr) {
		fprintf(stderr, "File Open Error\n");
	};
	std::cout << log_info << std::endl;
	fprintf(fp, "%s\n", log_info.c_str());
	fflush(fp);

}

void  Log::Checkfilesize(const std::string& where, const std::string& text, const int& max_size) {
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