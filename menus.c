/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

/**@file menus.c
 * @author Diogo Coelho
 * @version 1.0
 * @date 6 de dezembro de 2023, 14:18
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"


const char *PROFILE_OPTIONS[PROFILE_OPTION_SIZE] = {"Administrator", "User"};
const char *ADMIN_OPTIONS[ADMIN_OPTION_SIZE] = {"Manage Comapnies Catalog", "Manage Activity Branches", "View Reports", "Go Back"};
const char *USER_OPTIONS[USER_OPTION_SIZE] = {"Search Company", "Rate Company", "Comment Company","Go Back"};

/**
 * @brief This function is a generalized way of generating a menu given a number of options and thier respective text
 * @param num_op Number of options
 * @param title Title of the menu
 * @param op_array Array with the name of each option
 * @return Returns the option selected by the user
 */
int menu(int num_op, char *title, const char *op_array[]) {

    int op;

    do {
        printf("%s ------------------------------\n", title);

        for (int i = 0; i < num_op; i++) {
            printf("  %d -> %s\n", i + 1, op_array[i]);
        }

        printf("  0 -> Exit\n");

        for (int i = 0; i <= strlen(title); i++) {
            printf("-");
        }
        printf("------------------------------\n\n");

        printf("-> ");
        scanf("%d", &op);

    } while (op < 0 || op > num_op);

    return op;

}

/**
 * @brief This functiongenerates the menu for the profile ADMIN
 * @param main_op
 */
void admin_menu(int *main_op) {
    int op;

    do {
        op = menu(ADMIN_OPTION_SIZE, "Administrator", ADMIN_OPTIONS);

        switch (op) {
            case 1:
                //TODO: manage_comp_catalog();
                break;
            case 2:
                //TODO: manage_act_branches();
                break;
            case 3:
                //TODO: show_reports();
                break;
            case 4:
                break;
            case 0:
                *main_op = 0;
                break;
        }
    } while (op != 0 && op != 4);
}

/**
 * @brief This function generates the menu for the profile USER
 * @param main_op
 */
void user_menu(int *main_op) {
    int op;

    do {
        op = menu(USER_OPTION_SIZE, "User", USER_OPTIONS);

        switch (op) {
            case 1:
                //TODO: search_comp();
                break;
            case 2:
                //TODO: rate_comp();
                break;
            case 3:
                //TODO: comment_comp();
                break;
            case 4:
                break;
            case 0:
                *main_op = 0;
                break;
        }
    } while (op != 0 && op != 4);
}

/**
 * @brief This function generates the application's main menu and waits for a user to choose an option to start
 */
void main_menu() {

    int op;

    do {
        op = menu(PROFILE_OPTION_SIZE, "Menu", PROFILE_OPTIONS);

        switch (op) {
            case ADMIN:
                admin_menu(&op);
                break;
            case USER:
                user_menu(&op);
                break;
            case 0:
                break;
        }
    } while (op != 0);

}