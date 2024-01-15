/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include "company.h"

#include "company.h"
#include "user.h"

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
#define MANAGE_CATALOG_OPTION_SIZE    5
#define MANAGE_ACT_BRANCH_OPTION_SIZE 5
#define SHOW_REPORTS_OPTION_SIZE      4

//User menu
#define USER_SEARCH_COMP_OPTION_SIZE  4

enum Profiles {
    ADMIN = 1,
    USER
};

/*ADMIN OPTIONS*/

/**
 * @brief This function generates the menu for the company catalog management
 * @param main_op The pointer to the option on the main menu so that the user can quit at any time
 * @param companies The pointe to the companies array to be used troughout the program
 * @param activity_branches The activity branch array
 */
void manage_comp_catalog(int *main_op, Companies *companies, Activity_Branches activity_branches);

/**
 * @brief This function generates the menu for the activity branch management
 * @param main_op The pointer to the option on the main menu so that the user can quit at any time
 * @param activity_branches The activity branch array
 * @param companies The pointe to the companies array to be used troughout the program
 */
void manage_act_branches(int *main_op, Activity_Branches *activity_branches, Companies *companies);

/*PROFILE MENUS*/

/**
 * @brief This function generates the menu for the profile ADMIN
 * @param main_op The pointer to the option on the main menu so that the user can quit at any time
 * @param companies The pointe to the companies array to be used troughout the program
 * @param activity_branches The activity branch array
 */
void admin_menu(int *main_op, Companies *companies, Activity_Branches *activity_branches);

/**
 * @brief This function generates the menu for the profile USER
 * @param main_op The pointer to the option on the main menu so that the user can quit at any time
 * @param companies The pointe to the companies array to be used troughout the program
 * @param activity_branches The activity branch array
 */
void user_menu(int *main_op, Companies *companies, Activity_Branches activity_branches);

/*MAIN MENU*/

/**
 * @brief This function generates the application's main menu and waits for a user to choose an option to start
 * @param companies The comapany array
 * @param activity_branches The activity branch array
 */
void main_menu(Companies *companies, Activity_Branches *activity_branches);

#endif /* MENUS_H */

