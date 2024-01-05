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

void pause_exec();

void clear_screen();

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

int confirm_menu(char *title, int exit);

void print_confirm_menu(char *title, int exit);


#endif /* UTILITIES_H */

