/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

void pause_exec(){
    getChar("Press ENTER to continue...");
}

void clear_screen(){
    printf("\E[H\E[J");
}

void print_menu(int num_op, char *title, const char *op_array[]) {
    printf("%s ", title);

    for (int i = 0; i < 39 - (int) strlen(title); i++) {
        printf("-");
    }

    printf("\n");

    for (int i = 0; i < num_op; i++) {
        printf("  %d -> %s\n", i + 1, op_array[i]);
    }

    printf("  0 -> Exit\n");
    printf("----------------------------------------\n\n");
}

int menu(int num_op, char *title, const char *op_array[]) {

    int op;

    do {
        print_menu(num_op, title, op_array);
        op = getInt(0, num_op, "-> ");

        if (op < 0 || op > num_op) {
            puts("Invalid Option");
        }
    } while (op < 0 || op > num_op);

    return op;

}

void print_confirm_menu(char *title, int exit) {
    printf("\n");
    printf("%s ----------", title);

    printf("\n");
    printf("  1 -> Yes\n");
    printf("  2 -> No\n");
    printf("  0 -> %s\n", exit ? "Exit" : "Cancel");
    
    for(int i = 0; i < (int) strlen(title); i++){
        printf("-");
    }
    
    printf("-----------\n\n");
}

int confirm_menu(char *title, int exit) {

    int op;

    do {
        print_confirm_menu(title, exit);
        op = getInt(0, 2, "-> ");

        if (op < 0 || op > 2) {
            puts("Invalid Option");
        }
    } while (op < 0 || op > 2);

    return op;

}