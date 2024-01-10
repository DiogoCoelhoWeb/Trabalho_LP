/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "company.h"
#include "utilities.h"
#include "log_gen.h"

const char *EDIT_COMP_OPTIONS[EDIT_COMP_OPTION_SIZE] = {"Name", "Activity Branch", "Street", "Locality", "Postal Code", "Category", "Enable/Disable", "Go Back"};

char *print_category(int i) {
    switch (i) {
        case MICRO:
            return "Micro";
        case PME:
            return "PME";
        case BIG:
            return "Big";
    }
    return"";
}

int read_cat(char *phrase) {

    int category;

    do {
        puts("Categories ------------------------------------------------------");
        for (int i = 0; i < CATEGORY; i++) {
            printf("  %d - %s\n", i + 1, print_category(i));
        }
        puts("-----------------------------------------------------------------");

        category = getInt(1, CATEGORY, phrase);

    } while (category < 1 || category > CATEGORY);

    return category - 1;

}

void show_comp(Company company) {

    printf("\n%s (%s) ", company.name, company.active ? "Active" : "Inactive");
    
    for(int i = 0; i < 61 - (int) strlen(company.name) - (company.active == 1 ? 6 : 8); i++){
        printf("-");
    }
    
    printf("\n");
    
    printf("  NIF                %d\n", company.NIF);
    printf("  Category           %s\n", print_category(company.category));
    printf("  Address            %s, %s, %s\n", company.address.street, company.address.locality, company.address.postal_code);
    printf("  Number of Ratings  %d\n", company.nClassis);
    printf("  Number of Comments %d\n", company.nComments);

    printf("-----------------------------------------------------------------\n\n");
}

int get_edit_string(Company *comp, char *str, char *phrase, char *menu_phrase, int size) {

    int confirm;

    char aux[size];

    do {
        getString(aux, size, phrase);

        confirm = confirm_menu(menu_phrase, 1);

        if (confirm == 1) {
            strncpy(str, aux, size);
            show_comp(*comp);
            return 1;
        }
    } while (confirm != 1 && confirm != 0);
    return 0;
}

int get_edit_cat(Company *comp, Category *cat, char *phrase, char *menu_phrase) {

    int confirm;
    int cat_tmp;

    do {

        cat_tmp = read_cat(phrase);

        confirm = confirm_menu(menu_phrase, 1);

        if (confirm == 1) {
            *cat = cat_tmp;
            show_comp(*comp);
            return 1;
        }
    } while (confirm != 1 && confirm != 0);
    return 0;
}

int change_state(Company *company) {
    if (company->active) {
        printf("The company %s is enabled!\n", company->name);
        if (confirm_menu("Are you sure you want to disbale the company?", 0) == 1) {
            company->active = 0;
        }

        clear_screen();
        show_comp(*company);
        pause_exec();
        return 1;
    }

    if (confirm_menu("Are you sure you want to enbale the company?", 0) == 1) {
        company->active = 1;
        return 1;
    }

    return 0;
    
    clear_screen();
    show_comp(*company);
    pause_exec();

}

int search_comp(Companies companies, int NIF) {

    if (companies.n_comp == 0) {
        return -1;
    }

    for (int i = 0; i < companies.n_comp; i++) {
        if (companies.companies[i].NIF == NIF) {
            return i;
        }
    }
    return -1;
}

void insert_comp(Companies *companies) {
    int NIF;

    Company *companiestmp;

    clear_screen();

    puts("Create Company --------------------------------------------------");
    NIF = getInt(100000000, 999999999, "Enter the companies NIF: ");

    if (search_comp(*companies, NIF) != -1) {
        puts("Company already exists!");
        return;
    }

    logMsg("Trying to create company...", INFORMATIONAL, LOG_FILE);
    
    if (companies->n_comp == companies->comp_mem_size) {
        companiestmp = (Company *) realloc(companies->companies, sizeof (Company) * (companies->comp_mem_size * COMPANY_MULT_FACTOR));

        if (companiestmp == NULL) {
            logMsg("Failed to reallocate memory on the heap!(realloc failed)", ERROR, LOG_FILE);
            logMsg("The company couldn't be created!", WARNING, LOG_FILE);
            puts("Error creating company!");
            return;
        }

        companies->companies = companiestmp;
        companies->comp_mem_size = companies->n_comp * COMPANY_MULT_FACTOR;
    }

    companies->companies[companies->n_comp].NIF = NIF;

    companies->companies[companies->n_comp].category = read_cat("Enter the company's category: ");

    getString(companies->companies[companies->n_comp].name, COMPANY_NAME_SIZE, "Enter the company's name: ");
    getString(companies->companies[companies->n_comp].address.street, COMPANY_STREET_SIZE, "Enter the company's street: ");
    getString(companies->companies[companies->n_comp].address.locality, COMPANY_LOCALITY_SIZE, "Enter the company's locality: ");
    getString(companies->companies[companies->n_comp].address.postal_code, 11, "Enter the company's postal code: ");

    companies->companies[companies->n_comp].active = 1;
    companies->companies[companies->n_comp].nClassis = 0;
    companies->companies[companies->n_comp].nComments = 0;

    clear_screen();

    show_comp(companies->companies[companies->n_comp]);
    companies->n_comp++;

    logMsg("Company created successfully!", INFORMATIONAL, LOG_FILE);
    
    pause_exec();

}

