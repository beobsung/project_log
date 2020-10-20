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


int GetSize(std::string s) {

	int size = 0;
	FILE* fp = fopen(s.c_str(), "r");
	if (fp == nullptr) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);    // ���� �����͸� ������ ������ �̵���Ŵ
	size = ftell(fp);          // ���� �������� ���� ��ġ�� ����

	fclose(fp);
	return size;
}


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

	void Command() {
		std::cout << log_info << std::endl;
		check_filesize(text_name);

	}

	void Write(std::string filePath) {   //�Է�
		FILE* fp = fopen(filePath.c_str(), "a");
		if (fp == nullptr) {
			fprintf(stderr, "File Open Error\n");
		};
		fprintf(fp, "%s\n", log_info.c_str());
		fflush(fp);


	}
	void check_filesize(std::string text) {  //���Ͽ뷮 ����
		int rev = 0;
		while (1) {
			std::string make_text = std::to_string(rev) + "." + text_name;
			std::string where_save = wherefile + make_text;
			if (GetSize(where_save) < 300) {
				Write(where_save);
				break;
			}
			rev += 1;
		}
	}

};

void Factory(int which_log, std::string message ,const char* filename, const char* funcname, const int& linenum) {
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

	std::string wherefile ="C:\\Users\\M\\Desktop\\pro\\";    //���� ��ġ ����

	Log* m = new Log(s, message, wherefile, filename, funcname, linenum);
	m->Command();
}


int main() {

	while (1) {
		getchar();
		LOG(INFO,"���� ����");
		getchar();
		LOG(DEBUG,"���� �����");
		getchar();
		LOG(ERROR,"���� ����");
	}
}