/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

#include <stdio.h>
#include <stdlib.h>

/**@file menus.h
 * @author Diogo Coelho
 * @version 1.0
 * @date 6 de dezembro de 2023, 14:18
 */

#ifndef MENUS_H
#define MENUS_H

#define PROFILE_OPTION_SIZE 2
#define ADMIN_OPTION_SIZE   4
#define USER_OPTION_SIZE    4

typedef enum {
    FALSE,
    TRUE
} bool;

enum Profiles {
    ADMIN = 1,
    USER
};

int menu(int num_op, char *title, const char *op_array[]);

void admin_menu(int *main_op);

void user_menu(int *main_op);

void main_menu();

#endif /* MENUS_H */

