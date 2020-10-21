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



//�������---------------------------------------------------------------
#define LOG(WHAT,MESSAGE) new Log(WHAT,MESSAGE, __FILE__, __FUNCTION__, __LINE__);

enum level {
	INFO,
	DEBUG,
	ERROR
};

class Log {
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

public:
	Log(int which_log, std::string messa, std::string fn, std::string fcn, int lnum) {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);

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
		information = s;
		message = messa;
		file_name = fn;
		func_name = fcn;
		line_num = lnum;

		year = tm.tm_year + 1900;
		month = tm.tm_mon + 1;
		day = tm.tm_mday;
		hour = tm.tm_hour;
		minute = tm.tm_min;
		second = tm.tm_sec;


		log_info = "[" + information + "] " + file_name + " " + func_name + " " + std::to_string(line_num) + " " +
			"[" + std::to_string(year) + "��" + std::to_string(month) + "��" + std::to_string(day) + "��" + std::to_string(hour) +
			"��" + std::to_string(minute) + "��" + std::to_string(second) + "��" + "]" + " <<" + message;
		Command();
	}

	//�����
	void Command();
	int GetSize(std::string s);
	void Write(std::string filePath);
	void check_filesize(std::string where, std::string text, int max_size);
};
//�����---------------------------------------------------------------

//����� ����----------------------------------------------------------
void Log::Command() {
	std::string where_file = "";

	std::string text_name = information + "_" + "[" + std::to_string(year) + "��" + std::to_string(month) +
		"��" + std::to_string(day) + "��" + "]" + ".txt";
	int max_size = 300;

	check_filesize(where_file, text_name, max_size);
}

int Log::GetSize(std::string s) {

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

void  Log::Write(std::string filePath) {   //�Է�
	FILE* fp = fopen(filePath.c_str(), "a");
	if (fp == nullptr) {
		fprintf(stderr, "File Open Error\n");
	};
	std::cout << log_info << std::endl;
	fprintf(fp, "%s\n", log_info.c_str());
	fflush(fp);

}
void  Log::check_filesize(std::string where, std::string text, int max_size) {  //���Ͽ뷮 ����
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
//����� ��----------------------------------------------------------

int main() {

	while (1) {
		getchar();
		LOG(INFO, "��ϳ����");
		getchar();
		LOG(DEBUG, "���� �����");
		getchar();
		LOG(ERROR, "���� ����");
	}
}