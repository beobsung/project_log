#include "hadder.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>


void Log::Command() {
	std::cout << log_info << std::endl;
	check_filesize(text_name);
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



void  Log::check_filesize(std::string text) {  //���Ͽ뷮 ����
	int rev = 0;
	while (1) {
		std::string make_text = std::to_string(rev) + "." + text_name;
		if (GetSize(where_save) < 300) {
			Write(where_save);
			break;
		}
		rev += 1;
	}
}