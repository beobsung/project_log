#include "hadder.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>


void Factory(int which_log, std::string message, const char* filename, const char* funcname, const int& linenum) {
	std::string s;

	if (which_log == 0) {
		s = "INFO";
	}
	else if (which_log == 1) {
		s = "DEBUG";
	}
	else if (which_log == 2) {
		s = "ERROR";
	}

	std::string wherefile = "C:\\Users\\M\\Desktop\\pro\\";    //파일 위치 변경

	Log* m = new Log(s, message, wherefile, filename, funcname, linenum);
	m->Command();
}

int main() {
	LOG(INFO, "여기 인포");
	//while (1) {
	//	getchar();
	//	LOG(INFO, "여기 인포");
	//	getchar();
	//	LOG(DEBUG, "여기 디버그");
	//	getchar();
	//	LOG(ERROR, "여기 에러");
	//}
}