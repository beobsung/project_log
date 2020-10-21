#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>
#include <string>
#include "Timestamp.h"

std::string TimeStamp::current() {
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;

	char buf[512];
	sprintf(buf, "%d.%d.%d_%dh%dmin%dsec",
		year, month, day, hour, minute, second
	);
	return buf;
}