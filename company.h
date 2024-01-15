/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/**@file main.c 
 * @author Diogo Coelho
 * @version 1.0
 * @date 7 de dezembro de 2023, 13:12
 */

#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#ifndef COMPANY_H
#define COMPANY_H

#define COMPANY_MULT_FACTOR         2
#define COMPANY_NAME_SIZE           50
#define COMPANY_STREET_SIZE         100
#define COMPANY_LOCALITY_SIZE       50

#define ACTIVITY_BRANCH_NAME_SIZE   50

#define COMMENT_TITLE_SIZE          40
#define COMMENT_TEXT_SIZE           100

#define NAME_USER_SIZE              40
#define EMAIL_USER_SIZE             50

#define EDIT_COMP_OPTION_SIZE       8
#define EDIT_ACT_BRANCH_OPTION_SIZE 3

#define SHOW_REPORTS_OPTION_SIZE    4

typedef enum {
    MICRO,
    PME,
    BIG,
    CATEGORY
} Category;

typedef struct{
    char street[COMPANY_STREET_SIZE];
    char locality[COMPANY_LOCALITY_SIZE];
    char postal_code[11];
} Address;

typedef struct {
    int rating;
    char nameUser[NAME_USER_SIZE];
    char emailUser[EMAIL_USER_SIZE];
} Classification;

typedef struct {
    char nameUser[NAME_USER_SIZE];
    char emailUser[EMAIL_USER_SIZE];
    char title[COMMENT_TITLE_SIZE];
    char text[COMMENT_TEXT_SIZE];
} Comment;

typedef struct {
    char name[ACTIVITY_BRANCH_NAME_SIZE];
    int active;
    int isRemoved;
} Act_Branch;

typedef struct{
    int n_branches;
    Act_Branch *activity_branches;
} Activity_Branches;

typedef struct {
    int act_code;
    int NIF;
    int nClassis;
    int nComments;
    int active;
    char name[COMPANY_NAME_SIZE]; 
    Address address;
    Category category;
    Classification *classis;
    Comment *comments;
} Company;

typedef struct {
    int n_comp;
    int comp_mem_size;
    Company *companies;
} Companies;

/**
 * @brief Prints a String with the category name from its value
 * @param i Category value
 * @return The string with the category name
 */
char *print_category(int i);

/**
 * @brief Reads the category that the user wnats to choose
 * @return Returns the value of the category
 */
int read_cat();

/**
 * @brief Prints the company's data in the console
 * @param company The company to be printed
 * @param activity_branches The activity branch array
 */
void show_comp(Company company, Activity_Branches activity_branches);

/**
 * @brief Reads and confirms strings to be edited in a company
 * @param comp The company where the string is being edited
 * @param activity_branches The activity branch array
 * @param str The string to be edited
 * @param phrase Message to be shown to the user
 * @param menu_phrase Message to be shown in the confirmation menu
 * @param size The size of the string to be edited
 * @return Returns 1 if the value changed or 0 otherwise
 */
int get_edit_string(Company *comp, Activity_Branches activity_branches, char *str, char *phrase, char *menu_phrase, int size);

/**
 * @brief Reads and confirms the new category for a company
 * @param comp The company where the string is being edited
 * @param activity_branches The activity branch array
 * @param cat The current category in a company
 * @param phrase Message to be shown to the user
 * @param menu_phrase Message to be shown in the confirmation menu
 * @return Returns 1 if the value changed or 0 otherwise
 */
int get_edit_cat(Company *comp, Activity_Branches activity_branches, Category *cat, char *phrase, char *menu_phrase);

/**
 * @brief Changes the company active state to Active or Inactive
 * @param company The company where the active state will be changed
 * @param activity_branches The activity branch array
 * @return Returns 1 if the value changed or 0 otherwise
 */
int change_state(Company *company, Activity_Branches activity_branches);

/**
 * @brief Searches if a company exists in the Companies array
 * @param companies The comapnies array
 * @param NIF The NIF number of the company to be searched
 * @return Return the company's position in the array or -1 if the company doesn't exist
 */
int search_comp(Companies companies, int NIF);

/**
 * @brief Adds a company to the companies array and expands it if necessary
 * @param companies The companies array where the new company will be added
 * @param activity_branches The activity branch array
 */
void insert_comp(Companies *companies, Activity_Branches activity_branches);

/**
 * @brief Lets the user choose a parameter in a company to be edited and prompts the user for the new data to be entered
 * @param companies The companies array where the company to be edited is stored
 * @param activity_branches The activity branch array
 * @param main_op The option variable of the main menu to quit the program if the user chooses to do so
 */
void edit_comp(Companies *companies, Activity_Branches activity_branches, int *main_op);

/**
 * @brief Deletes a company from the company array or changes it's state to inactive if the comapny has stored comments
 * @param companies The companies array where the company is stored
 * @param activity_branches The activity branch array
 */
void remove_comp(Companies *companies, Activity_Branches activity_branches);

/**
 * @brief Shows all companies stored in the company array with the show_comp(Company company) function
 * @param companies The company array
 * @param activity_branches The activity branch array
 */
void list_comp(Companies companies, Activity_Branches activity_branches);

/**
 * @brief Shows 3 different reports the user can choose to view
 * @param companies The comapnies array
 * @param main_op The option variable of the main menu to quit the program if the user chooses to do so
 */
void show_reports(Companies companies, int *main_op);

/**
 * @brief Inserts a new activity branch into the array
 * @param activity_branches The activity branch array
 */
void insert_act_branch(Activity_Branches *activity_branches);

/**
 * @brief Edits an activity branch
 * @param activity_branches The activity branch array
 * @param main_op The pointer to the main manu option so the user can quit at any time
 */
void edit_act_branch(Activity_Branches *activity_branches, int *main_op);

/**
 * @brief Removes an activity branch from the array or diables it if it's being used by a company
 * @param activity_branches The activity branch array
 * @param companies The comapnies array
 */
void remove_act_branch(Activity_Branches *activity_branches, Companies companies);

/**
 * @brief Shows all the activity branches in the array
 * @param activity_branches The activity branches array
 */
void list_act_branch(Activity_Branches activity_branches);

#endif /* COMPANY_H */

