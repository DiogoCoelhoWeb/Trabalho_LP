/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/**@file main.c 
 * @author Diogo Coelho
 * @version 1.0
 * @date 7 de dezembro de 2023, 16:25
 */

#ifndef INPUT_H
#define INPUT_H

/**
 * @brief Cleans the console's input buffer
 */
void cleanInputBuffer();

/**
 * @brief Safely reads an integer from the console
 * @param min_value Minimum acceptable value
 * @param max_value Maximum acceptable value
 * @param msg Message to be displayed to the user
 * @return Returns the user selected integer
 */
int getInt(int min_value, int max_value, char *msg);

/**
 * @brief Safely reads a float from the console
 * @param min_value Minimum acceptable value
 * @param max_value Maximum acceptable value
 * @param msg Message to be displayed to the user
 * @return Returns the user selected float
 */
float getFloat(float min_value, float max_value, char *msg);

/**
 * @brief Safely reads a double from the console
 * @param min_value Minimum acceptable value
 * @param max_value Maximum acceptable value
 * @param msg Message to be displayed to the user
 * @return Returns the user selected double
 */
double getDouble(double min_value, double max_value, char *msg);

/**
 * @brief Safely reads a character from the console
 * @param msg Message to be displayed to the user
 * @return Returns the user selected character
 */
char getChar(char *msg);

/**
 * @brief Safely reads a string from the console
 * @param string The string to be read
 * @param size The size of the string to be read
 * @param msg Message to be displayed to the user
 */
void getString(char *string, unsigned int size, char *msg);

int get_confirm_string(char *str, char *phrase, char *menu_phrase, int size, int cancel);

#endif /* INPUT_H */

