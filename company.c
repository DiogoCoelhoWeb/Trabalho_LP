/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "company.h"
#include "utilities.h"

const char *EDIT_COMP_OPTIONS[EDIT_COMP_OPTION_SIZE] = {"Name", "Activity Branch", "Street", "Locality", "Postal Code", "Category", "Go Back"};

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
        puts("Categories ------------");
        for (int i = 0; i < CATEGORY; i++) {
            printf("  %d - %s\n", i + 1, print_category(i));
        }
        puts("-----------------------");

        category = getInt(1, CATEGORY, phrase);

    } while (category < 1 || category > CATEGORY);

    return category - 1;

}

void show_comp(Company company) {

    printf("\n%s (%s) ----------------------------------------------------\n", company.name, company.active ? "Active" : "Inactive");
    printf("  NIF                %d\n", company.NIF);
    printf("  Category           %s\n", print_category(company.category));
    printf("  Address            %s, %s, %s\n", company.address.street, company.address.locality, company.address.postal_code);
    printf("  Number of Ratings  %d\n", company.nClassis);
    printf("  Number of Comments %d\n", company.nComments);

    for (int i = 0; i < (int) strlen(company.name); i++) {
        printf("-");
    }

    if (!company.active) {
        printf("--");
    }

    printf("--------------------------------------------------------------\n\n");
}

void get_edit_string(Company *comp, char* str, char *phrase, char *menu_phrase, int size) {

    int confirm;

    char aux[size];

    do {
        getString(aux, size, phrase);

        confirm = confirm_menu(menu_phrase, 0);

        if (confirm == 1) {
            strncpy(str, aux, size);
            show_comp(*comp);
        }

    } while (confirm != 1 && confirm != 0);
}

void get_edit_cat(Company *comp, Category *cat, char *phrase, char *menu_phrase) {

    int confirm;
    int cat_tmp;

    do {
        
        cat_tmp = read_cat(phrase);

        confirm = confirm_menu(menu_phrase, 0);

        if (confirm == 1) {
            *cat = cat_tmp;
            show_comp(*comp);
        }

    } while (confirm != 1 && confirm != 0);
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
    
    clear_screen();

    Company *companiestmp;

    NIF = getInt(100000000, 999999999, "Enter the companies NIF: ");

    if (search_comp(*companies, NIF) != -1) {
        puts("Company already exists!");
        return;
    }

    if (companies->n_comp == companies->comp_mem_size) {
        companiestmp = (Company *) realloc(companies->companies, sizeof (Company) * (companies->comp_mem_size * COMPANY_MULT_FACTOR));


        if (companiestmp == NULL) {
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

    
    show_comp(companies->companies[companies->n_comp]);

    companies->n_comp++;
    
    pause_exec();
    
}

void edit_comp(Companies *companies, int *main_op) {
    int NIF;
    int comp_position;
    int op;

    clear_screen();
    
    if (companies->n_comp == 0) {
        puts("There are no companies stored!");
        return;
    }

    NIF = getInt(100000000, 999999999, "Enter the companies NIF: ");

    comp_position = search_comp(*companies, NIF);

    if (comp_position == -1) {
        puts("The company doesn't exist!");
        return;
    }

    do {
        op = menu(EDIT_COMP_OPTION_SIZE, "Edit Company", EDIT_COMP_OPTIONS);

        switch (op) {
            case 1:
                get_edit_string(&(companies->companies[comp_position]), companies->companies[comp_position].name, "Enter the new company's name: ", "Are you sure you want to keep the new name?", COMPANY_NAME_SIZE);
                break;
            case 2:
                //TODO: Activity Branch
                break;
            case 3:
                get_edit_string(&(companies->companies[comp_position]), companies->companies[comp_position].address.street, "Enter the company's new street: ", "Are you sure you want to keep the new street?", COMPANY_STREET_SIZE);
                break;
            case 4:
                get_edit_string(&(companies->companies[comp_position]), companies->companies[comp_position].address.locality, "Enter the company's new locality: ", "Are you sure you want to keep the new locality?", COMPANY_LOCALITY_SIZE);
                break;
            case 5:
                get_edit_string(&(companies->companies[comp_position]), companies->companies[comp_position].address.postal_code,"Enter the company's new postal_code: ", "Are you sure you want to keep the new postal_code?", 11);
                break;
            case 6:
                get_edit_cat(&(companies->companies[comp_position]), &(companies->companies[comp_position].category), "Enter the new company's category: ", "Are you sure you want to keep the new category?");
                break;
            case 7:
                break;
            case 0:
                *main_op = 0;
                break;
        }
        
    } while (op != 0 && op != 7);

}

void remove_comp(Companies *companies){
    clear_screen();
}