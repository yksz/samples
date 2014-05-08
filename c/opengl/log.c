#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

static LogLevel loglevel = LOG_INFO;

void writeLog(LogLevel level, FILE* fp, const char* file, int line, const char* func, const char* fmt, ...)
{
    if (loglevel > level)
        return;

    time_t timer = time(NULL);
    char time[20];
    tzset();
    strftime(time, sizeof(time), "%Y/%m/%d %H:%M:%S", localtime(&timer));

    switch (level) {
        case LOG_DEBUG:
            fprintf(fp, "%s DEBUG %s:%d:%s: ", time, file, line, func);
            break;
        case LOG_INFO:
            fprintf(fp, "%s INFO  %s:%d:%s: ", time, file, line, func);
            break;
        case LOG_WARN:
            fprintf(fp, "%s WARN  %s:%d:%s: ", time, file, line, func);
            break;
        case LOG_ERROR:
            fprintf(fp, "%s ERROR %s:%d:%s: ", time, file, line, func);
            break;
    }

    va_list list;
    va_start(list, fmt);
    vfprintf(fp, fmt, list);
    va_end(list);
}

void setLogLevel(LogLevel level)
{
    loglevel = level;
}
