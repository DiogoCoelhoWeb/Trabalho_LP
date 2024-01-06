/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   log_gen.h
 * Author: Diogo Coelho
 *
 * Created on 6 de janeiro de 2024, 09:49
 */

#ifndef LOG_GEN_H
#define LOG_GEN_H

#define LOG_FILE "./logs/log.txt"

typedef enum {
    EMERGENCY,
    ALERT,
    CRITICAL,
    ERROR,
    WARNING,
    INFORMATIONAL,
    DEBUG,
    NOLEVEL
} LogLevel;

char* print_severity(LogLevel level);

void logMsg(char *msg, LogLevel level, char *filename);

#endif /* LOG_GEN_H */

