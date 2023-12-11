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
}

int read_cat() {
    
    int category;
    
    do {
        puts("------------");
        for (int i = 0; i < CATEGORY; i++) {
            printf("  %d - %s\n", i + 1, print_category(i));
        }
        puts("------------");

        category = getInt(1, CATEGORY, "Enter the company's category: ");

    } while (category < 1 || category > CATEGORY);
    
    return category - 1;
    
}

void show_comp(Company company){
    
    printf("\n%s (%s) ----------------------------------------------------\n",company.name, company.active ? "Active": "Inactive");
    printf("  NIF                %d\n", company.NIF);
    printf("  Category           %s\n", print_category(company.category));
    printf("  Address            %s, %s, %s\n", company.address.street, company.address.locality, company.address.postal_code);
    printf("  Number of Ratings  %d\n", company.nClassis);
    printf("  Number of Comments %d\n", company.nComments);
    
    for(int i = 0; i < strlen(company.name); i++){
        printf("-");
    }
    
    if(!company.active){
        printf("--");
    }
    
    printf("--------------------------------------------------------------\n\n");
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
    Category category;

    NIF = getInt(100000000, 999999999, "Ennter the companies NIF: ");

    if (search_comp(*companies, NIF) != -1) {
        puts("Company already exists!");
        return;
    }

    companies->companies[companies->n_comp].NIF = NIF;

    companies->companies[companies->n_comp].category = read_cat();

    getString(companies->companies[companies->n_comp].name, COMPANY_NAME_SIZE, "Enter the company's name: ");
    getString(companies->companies[companies->n_comp].address.street, COMPANY_STREET_SIZE, "Enter the company's street: ");
    getString(companies->companies[companies->n_comp].address.locality, COMPANY_LOCALITY_SIZE, "Enter the company's locality: ");
    getString(companies->companies[companies->n_comp].address.postal_code, 11, "Enter the company's postal code: ");

    companies->companies[companies->n_comp].active = 0;
    companies->companies[companies->n_comp].nClassis = 0;
    companies->companies[companies->n_comp].nComments = 0;
    
    show_comp(companies->companies[companies->n_comp]);
    
    companies->n_comp++;
    
}

void edit_comp(Companies *companies, int *main_op) {
    int NIF;
    int comp_position;

    NIF = getInt(100000000, 999999999, "Enter the companies NIF: ");

    comp_position = search_comp(*companies, NIF);
    
    if (comp_position == -1) {
        puts("The company doesn't exist!");
        return;
    }
    
    switch(menu(EDIT_COMP_OPTION_SIZE, "Edit Company", EDIT_COMP_OPTIONS)){
        case 1:
            getString(companies->companies[comp_position].name, COMPANY_NAME_SIZE, "Enter the company's name: ");
            break;
        case 2:
            //TODO: Activity Branch
            break;
        case 3:
            getString(companies->companies[comp_position].address.street, COMPANY_STREET_SIZE, "Enter the company's street: ");
            break;
        case 4:
            getString(companies->companies[comp_position].address.locality, COMPANY_LOCALITY_SIZE, "Enter the company's locality: ");
            break;
        case 5:
            getString(companies->companies[comp_position].address.postal_code, 11, "Enter the company's postal code: ");
            break;
        case 6:
            companies->companies[comp_position].category = read_cat();
            break;
        case 7:
            break;
        case 0:
            *main_op = 0;
            break;
    }

}