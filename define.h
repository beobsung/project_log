#include <stdarg.h>

#define LOG_INFO(fmt, ...)  Info(fmt, __VA_ARGS__);
#define LOG_DEBUG(fmt, ...) Debug(fmt, __VA_ARGS__) 
#define LOG_ERROR(fmt, ...) Error(fmt, __VA_ARGS__)

void Info(const char* fmt, ...) {
	char buf[512];
	va_list ptr;
	va_start(ptr, fmt);
	vsprintf_s(buf, fmt, ptr);
	do {
		InfoState s;
		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
	} while (0);
}

void Debug(const char* fmt, ...) {
	char buf[512];
	va_list ptr;
	va_start(ptr, fmt);
	vsprintf_s(buf, fmt, ptr);
	do {
		DebugState s;
		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
	} while (0);
}

void Error(const char* fmt, ...) {
	char buf[512];
	va_list ptr;
	va_start(ptr, fmt);
	vsprintf_s(buf, fmt, ptr);
	do {
		ErrorState s;
		new Log(&s, buf, __FILE__, __FUNCTION__, __LINE__);
	} while (0);
}