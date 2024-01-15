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
#include "log_gen.h"

/*
 * 
 */
int main() {

    Companies companies;
    Activity_Branches activity_branches;

    companies.n_comp = 0;
    companies.comp_mem_size = 0;
    companies.companies = NULL;

    companies.companies = (Company *)malloc(sizeof (Company));

    activity_branches.n_branches = 0;
    activity_branches.activity_branches = NULL;
    
    activity_branches.activity_branches = (Act_Branch *) malloc(sizeof(Act_Branch));

    logMsg("Starting program ------------------------------------------------", NOLEVEL, LOG_FILE);

    if (companies.companies != NULL) {
        companies.comp_mem_size = 1;
    } else {
        logMsg("Error allocating memmory on the heap!(malloc failed)", ERROR, LOG_FILE);
        puts("Error starting the program!(Memory allocation failed)");
        return(EXIT_FAILURE);
    }
    
    if (companies.companies == NULL){
        logMsg("Error allocating memmory on the heap!(malloc failed)", ERROR, LOG_FILE);
        puts("Error starting the program!(Memory allocation failed)");
        return(EXIT_FAILURE);
    }

    main_menu(&companies, &activity_branches);
    
    free(companies.companies);
    free(activity_branches.activity_branches);

    logMsg("Exiting program  ------------------------------------------------\n", NOLEVEL, LOG_FILE);
    printf("\nExiting ...\n");

    return (EXIT_SUCCESS);
}