/**@file main.c 
 * @author Diogo Coelho
 * @version 1.0
 * @date 22 de novembro de 2023, 13:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"
#include "company.h"

/*
 * 
 */
int main() {

    Companies companies;

    companies.n_comp = 0;
    companies.comp_mem_size = 0;
    companies.companies = NULL;

    companies.companies = malloc(sizeof(Company));

    if (companies.companies != NULL) {
        companies.comp_mem_size = 1;
        
        main_menu(&companies);   
        
        free(companies.companies);
    } else {
        puts("Error starting the program!(Memory allocation failed)");
    }
    
    printf("\nExiting ...\n");

    return (EXIT_SUCCESS);
}