/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <string.h>

#include "utilities.h"

#define INVALID_MESSAGE "Invalid value"

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int getInt(int min_value, int max_value, char *msg) {
    int value;
    printf(msg);
    while (scanf("%d", &value) != 1 || value < min_value || value > max_value) {
        puts(INVALID_MESSAGE);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return value;
}

float getFloat(float min_value, float max_value, char *msg) {
    float value;
    printf(msg);
    while (scanf("%f", &value) != 1 || value < min_value || value > max_value) {
        puts(INVALID_MESSAGE);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return value;
}

double getDouble(double min_value, double max_value, char *msg) {
    double value;
    printf(msg);
    while (scanf("%lf", &value) != 1 || value < min_value || value > max_value) {
        puts(INVALID_MESSAGE);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return value;
}

char getChar(char *msg) {
    char value;
    printf(msg);
    value = getchar();
    cleanInputBuffer();
    return value;
}

void getString(char *string, unsigned int size, char *msg) {
    printf(msg);
    
    if (fgets(string, size, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}

int get_confirm_string(char *str, char *phrase, char *menu_phrase, int size, int cancel) {

    int confirm;

    char aux[size];

    do {
        clear_screen();
        
        getString(aux, size, phrase);

        printf("\n");
        
        confirm = confirm_menu(menu_phrase, cancel);

        if (confirm == 1) {
            strncpy(str, aux, size);
            return 1;
        }
    } while (confirm != 1 && confirm != 0);
    return 0;
}
