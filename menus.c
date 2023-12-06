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

/**
 * @brief This function is a generalized way of generating a menu given a number of options and thier respective text
 * @param num_op Number of options
 * @param title Title of the menu
 * @param op_array Array with the name of each option
 * @return Returns the option selected by the user
 */
int menu(int num_op, char *title, char *op_array[]) {

    int op;

    do {
        printf("%s --------------------\n", title);

        for (int i = 0; i < num_op; i++) {
            printf("  %d -> %s\n", i + 1, op_array[i]);
        }

        printf("  0 -> Exit\n");

        for (int i = 0; i <= strlen(title); i++) {
            printf("-");
        }
        printf("--------------------\n\n");

        printf("-> ");
        scanf("%d", &op);

    } while (op < 0 || op > num_op);

    return op;

}

/**
 * @brief This function generates the application's main menu and waits for a user to choose an option to start
 */
void main_menu() {

    int op;

    char *op_text[2] = {"User", "Administrator"};

    do {
        op = menu(2, "Menu", op_text);

        switch (op) {
            case 1:
                puts("USER");
                break;
            case 2:
                puts("ADMIN");
                break;
            case 0:
                break;
        }
    } while (op != 0);

}