/**@file main.c 
 * @author Diogo Coelho
 * @version 1.0
 * @brief 
 * @date 22 de novembro de 2023, 13:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(int num_op, char *title, char *op_array[]) {

    int op;

    do {
        for (int i = 0; i < strlen(title) + 4; i++) {
            printf("-");
        }
        printf("\n");

        printf("  %s\n", title);

        for (int i = 0; i < strlen(title) + 4; i++) {
            printf("-");
        }
        printf("\n");

        for (int i = 0; i < num_op; i++) {
            printf("  %d -> %s\n", i + 1, op_array[i]);
        }

        printf("\n  0 -> Exit\n\n");

        printf("-> ");
        scanf("%d", &op);
    }while(op < 0 || op > num_op);
}

/*
 * 
 */
int main() {

    return (EXIT_SUCCESS);
}