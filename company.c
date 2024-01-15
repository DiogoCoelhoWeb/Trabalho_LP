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

const char *SHOW_REPORTS_OPTIONS[SHOW_REPORTS_OPTION_SIZE] = {"Best Rated Company", "Top 5 Most Rated", "Top 5 Most Commented", "Go Back"};

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

int read_act_branch(char *phrase, Activity_Branches activity_branches) {
    int branch;

    do {
        puts("Ativity Branches ------------------------------------------------");
        for (int i = 0; i < activity_branches.n_branches; i++) {
            printf("  %d - %s\n", i + 1, activity_branches.activity_branches[i].name);
        }

        branch = getInt(1, activity_branches.n_branches, phrase);

        puts("-----------------------------------------------------------------");
    } while (branch < 1 || branch > activity_branches.n_branches);

    return branch - 1;

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

void show_comp(Company company, Activity_Branches activity_branches) {

    printf("\n%s (%s) ", company.name, company.active ? "Active" : "Inactive");

    for (int i = 0; i < 61 - (int) strlen(company.name) - (company.active == 1 ? 6 : 8); i++) {
        printf("-");
    }

    printf("\n");
    printf("  NIF                %d\n", company.NIF);
    printf("  Category           %s\n", print_category(company.category));
    printf("  Activity Branch    %s\n", activity_branches.activity_branches[company.act_code].name);
    printf("  Address            %s, \n", company.address.street);
    printf("                     %s, %s\n\n", company.address.locality, company.address.postal_code);
    printf("  Number of Ratings  %d\n", company.nClassis);
    printf("  Number of Comments %d\n", company.nComments);

    printf("-----------------------------------------------------------------\n\n");
}

int get_edit_string(Company *comp, Activity_Branches activity_branches, char *str, char *phrase, char *menu_phrase, int size) {

    int confirm;

    char aux[size];

    do {
        getString(aux, size, phrase);

        confirm = confirm_menu(menu_phrase, 1);

        if (confirm == 1) {
            strncpy(str, aux, size);
            show_comp(*comp, activity_branches);
            return 1;
        }
    } while (confirm != 1 && confirm != 0);
    return 0;
}

int get_edit_branch(Company *comp, Activity_Branches activity_branches, int *branch, char *phrase, char *menu_phrase) {

    int confirm;
    int branch_tmp;

    if (activity_branches.n_branches == 0) {
        puts("Error editing branches! There are no stored branches!");
        return 0;
    }

    do {

        branch_tmp = read_act_branch(phrase, activity_branches);

        confirm = confirm_menu(menu_phrase, 1);

        if (confirm == 1) {
            *branch = branch_tmp;
            show_comp(*comp, activity_branches);
            return 1;
        }
    } while (confirm != 1 && confirm != 0);
    return 0;
}

int get_edit_cat(Company *comp, Activity_Branches activity_branches, Category *cat, char *phrase, char *menu_phrase) {

    int confirm;
    int cat_tmp;

    do {

        cat_tmp = read_cat(phrase);

        confirm = confirm_menu(menu_phrase, 1);

        if (confirm == 1) {
            *cat = cat_tmp;
            show_comp(*comp, activity_branches);
            return 1;
        }
    } while (confirm != 1 && confirm != 0);
    return 0;
}

int change_state(Company *company, Activity_Branches activity_branches) {
    if (company->active) {
        printf("The company %s is enabled!\n", company->name);
        if (confirm_menu("Are you sure you want to disbale the company?", 0) == 1) {
            company->active = 0;
            clear_screen();
            show_comp(*company, activity_branches);
            pause_exec();
            return 1;
        }
        clear_screen();
        show_comp(*company, activity_branches);
        pause_exec();
        return 0;
    }

    if (confirm_menu("Are you sure you want to enbale the company?", 0) == 1) {
        company->active = 1;
        return 1;
    }

    return 0;

    clear_screen();
    show_comp(*company, activity_branches);
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

void insert_comp(Companies *companies, Activity_Branches activity_branches) {
    int NIF;

    Company *companiestmp;

    clear_screen();

    if (activity_branches.n_branches == 0) {
        puts("There are no activity branches!\n");
        pause_exec();
        return;
    }

    puts("Create Company --------------------------------------------------");
    NIF = getInt(100000000, 999999999, "Enter the companies NIF: ");

    if (search_comp(*companies, NIF) != -1) {
        puts("Company already exists!\n");
        pause_exec();
        return;
    }

    logMsg("Trying to create company...", INFORMATIONAL, LOG_FILE);

    if (companies->n_comp == companies->comp_mem_size) {
        companiestmp = (Company *) realloc(companies->companies, sizeof (Company) * (companies->comp_mem_size * COMPANY_MULT_FACTOR));

        if (companiestmp == NULL) {
            logMsg("Failed to reallocate memory on the heap!(realloc failed)", ERROR, LOG_FILE);
            logMsg("The company couldn't be created!", WARNING, LOG_FILE);
            puts("Error creating company!");
            pause_exec();
            return;
        }

        companies->companies = companiestmp;
        companies->comp_mem_size = companies->n_comp * COMPANY_MULT_FACTOR;
    }

    companies->companies[companies->n_comp].NIF = NIF;

    clear_screen();
    puts("Create Company --------------------------------------------------");
    companies->companies[companies->n_comp].category = read_cat("Enter the company's category: ");

    clear_screen();
    puts("Create Company --------------------------------------------------");
    companies->companies[companies->n_comp].act_code = read_act_branch("Enter the activity branch: ", activity_branches);

    clear_screen();
    puts("Create Company --------------------------------------------------");
    getString(companies->companies[companies->n_comp].name, COMPANY_NAME_SIZE, "Enter the company's name: ");

    clear_screen();
    puts("Create Company --------------------------------------------------");
    getString(companies->companies[companies->n_comp].address.street, COMPANY_STREET_SIZE, "Enter the company's street: ");

    clear_screen();
    puts("Create Company --------------------------------------------------");
    getString(companies->companies[companies->n_comp].address.locality, COMPANY_LOCALITY_SIZE, "Enter the company's locality: ");

    clear_screen();
    puts("Create Company --------------------------------------------------");
    getString(companies->companies[companies->n_comp].address.postal_code, 11, "Enter the company's postal code: ");

    companies->companies[companies->n_comp].active = 1;
    companies->companies[companies->n_comp].nClassis = 0;
    companies->companies[companies->n_comp].nComments = 0;

    clear_screen();

    show_comp(companies->companies[companies->n_comp], activity_branches);
    companies->n_comp++;

    logMsg("Company created successfully!", INFORMATIONAL, LOG_FILE);

    pause_exec();

}

void edit_comp(Companies *companies, Activity_Branches activity_branches, int *main_op) {
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

        show_comp(companies->companies[comp_position], activity_branches);

        confirm_comp = confirm_menu("Are you sure you want to edit this company?", 1);

        if (confirm_comp == 0) {
            return;
        }

    } while (confirm_comp != 1);

    logMsg("Trying to edit company...", INFORMATIONAL, LOG_FILE);

    do {

        clear_screen();

        op = menu(EDIT_COMP_OPTION_SIZE, "Edit Company", EDIT_COMP_OPTIONS);

        switch (op) {
            case 1:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if (get_edit_string(&(companies->companies[comp_position]), activity_branches, companies->companies[comp_position].name, "Enter the new company's name: ", "Are you sure you want to keep the new name?", COMPANY_NAME_SIZE)) {
                    logMsg("Changed the company's name", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 2:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if (get_edit_branch(&(companies->companies[comp_position]), activity_branches, &(companies->companies[comp_position].act_code), "Enter the new company's activity branch: ", "Are you sure you want to keep this activity branch?")) {
                    logMsg("Changed the company's activity branch", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 3:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if (get_edit_string(&(companies->companies[comp_position]), activity_branches, companies->companies[comp_position].address.street, "Enter the company's new street: ", "Are you sure you want to keep the new street?", COMPANY_STREET_SIZE)) {
                    logMsg("Changed the company's street", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 4:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if (get_edit_string(&(companies->companies[comp_position]), activity_branches, companies->companies[comp_position].address.locality, "Enter the company's new locality: ", "Are you sure you want to keep the new locality?", COMPANY_LOCALITY_SIZE)) {
                    logMsg("Changed the company's locality", INFORMATIONAL, LOG_FILE);
                }
                break;
            case 5:
                clear_screen();
                puts("Edit Company ----------------------------------------------------");
                if (get_edit_string(&(companies->companies[comp_position]), activity_branches, companies->companies[comp_position].address.postal_code, "Enter the company's new postal_code: ", "Are you sure you want to keep the new postal_code?", 11)) {
                    logMsg("Changed the company's postal code", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 6:
                clear_screen();
                puts("Edit Company ----------------------------------------------------\n");
                if (get_edit_cat(&(companies->companies[comp_position]), activity_branches, &(companies->companies[comp_position].category), "Enter the new company's category: ", "Are you sure you want to keep the new category?")) {
                    logMsg("Changed the company's category", INFORMATIONAL, LOG_FILE);
                }
                pause_exec();
                break;
            case 7:
                clear_screen();
                puts("Edit Company ----------------------------------------------------\n");
                if (change_state(companies->companies + comp_position, activity_branches)) {
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

void remove_comp(Companies *companies, Activity_Branches activity_branches) {

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

    show_comp(companies->companies[comp_position], activity_branches);

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
        } else {
            logMsg("Failed to reallocate the companies array!(realloc failed)", ERROR, LOG_FILE);
            logMsg("The array couldn't be resized!", WARNING, LOG_FILE);
        }
    }

    clear_screen();
    logMsg("Company successfuly deleted!", INFORMATIONAL, LOG_FILE);
    puts("Company successfully deleted!\n");
    pause_exec();
}

void list_comp(Companies companies, Activity_Branches activity_branches) {

    clear_screen();

    if (companies.n_comp == 0) {
        puts("There are no companies stored!\n");
        pause_exec();
        return;
    }

    logMsg("Listing companies...", INFORMATIONAL, LOG_FILE);
    puts("List Companies --------------------------------------------------\n");

    for (int i = 0; i < companies.n_comp; i++) {
        if (companies.companies[i].active || activity_branches.activity_branches[companies.companies[i].act_code].active) {
            show_comp(companies.companies[i], activity_branches);
        }
    }

    logMsg("Companies listed successfuly!", INFORMATIONAL, LOG_FILE);

    pause_exec();
}

void show_reports(Companies companies, int *main_op) {

    int op;
    int sum;
    int comp_id;
    int rated_count = 0;
    
    float average;
    float best_average = 0.0;

    do {
        clear_screen();
        
        op = menu(SHOW_REPORTS_OPTION_SIZE, "Show Reports", SHOW_REPORTS_OPTIONS);
        
        switch(op){
            case 1:
                
                for(int i = 0; i < companies.n_comp; i++){
                    if(companies.companies[i].nClassis > 0){
                        rated_count++;
                    }
                }
                
                if(rated_count == 0){
                    puts("No companies were rated!");
                    pause_exec();
                    return;
                }
                
                for(int i = 0; i < companies.n_comp; i++){
                    sum = 0;
                    for(int j = 0; j < companies.companies[i].nClassis; j++){
                        sum += companies.companies[i].classis[j].rating;
                    }
                    average = (float) sum / companies.companies[i].nClassis;
                    
                    if(average > best_average){
                        best_average = average;
                        comp_id = i;
                    }  
                }
                
                printf("The best rated comapny is %s with a rating of: %.2f", companies.companies[comp_id].name, best_average);
                pause_exec();
                break;
                
            case 2:
                break;
                
            case 3:
                break;
                
            case 4:
                break;
                
            case 0:
                *main_op = 0;
                break;
        }
        
    }while(op < 0 || op > SHOW_REPORTS_OPTION_SIZE);

}

const char *EDIT_ACT_BRANCH_OPTIONS[EDIT_ACT_BRANCH_OPTION_SIZE] = {"Name", "Enable/Disable", "Go Back"};

int enable_disbale(Act_Branch *activity_branch) {
    if (activity_branch->active) {
        printf("The branch %s is enabled!\n", activity_branch->name);
        if (confirm_menu("Are you sure you want to disbale this branch?", 0) == 1) {
            activity_branch->active = 0;
            clear_screen();
            puts("The branch is disabled!\n");
            pause_exec();
            return 1;
        }
        return 0;
    }

    if (confirm_menu("Are you sure you want to enbale the company?", 0) == 1) {
        activity_branch->active = 1;
        puts("The branch is enabled!\n");
        return 1;
    }

    return 0;
}

void insert_act_branch(Activity_Branches *activity_branches) {

    int confirm_option;

    char branch_name[ACTIVITY_BRANCH_NAME_SIZE];

    Act_Branch *tmp;

    clear_screen();

    puts("Create Activity Branch ------------------------------------------");
    logMsg("Trying to create an activity branch...", INFORMATIONAL, LOG_FILE);

    do {
        confirm_option = get_confirm_string(branch_name, "Enter the branch name:", "Are you sure you want to keep this branch name?", ACTIVITY_BRANCH_NAME_SIZE, 1);
        if (confirm_option == 0) {
            return;
        }
    } while (confirm_option != 1);

    for (int i = 0; i < activity_branches->n_branches; i++) {
        if (activity_branches->activity_branches[i].isRemoved) {
            strncpy(activity_branches->activity_branches[i].name, branch_name, ACTIVITY_BRANCH_NAME_SIZE);
            activity_branches->activity_branches[i].active = 1;
            activity_branches->activity_branches[i].isRemoved = 0;
            logMsg("Branch created successfully", INFORMATIONAL, LOG_FILE);
            pause_exec();
            return;
        }
    }

    tmp = (Act_Branch *) realloc(activity_branches->activity_branches, sizeof (Act_Branch) * (activity_branches->n_branches + 1));

    if (tmp == NULL) {
        puts("Failed to create activity branch!");
        pause_exec();
        logMsg("Error creating activity_branch!(realloc failed)", ERROR, LOG_FILE);
        return;
    }

    activity_branches->activity_branches = tmp;

    strncpy(activity_branches->activity_branches[activity_branches->n_branches].name, branch_name, ACTIVITY_BRANCH_NAME_SIZE);
    activity_branches->activity_branches[activity_branches->n_branches].active = 1;
    activity_branches->activity_branches[activity_branches->n_branches].isRemoved = 0;
    activity_branches->n_branches++;

    logMsg("Branch created successfully", INFORMATIONAL, LOG_FILE);

}

void edit_act_branch(Activity_Branches *activity_branches, int *main_op) {

    int branch;
    int op;

    clear_screen();

    if (activity_branches->n_branches == 0) {
        puts("There are no activity braches stored!");
        pause_exec();
        return;
    }

    do {
        puts("Edit Activity Branch --------------------------------------------");

        for (int i = 0; i < activity_branches->n_branches; i++) {
            printf("  %d - %s\n", i + 1, activity_branches->activity_branches[i].name);
        }

        puts("-----------------------------------------------------------------");

        branch = getInt(1, activity_branches->n_branches, "Choose the activity branch you want to edit: ");
    } while (branch < 1 || branch > activity_branches->n_branches);

    branch--;

    do {

        clear_screen();

        op = menu(EDIT_ACT_BRANCH_OPTION_SIZE, "Edit Activity Branch", EDIT_ACT_BRANCH_OPTIONS);

        switch (op) {
            case 1:
                if (get_confirm_string(activity_branches->activity_branches[branch].name, "Enter the new branch name: ", "Are you sure you want to kee the new branch name?", ACTIVITY_BRANCH_NAME_SIZE, 1) != 0) {
                    logMsg("Changed the branch's name!", INFORMATIONAL, LOG_FILE);
                }
                break;

            case 2:
                if (enable_disbale(&(activity_branches->activity_branches[branch]))) {
                    logMsg("Changed the branch's activity state!", INFORMATIONAL, LOG_FILE);
                }
                break;

            case 3:
                break;

            case 0:
                *main_op = 0;
                break;
        }

    } while (op != 0 && op != 3);
}

void remove_act_branch(Activity_Branches *activity_branches, Companies companies) {

    int branch;

    clear_screen();

    if (activity_branches->n_branches == 0) {
        puts("There are no activity branches stored!\n");
        pause_exec();
        return;
    }

    clear_screen();

    if (activity_branches->n_branches == 0) {
        puts("There are no activity braches stored!");
        pause_exec();
        return;
    }

    do {
        puts("Remove Activity Branch --------------------------------------------");

        for (int i = 0; i < activity_branches->n_branches; i++) {
            printf("  %d - %s\n", i + 1, activity_branches->activity_branches[i].name);
        }

        puts("-----------------------------------------------------------------");

        branch = getInt(1, activity_branches->n_branches, "Choose the activity branch you want to remove: ");
    } while (branch < 1 || branch > activity_branches->n_branches);

    branch--;

    for (int i = 0; i < companies.n_comp; i++) {
        if (companies.companies[i].act_code == branch) {
            puts("The branch is being used by stored companies!\n");

            if (activity_branches->activity_branches[branch].active != 0) {
                puts("Changing branch to inactive!");
                activity_branches->activity_branches[branch].active = 0;
            } else {
                puts("This branch is already inactive. Skipping instruction!\n");
            }

            pause_exec();
            return;
        }
    }

    strncpy(activity_branches->activity_branches[branch].name, "", ACTIVITY_BRANCH_NAME_SIZE);
    activity_branches->activity_branches[branch].active = 0;
    activity_branches->activity_branches[branch].isRemoved = 1;
}

void list_act_branch(Activity_Branches activity_branches) {

    clear_screen();

    puts("List Activity Branches ------------------------------------------");

    for (int i = 0; i < activity_branches.n_branches; i++) {
        if (activity_branches.activity_branches[i].active != 0 && activity_branches.activity_branches[i].isRemoved != 1) {
            printf("  %d - %s\n", i + 1, activity_branches.activity_branches[i].name);
        }
    }

    puts("-----------------------------------------------------------------");

    pause_exec();

}