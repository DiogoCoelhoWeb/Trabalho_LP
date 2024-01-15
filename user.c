/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "company.h"
#include "user.h"
#include "utilities.h"
#include "input.h"
#include "log_gen.h"

void show_comment(char *name, char *email, char *title, char *text) {
    printf("%s ", title);

    for (int i = 0; i < 64 - (int) strlen(title); i++) {
        printf("-");
    }

    printf("\n");

    printf("%s\n", text);
    printf("%s <%s>\n", name, email);
    printf("-----------------------------------------------------------------\n");
}

void user_search_comp(Companies companies, Activity_Branches activity_branches, SearchType search_type) {

    int NIF;
    int confirm_option;
    int comp;

    Category cat;

    char name[COMPANY_NAME_SIZE];

    switch (search_type) {
        case NIF_SEARCH:
            do {
                clear_screen();
                NIF = getInt(10000000, 999999999, "Enter the NIF you want to search: ");
                confirm_option = confirm_menu("Are you sure you want to seach this NIF?", 1);

                if (confirm_option == 0) {
                    return;
                }
            } while (confirm_option != 1);
            comp = search_comp(companies, NIF);

            if (comp == -1) {
                printf("There are no companies with %d as NIF!", NIF);
                return;
            }

            show_comp(companies.companies[comp], activity_branches);
            pause_exec();
            break;
            
        case NAME_SEARCH:

            do {
                clear_screen();
                confirm_option = get_confirm_string(name, "Enter the name you want to search: ", "Are you sure you want to keep this company name?", COMPANY_NAME_SIZE, 1);

                if (confirm_option == 0) {
                    return;
                }
            } while (confirm_option != 1);

            for (int i = 0; i < companies.n_comp; i++) {
                if (strcmp(name, companies.companies[i].name) == 0) {
                    show_comp(companies.companies[i], activity_branches);
                }
            }
            pause_exec();
            break;

        case CATEGORY_SEARCH:
            do {
                clear_screen();
                cat = read_cat("Choose the category you want to search: ");
                confirm_option = confirm_menu("Are you sure you want to search this category?", 1);

                if (confirm_option == 0) {
                    return;
                }

            } while (confirm_option != 1);

            for (int i = 0; i < companies.n_comp; i++) {
                if (cat == companies.companies[i].category) {
                    show_comp(companies.companies[i], activity_branches);
                }
            }
            pause_exec();
            break;
    }
}

void rate_comp(Companies *companies, Activity_Branches activity_branches, char *name, char *email) {
    int NIF;
    int comp_position;
    int confirm_comp;
    int rate;
    int confirm_option;

    Classification *tmp;

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

        confirm_comp = confirm_menu("Are you sure you want to rate this company?", 1);

        if (confirm_comp == 0) {
            return;
        }
    } while (confirm_comp != 1);


    do {
        clear_screen();
        rate = getInt(0, 5, "Enter the rate (0-5): ");
        confirm_option = confirm_menu("Are you sure you want to keep the rating?", 0);

        if (confirm_option == 0) {
            return;
        }

    } while (confirm_option != 1 && confirm_option != 0);

    tmp = (Classification *) realloc(companies->companies[comp_position].classis, sizeof (Classification) * (companies->companies[comp_position].nClassis + 1));

    if (tmp == NULL) {
        puts("Error rating company");
        logMsg("Error reallocating the classifications array!(realloc failed)", ERROR, LOG_FILE);
        return;
    }

    companies->companies[comp_position].classis = tmp;

    strncpy(companies->companies[comp_position].classis[companies->companies[comp_position].nClassis].nameUser, name, NAME_USER_SIZE);
    strncpy(companies->companies[comp_position].classis[companies->companies[comp_position].nClassis].emailUser, email, EMAIL_USER_SIZE);
    companies->companies[comp_position].classis[companies->companies[comp_position].nClassis].rating = rate;

    companies->companies[comp_position].nClassis++;

}

void comment_comp(Companies *companies, Activity_Branches activity_branches, char *name, char *email) {
    int NIF;
    int comp_position;
    int confirm_comp;
    int confirm_option;

    char title[COMMENT_TITLE_SIZE];
    char comment[COMMENT_TEXT_SIZE];

    Comment *tmp;

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

        confirm_comp = confirm_menu("Are you sure you want to comment this company?", 1);

        if (confirm_comp == 0) {
            return;
        }
    } while (confirm_comp != 1);

    clear_screen();
    confirm_option = get_confirm_string(title, "Enter the comments title: ", "Are you sure you want to keep the title?", COMMENT_TITLE_SIZE, 1);
    if (confirm_option == 0) {
        return;
    }

    clear_screen();
    confirm_option = get_confirm_string(comment, "Enter the comment: ", "Are you sure you want to keep this comment?", COMMENT_TEXT_SIZE, 1);
    if (confirm_option == 0) {
        return;
    }

    tmp = (Comment *) realloc(companies->companies[comp_position].comments, sizeof (Comment) * (companies->companies[comp_position].nComments + 1));
    if (tmp == NULL) {
        puts("Error commenting company");
        logMsg("Error reallocating the comments array!(realloc failed)", ERROR, LOG_FILE);
        return;
    }

    companies->companies[comp_position].comments = tmp;

    strncpy(companies->companies[comp_position].comments[companies->companies[comp_position].nComments].nameUser, name, NAME_USER_SIZE);
    strncpy(companies->companies[comp_position].comments[companies->companies[comp_position].nComments].emailUser, email, EMAIL_USER_SIZE);
    strncpy(companies->companies[comp_position].comments[companies->companies[comp_position].nComments].title, title, COMMENT_TITLE_SIZE);
    strncpy(companies->companies[comp_position].comments[companies->companies[comp_position].nComments].text, comment, COMMENT_TEXT_SIZE);

    companies->companies[comp_position].nComments++;

    show_comment(name, email, title, comment);
    pause_exec();
}