#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

//��� �Ǵ� �ҽ� ������ � �Լ�, � ��ġ���� �߻��� �������� �˼� �־�� �Ѵ�.
// OK
//�α� ������ �پ��� �������� ���� / ���� �� �� �־�� �Ѵ�.
//OK
//�α��� ��� ������ ������ �� �־�� �Ѵ�.
//OK??
//�α��� ��Ȯ�� ��¥�� �ð��� ����� �� �־�� �Ѵ�.
//OK
//�α��� ��¥�� �ð����� �ٸ� ���Ϸ� ����� ��.
//OK??
//�α� ������ ������ ũ�⸦ �Ѿ ���, �ڵ����� �ٸ� ���Ͽ� ����� �� �־�� �Ѵ�.
//OK

//�ϴ� ���� ������ �������...
//�������̽� ������ �ʿ������� �ִ�.
//������ ������ �� �ǳ� ��� Ȯ�� �ʿ�=>���� ���� ��������

enum level {
	INFO,
	DEBUG,
	ERROR
};

#define LOG(WHAT,MESSAGE)  Factory(WHAT, MESSAGE ,__FILE__,__FUNCTION__,__LINE__);  


class Log {
	std::string log_info;
	std::string filePath;
	std::string information;
	std::string file_name;
	std::string func_name;
	std::string text_name;
	std::string message;
	std::string wherefile;
	int line_num;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	Log(std::string info, std::string messa,std::string new_filePath, std::string fn, std::string fcn, int lnum) {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
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
		message = messa;
		wherefile = new_filePath;

		text_name = information + "_" + "[" + std::to_string(year) + "��" + std::to_string(month) +
			"��" + std::to_string(day) + "��" + "]" + ".txt";

		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num) + " " +
			"[" + std::to_string(year) + "��" + std::to_string(month) + "��" + std::to_string(day) + "��" + std::to_string(hour) +
			"��" + std::to_string(minute) + "��" + std::to_string(second) + "��" + "]" + " <<"+ message;
	}
	void Command();
	int GetSize(std::string s);
	void Write(std::string filePath);
	void check_filesize(std::string text);
};