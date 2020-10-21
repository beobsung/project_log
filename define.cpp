#include <stdarg.h>
#include "Log.h"
#include "LogConfiguration.h"

void Info(const char* fmt, ...) {
	char buf[512];
	va_list ptr;
	va_start(ptr, fmt);
	vsprintf(buf, fmt, ptr);
	do {
		InfoState s;
		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
	} while (0);
}

void Debug(const char* fmt, ...) {
	char buf[512];
	va_list ptr;
	va_start(ptr, fmt);
	vsprintf(buf, fmt, ptr);
	do {
		DebugState s;
		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
	} while (0);
}

void Error(const char* fmt, ...) {
	char buf[512];
	va_list ptr;
	va_start(ptr, fmt);
	vsprintf(buf, fmt, ptr);
	do {
		ErrorState s;
		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
	} while (0);
}