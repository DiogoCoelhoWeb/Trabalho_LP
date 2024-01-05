/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

void clear_screen(){
    printf("\E[H\E[J");
}

void pause_exec(){
    printf("Press ENTER to continue... ");
    getchar();
}

void print_menu(int num_op, char *title, const char *op_array[]) {
    printf("%s ", title);

    for (int i = 0; i < 39 - (int) strlen(title); i++) {
        printf("-");
    }

    printf("\n");

    for (int i = 0; i < num_op; i++) {
        printf("  [%d] %s\n", i + 1, op_array[i]);
    }

    printf("  [0] Exit\n");
    printf("----------------------------------------\n\n");
}

int menu(int num_op, char *title, const char *op_array[]) {

    int op;
    
    print_menu(num_op, title, op_array);
    op = getInt(0, num_op, "-> ");

    return op;
}

int confirm_menu(char *msg, int cancel) {

    printf("%s -----\n", msg);
    printf("  1 -> Yes\n");
    printf("  2 -> No\n");

    if (cancel) {
        printf("  0 -> Cancel\n");
    }

    for (int i = 0; i < (int) strlen(msg); i++) {
        printf("-");
    }

    printf("------\n\n");
    
    if(cancel){
        return getInt(0, 2, "-> ");
    }
    
    return getInt(1, 2, "-> ");
}
