/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        
        if(op < 0 || op > num_op){
            puts("Invalid Option");
        }
    } while (op < 0 || op > num_op);

    return op;

}