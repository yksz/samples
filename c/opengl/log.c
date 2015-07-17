#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

static LogLevel loglevel = LogLevel_Info;

void writeLog(LogLevel level, FILE* fp, const char* file, int line, const char* func, const char* fmt, ...)
{
    if (loglevel > level)
        return;

    time_t timer = time(NULL);
    char time[20];
    tzset();
    strftime(time, sizeof(time), "%Y/%m/%d %H:%M:%S", localtime(&timer));

    switch (level) {
        case LogLevel_Debug:
            fprintf(fp, "%s DEBUG %s:%d:%s: ", time, file, line, func);
            break;
        case LogLevel_Info:
            fprintf(fp, "%s INFO  %s:%d:%s: ", time, file, line, func);
            break;
        case LogLevel_Warn:
            fprintf(fp, "%s WARN  %s:%d:%s: ", time, file, line, func);
            break;
        case LogLevel_Error:
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
