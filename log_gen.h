/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/**@file main.c 
 * @author Diogo Coelho
 * @version 1.0
 * @date 6 de janeiro de 2024, 09:49
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

/**
 * @brief Prints the string with the log severity name
 * @param level Severity level value
 * @return Returns the string with the severity level name
 */
char* print_severity(LogLevel level);

/**
 * @brief Prints a message to the log file
 * @param msg Message to be printed
 * @param level Severity level of the message
 * @param filename Log file where the message will be written
 */
void logMsg(char *msg, LogLevel level, char *filename);

#endif /* LOG_GEN_H */

