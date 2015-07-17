#ifndef LOG_H
#define LOG_H

#include <stdio.h>

typedef enum
{
    LogLevel_Debug,
    LogLevel_Info,
    LogLevel_Warn,
    LogLevel_Error,
} LogLevel;

#define LOG_DEBUG(fmt, ...) writeLog(LogLevel_Debug, stderr, __FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)
#define LOG_INFO(fmt, ...)  writeLog(LogLevel_Info,  stderr, __FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)
#define LOG_WARN(fmt, ...)  writeLog(LogLevel_Warn,  stderr, __FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)
#define LOG_ERROR(fmt, ...) writeLog(LogLevel_Error, stderr, __FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)

void writeLog(LogLevel level, FILE* fp, const char* file, int line, const char* func, const char* fmt, ...);
void setLogLevel(LogLevel level);

#endif /* LOG_H */
