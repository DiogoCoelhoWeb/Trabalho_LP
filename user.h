/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/**@file user.h
 * @author Diogo Coelho
 * @version 1.0
 * @date 11 de janeiro de 2024, 10:00
 */

#ifndef USER_H
#define USER_H

typedef enum {
    NIF_SEARCH,
    CATEGORY_SEARCH,
    NAME_SEARCH
} SearchType;

/**
 * @brief This functions shows a comment added by a user
 * @param name The name of the user
 * @param email The email of the user
 * @param title The title of the comment
 * @param text The comment's content
 */
void show_comment(char *name, char *email, char *title, char *text);

/**
 * @brief Searches the companies array for a company with options shown to the user
 * @param companies The companies array
 * @param search_type The type of search the user chose
 */
void user_search_comp(Companies companies, Activity_Branches activity_branches, SearchType search_type);

/**
 * @brief Let's the user rate a company
 * @param companies The companies array
 * @param name The name of the user
 * @param email The email of the user
 */
void rate_comp(Companies *companies, Activity_Branches activity_branches, char *name, char *email);


/**
 * @brief Let's the user comment a company
 * @param companies The companies array
 * @param name The name of the user
 * @param email The email of the user
 */
void comment_comp(Companies *companies, Activity_Branches activity_branches, char *name, char *email);

#endif /* USER_H */

