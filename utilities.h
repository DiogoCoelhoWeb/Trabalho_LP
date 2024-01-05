/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   utilities.h
 * Author: Diogo Coelho
 *
 * Created on 7 de dezembro de 2023, 17:05
 */

#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * @brief Clears the console text
 */
void clear_screen();

/**
 * @brief Stops the code until the user presses ENTER
 */
void pause_exec();

/**
 * @brief Prints the text of the generalized menu with all the options associated
 * @param num_op Number of options
 * @param title Title of the menu
 * @param op_array Array with the name of each option
 * @return Returns the option selected by the user
 */
void print_menu(int num_op, char *title, const char *op_array[]);

/**
 * @brief This function is a generalized way of generating a menu given a number of options and thier respective text
 * @param num_op Number of options
 * @param title Title of the menu
 * @param op_array Array with the name of each option
 * @return Returns the option selected by the user
 */
int menu(int num_op, char *title, const char *op_array[]);

/**
 * @brief Shows a confirmation menu
 * @param msg The title of the menu
 * @param cancel Cancel option(shows the Cancel option in the menu when not 0)
 * @return Return the option the user picked
 */
int confirm_menu(char *msg, int cancel);

#endif /* UTILITIES_H */

