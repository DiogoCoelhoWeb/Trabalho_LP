/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "log_gen.h"

char* print_severity(LogLevel level) {
    switch (level) {
        case EMERGENCY:
            return "EMERGENCY";
        case ALERT:
            return "ALERT";
        case CRITICAL:
            return "CRITICAL";
        case ERROR:
            return "ERROR";
        case WARNING:
            return "WARNING";
        case INFORMATIONAL:
            return "INFORMATIONAL";
        case DEBUG:
            return "DEBUG";
        case NOLEVEL:
            return "";
    }
    return "";
}

void logMsg(char *msg, LogLevel level, char *filename) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    FILE *fp = fopen(filename, "a");

    if (fp == NULL) {
        puts("SYSTEM ERROR: Failed writing to the log!");
        return;
    }

    if (level == NOLEVEL) {
        fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] %s\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, msg);
    } else {
        fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] [%s] %s\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, print_severity(level), msg);
    }


    fclose(fp);
}

