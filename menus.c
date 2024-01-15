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
#include "user.h"
#include "company.h"
#include "utilities.h"
#include "input.h"

//Main menu
const char *PROFILE_OPTIONS[PROFILE_OPTION_SIZE] = {"Administrator", "User"};

//Profile menus
const char *ADMIN_OPTIONS[ADMIN_OPTION_SIZE] = {"Manage Companies Catalog", "Manage Activity Branches", "View Reports", "Go Back"};
const char *USER_OPTIONS[USER_OPTION_SIZE] = {"Search Company", "Rate Company", "Comment Company", "Go Back"};

//Admin menu
const char *MANAGE_CATALOG_OPTIONS[MANAGE_CATALOG_OPTION_SIZE] = {"Create Company", "Edit Company", "Remove Company", "List Companies", "Go Back"};
const char *MANAGE_ACT_BRANCH_OPTIONS[MANAGE_ACT_BRANCH_OPTION_SIZE] = {"Create Activity Branch", "Edit Activity Branch", "Remove Activity Branch", "List Activity Branches", "Go Back"};

//User menu
const char *USER_SEARCH_COMP_OPTIONS[USER_SEARCH_COMP_OPTION_SIZE] = {"Search by NIF", "Search by Category", "Search by Name", "Go Back"};

/*ADMIN OPTIONS*/

void manage_comp_catalog(int *main_op, Companies *companies, Activity_Branches activity_branches) {
    int op;

    do {

        clear_screen();

        op = menu(MANAGE_CATALOG_OPTION_SIZE, "Admin - Companies Catalog", MANAGE_CATALOG_OPTIONS);

        switch (op) {
            case 1:
                insert_comp(companies, activity_branches);
                break;

            case 2:
                edit_comp(companies, activity_branches, main_op);
                break;

            case 3:
                remove_comp(companies, activity_branches);
                break;

            case 4:
                list_comp(*companies, activity_branches);
                break;

            case 5:
                break;

            case 0:
                *main_op = 0;
                break;
        }
    } while (op != 0 && op != 5 && *main_op != 0);
}

void manage_act_branches(int *main_op, Activity_Branches *activity_branches, Companies *companies) {
    int op;

    do {

        clear_screen();

        op = menu(MANAGE_ACT_BRANCH_OPTION_SIZE, "Admin - Activity Branches", MANAGE_ACT_BRANCH_OPTIONS);

        switch (op) {
            case 1:
                insert_act_branch(activity_branches);
                break;

            case 2:
                edit_act_branch(activity_branches, main_op);
                break;

            case 3:
                remove_act_branch(activity_branches, *companies);
                break;

            case 4:
                list_act_branch(*activity_branches);
                break;
            case 5:
                break;

            case 0:
                *main_op = 0;
                break;
        }
    } while (op != 0 && op != 5 && *main_op != 0);
}

void admin_menu(int *main_op, Companies *companies, Activity_Branches *activity_branches) {
    int op;

    do {

        clear_screen();

        op = menu(ADMIN_OPTION_SIZE, "Administrator", ADMIN_OPTIONS);

        switch (op) {
            case 1:
                manage_comp_catalog(main_op, companies, *activity_branches);
                break;

            case 2:
                manage_act_branches(main_op, activity_branches, companies);
                break;

            case 3:
                show_reports(*companies, main_op);
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

void search_comp_menu(int *main_op, Companies *companies, Activity_Branches activity_branches) {
    int op;

    do {

        clear_screen();

        op = menu(USER_OPTION_SIZE, "User - Search Company", USER_SEARCH_COMP_OPTIONS);

        switch (op) {
            case 1:
                user_search_comp(*companies, activity_branches, NIF_SEARCH);
                break;

            case 2:
                user_search_comp(*companies, activity_branches, CATEGORY_SEARCH);
                break;

            case 3:
                user_search_comp(*companies, activity_branches, NAME_SEARCH);
                break;

            case 4:
                break;

            case 0:
                *main_op = 0;
                break;
        }
    } while (op != 0 && op != 4 && *main_op != 0);
}

void user_menu(int *main_op, Companies *companies, Activity_Branches activity_branches) {
    int op;

    char name[NAME_USER_SIZE];
    char email[EMAIL_USER_SIZE];
    
    clear_screen();
    get_confirm_string(name, "Enter your name: ", "Are you sure you want to keep this name?", NAME_USER_SIZE, 0);
    
    clear_screen();
    get_confirm_string(email, "Enter your email: ", "Are you sure you want to keep this name?", EMAIL_USER_SIZE, 0);
    
    do {

        clear_screen();

        op = menu(USER_OPTION_SIZE, "User", USER_OPTIONS);

        switch (op) {
            case 1:
                search_comp_menu(main_op, companies, activity_branches);
                break;

            case 2:
                rate_comp(companies, activity_branches, name, email);
                break;

            case 3:
                comment_comp(companies, activity_branches, name, email);
                break;

            case 4:
                break;

            case 0:
                *main_op = 0;
                break;
        }
    } while (op != 0 && op != 4 && *main_op != 0);
}

/*MAIN MENU*/

void main_menu(Companies *companies, Activity_Branches *activity_branches) {

    int op;

    do {

        clear_screen();

        op = menu(PROFILE_OPTION_SIZE, "Menu", PROFILE_OPTIONS);

        switch (op) {
            case ADMIN:
                admin_menu(&op, companies, activity_branches);
                break;

            case USER:
                user_menu(&op, companies, *activity_branches);
                break;

            case 0:
                break;
        }
    } while (op != 0);
}