#ifndef LOG_H
#define LOG_H

#include <stdio.h>

typedef enum
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
} LogLevel;

#define debugLog(fmt, ...) writeLog(LOG_DEBUG, stderr, __FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)
#define infoLog(fmt, ...)  writeLog(LOG_INFO,  stderr, __FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)
#define warnLog(fmt, ...)  writeLog(LOG_WARN,  stderr, __FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)
#define errorLog(fmt, ...) writeLog(LOG_ERROR, stderr, __FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)

void writeLog(LogLevel level, FILE* fp, const char* file, int line, const char* func, const char* fmt, ...);
void setLogLevel(LogLevel level);

#endif /* LOG_H */
