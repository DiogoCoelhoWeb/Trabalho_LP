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

//Main menu
const char *PROFILE_OPTIONS[PROFILE_OPTION_SIZE] = {"Administrator", "User"};

//Profile menus
const char *ADMIN_OPTIONS[ADMIN_OPTION_SIZE] = {"Manage Comapnies Catalog", "Manage Activity Branches", "View Reports", "Go Back"};
const char *USER_OPTIONS[USER_OPTION_SIZE] = {"Search Company", "Rate Company", "Comment Company", "Go Back"};

//Admin menu
const char *MANAGE_CATALOG_OPTIONS[MANAGE_CATALOG_OPTION_SIZE] = {"Create Company", "Edit Company", "Remove Company", "Go Back"};
const char *MANAGE_ACT_BRANCH_OPTIONS[MANAGE_ACT_BRANCH_OPTION_SIZE] = {"Create Activity Branch", "Edit Activity Branch", "Remove Activity Branch", "Reactivate Activity Branch","Go Back"};

void print_menu(int num_op, char *title, const char *op_array[]) {
    printf("%s ", title);

    for (int i = 0; i < 39 - strlen(title); i++) {
        printf("-");
    }

    printf("\n");

    for (int i = 0; i < num_op; i++) {
        printf("  %d -> %s\n", i + 1, op_array[i]);
    }
    
    printf("  0 -> Exit\n");
    printf("----------------------------------------\n\n");
    printf("-> ");
}

int menu(int num_op, char *title, const char *op_array[]) {

    int op;

    do {
        print_menu(num_op, title, op_array);
        scanf("%d", &op);
    } while (op < 0 || op > num_op);

    return op;

}

/*ADMIN OPTIONS*/

void manage_comp_catalog(int *main_op) {
    int op;

    do {
        op = menu(MANAGE_CATALOG_OPTION_SIZE, "Admin - Companies Catalog", MANAGE_CATALOG_OPTIONS);

        switch (op) {
            case 1:
                //TODO: insert_company();
                break;

            case 2:
                //TODO: edit_company();
                break;

            case 3:
                //TODO: remove_company();
                break;

            case 4:
                break;

            case 0:
                *main_op = 0;
                break;
        }
    } while (op != 0 && op != 4 && *main_op != 0);
}

void manage_act_branches(int *main_op) {
    int op;

    do {
        op = menu(MANAGE_ACT_BRANCH_OPTION_SIZE, "Admin - Activity Branches", MANAGE_ACT_BRANCH_OPTIONS);

        switch (op) {
            case 1:
                //TODO: insert_act_branch();
                break;

            case 2:
                //TODO: edit_act_branch();
                break;

            case 3:
                //TODO: remove_act_branch();
                break;

            case 4:
                //TODO: reactivate_act_branch();
                break;
            case 5:
                break;

            case 0:
                *main_op = 0;
                break;
        }
    } while (op != 0 && op != 5 && *main_op != 0);
}

void admin_menu(int *main_op) {
    int op;

    do {
        op = menu(ADMIN_OPTION_SIZE, "Administrator", ADMIN_OPTIONS);

        switch (op) {
            case 1:
                manage_comp_catalog(main_op);
                break;

            case 2:
                manage_act_branches(main_op);
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
    } while (op != 0 && op != 4 && *main_op != 0);
}

/*USER OPTIONS*/

//TODO: Create the user options menu structure and program logic

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
    } while (op != 0 && op != 4 && *main_op != 0);
}

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