void edit_comp(Companies *companies, int *main_op) {
    int NIF;
    int comp_position;
    int op;
    int confirm_comp;

    clear_screen();

    if (companies->n_comp == 0) {
        puts("There are no companies stored!\n");
        pause_exec();
        return;
    }

    do {
        
        clear_screen();
        
        NIF = getInt(100000000, 999999999, "Enter the companies NIF: ");
        comp_position = search_comp(*companies, NIF);

        if (comp_position == -1) {
            puts("The company doesn't exist!\n");
            pause_exec();
            continue;
        }
        
        show_comp(companies->companies[comp_position]);
        
        confirm_comp = confirm_menu("Are you sure you want to edit this company?", 1);
        
        if(confirm_comp == 0){
            return;
        }
        
    }while(confirm_comp != 1);
    
    logMsg("Trying to edit company...", INFORMATIONAL, LOG_FILE);

    do {

        clear_screen();

        op = menu(EDIT_COMP_OPTION_SIZE, "Edit Company", EDIT_COMP_OPTIONS);

        switch (op) {
            case 1:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if(get_edit_string(&(companies->companies[comp_position]), companies->companies[comp_position].name, "Enter the new company's name: ", "Are you sure you want to keep the new name?", COMPANY_NAME_SIZE)){
                    logMsg("Changed the company's name", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 2:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                //TODO: Activity Branch
                pause_exec();
                break;
            case 3:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if(get_edit_string(&(companies->companies[comp_position]), companies->companies[comp_position].address.street, "Enter the company's new street: ", "Are you sure you want to keep the new street?", COMPANY_STREET_SIZE)){
                    logMsg("Changed the company's street", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 4:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if(get_edit_string(&(companies->companies[comp_position]), companies->companies[comp_position].address.locality, "Enter the company's new locality: ", "Are you sure you want to keep the new locality?", COMPANY_LOCALITY_SIZE)){
                    logMsg("Changed the company's locality", INFORMATIONAL, LOG_FILE);
                }
                break;
            case 5:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if(get_edit_string(&(companies->companies[comp_position]), companies->companies[comp_position].address.postal_code, "Enter the company's new postal_code: ", "Are you sure you want to keep the new postal_code?", 11)){
                    logMsg("Changed the company's postal code", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 6:
                clear_screen();
                puts("Edit Company ----------------------------------------------------\n");
                if(get_edit_cat(&(companies->companies[comp_position]), &(companies->companies[comp_position].category), "Enter the new company's category: ", "Are you sure you want to keep the new category?")){
                    logMsg("Changed the company's category", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 7:
                clear_screen();
                puts("Edit Company ----------------------------------------------------\n");
                if(change_state(companies->companies + comp_position)){
                    logMsg("Changed the company's state", INFORMATIONAL, LOG_FILE);
                }
                break;
            case 8:
                break;
            case 0:
                *main_op = 0;
                break;
        }

    } while (op != 0 && op != 8);
    
    logMsg("Edited the company successfuly!", INFORMATIONAL, LOG_FILE);

}

void remove_comp(Companies *companies) {

    int NIF;
    int comp_position;
    Company *companiestmp;

    clear_screen();

    if (companies->n_comp == 0) {
        puts("\nThere are no companies stored!\n");
        pause_exec();
        return;
    }

    NIF = getInt(100000000, 999999999, "Enter the companies NIF: ");
    comp_position = search_comp(*companies, NIF);

    if (comp_position == -1) {
        puts("\nThe company doesn't exist!\n");
        pause_exec();
        return;
    }

    show_comp(companies->companies[comp_position]);

    if (confirm_menu("Are you sure you want to delete the company?", 0) == 2) {
        return;
    }

    logMsg("Trying to remove company...", INFORMATIONAL, LOG_FILE);
    
    if (companies->companies[comp_position].nComments != 0) {

        clear_screen();

        if (companies->companies[comp_position].active) {
            logMsg("Couldn't remove company because it has comments", WARNING, LOG_FILE);
            puts("---- Unable to delete the company because there are comments ----\nChanging state to Inactive!");
            companies->companies[comp_position].active = 0;
        } else {
            logMsg("Couldn't remove company because it has comments", WARNING, LOG_FILE);
            puts("---- Unable to delete the company because there are comments ----\nThe company is already inactive!\nSkipping instruction!");
        }
        pause_exec();
        return;
    }

    clear_screen();

    puts("Deleting company...");

    //Copying last company to the deleted company's location
    companies->companies[comp_position].NIF = companies->companies[companies->n_comp - 1].NIF;
    strncpy(companies->companies[comp_position].name, companies->companies[companies->n_comp - 1].name, COMPANY_NAME_SIZE);
    companies->companies[comp_position].active = companies->companies[companies->n_comp - 1].active;
    companies->companies[comp_position].act_code = companies->companies[companies->n_comp - 1].act_code;
    companies->companies[comp_position].category = companies->companies[companies->n_comp - 1].category;

    strncpy(companies->companies[comp_position].address.locality, companies->companies[companies->n_comp - 1].address.locality, COMPANY_LOCALITY_SIZE);
    strncpy(companies->companies[comp_position].address.postal_code, companies->companies[companies->n_comp - 1].address.postal_code, 11);
    strncpy(companies->companies[comp_position].address.street, companies->companies[companies->n_comp - 1].address.street, COMPANY_STREET_SIZE);


    companies->companies[comp_position].classis = companies->companies[companies->n_comp - 1].classis;
    companies->companies[comp_position].nClassis = companies->companies[companies->n_comp - 1].nClassis;

    companies->companies[comp_position].comments = companies->companies[companies->n_comp - 1].comments;
    companies->companies[comp_position].nComments = companies->companies[companies->n_comp - 1].nComments;

    //Removing data from the last company's position
    companies->companies[companies->n_comp - 1].NIF = 0;
    companies->companies[companies->n_comp - 1].act_code = 0;
    companies->companies[companies->n_comp - 1].active = 0;
    companies->companies[companies->n_comp - 1].category = 0;
    companies->companies[companies->n_comp - 1].nClassis = 0;
    companies->companies[companies->n_comp - 1].nComments = 0;

    strncpy(companies->companies[companies->n_comp - 1].name, "", COMPANY_NAME_SIZE);
    strncpy(companies->companies[companies->n_comp - 1].address.locality, "", COMPANY_LOCALITY_SIZE);
    strncpy(companies->companies[companies->n_comp - 1].address.postal_code, "", 11);
    strncpy(companies->companies[companies->n_comp - 1].address.street, "", COMPANY_STREET_SIZE);

    companies->companies[companies->n_comp - 1].classis = NULL;
    companies->companies[companies->n_comp - 1].comments = NULL;

    companies->n_comp--;

    if (companies->n_comp < companies->comp_mem_size / 2) {
        companiestmp = (Company *) realloc(companies->companies, sizeof (Company) * (companies->comp_mem_size / COMPANY_MULT_FACTOR));

        if (companiestmp != NULL) {
            companies->companies = companiestmp;
            companies->comp_mem_size = companies->n_comp * COMPANY_MULT_FACTOR;
        }else{
            logMsg("Failed to reallocate the companies array!(realloc failed)", ERROR, LOG_FILE);
            logMsg("The array couldn't be resized!", WARNING, LOG_FILE);
        }
    }

    clear_screen();
    logMsg("Company successfuly deleted!", INFORMATIONAL, LOG_FILE);
    puts("Company successfully deleted!\n");
    pause_exec();
}

void list_comp(Companies companies) {

    clear_screen();
    
    if (companies.n_comp == 0) {
        puts("There are no companies stored!\n");
        pause_exec();
        return;
    }

    logMsg("Listing companies...", INFORMATIONAL, LOG_FILE);
    puts("List Companies --------------------------------------------------\n");
    
    for (int i = 0; i < companies.n_comp; i++) {
        show_comp(companies.companies[i]);
    }
    
    logMsg("Companies listed successfuly!", INFORMATIONAL, LOG_FILE);

    pause_exec();
}