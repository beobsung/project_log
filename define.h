#include <stdarg.h>

#define LOG_INFO(fmt, ...)  Info(fmt, __VA_ARGS__);
#define LOG_DEBUG(fmt, ...) Debug(fmt, __VA_ARGS__) 
#define LOG_ERROR(fmt, ...) Error(fmt, __VA_ARGS__)

void Info(const char* fmt, ...);
void Debug(const char* fmt, ...);
void Error(const char* fmt, ...);