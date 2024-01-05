/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include "company.h"

/**@file menus.h
 * @author Diogo Coelho
 * @version 1.0
 * @date 6 de dezembro de 2023, 14:18
 */

#ifndef MENUS_H
#define MENUS_H

//Main menu
#define PROFILE_OPTION_SIZE           2

//Profile menus
#define ADMIN_OPTION_SIZE             4
#define USER_OPTION_SIZE              4

//Admin menu
#define MANAGE_CATALOG_OPTION_SIZE    4
#define MANAGE_ACT_BRANCH_OPTION_SIZE 5
#define SHOW_REPORTS_OPTION_SIZE      4

typedef enum {
    FALSE,
    TRUE
} bool;

enum Profiles {
    ADMIN = 1,
    USER
};

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

/*ADMIN OPTIONS*/

/**
 * @brief This function generates the menu for the company catalog management
 * @param main_op
 */
void manage_comp_catalog(int *main_op, Companies *companies);

/**
 * @brief This function generates the menu for the activity branch management
 * @param main_op
 */
void manage_act_branches(int *main_op);

/*PROFILE MENUS*/

/**
 * @brief This function generates the menu for the profile ADMIN
 * @param main_op
 */
void admin_menu(int *main_op, Companies *companies);

/**
 * @brief This function generates the menu for the profile USER
 * @param main_op
 */
void user_menu(int *main_op, Companies *companies);

/*MAIN MENU*/

/**
 * @brief This function generates the application's main menu and waits for a user to choose an option to start
 */
void main_menu(Companies *companies);

#endif /* MENUS_H */

