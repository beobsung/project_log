#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

//DEBUG,INFO,WARING,ERROR,CRITICAL

//정책 : 파일 저장위치
//DEBUG,INFO를 같은 파일
//날짜별로 저장할지,파일 용량별로 저장할지


//Day1_요구사항 기능을 구현하자


void LOG(std::string info) {
	std::string filePath = "test.txt";

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int YEAR = tm.tm_year + 1900;
	int MONTH = tm.tm_mon + 1;
	int DAY = tm.tm_mday;
	int HOUR = tm.tm_hour;
	int MINUTE = tm.tm_min;
	int SECOND = tm.tm_sec;


	std::ofstream writeFile(filePath.data());
	if (writeFile.is_open()) {
		writeFile << YEAR <<'-'<< MONTH << '-' << DAY << '-' << HOUR << '-' << MINUTE << '-' << SECOND;

		writeFile.close();
	}
}

int main(){
	
	LOG("abc");

}