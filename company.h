/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   company.h
 * Author: Diogo Coelho
 *
 * Created on 7 de dezembro de 2023, 13:12
 */

#include <stdio.h>
#include <stdlib.h>

#include "input.h"

#ifndef COMPANY_H
#define COMPANY_H

#define COMPANY_SIZE              10
#define COMPANY_NAME_SIZE         50
#define COMPANY_STREET_SIZE       100
#define COMPANY_LOCALITY_SIZE     50
#define COMPANY_CLASSIS_SIZE      100
#define COMPANY_COMMENTS_SIZE     100

#define COMMENT_TITLE_SIZE        40
#define COMMENT_TEXT_SIZE         100

#define ACTIVITY_BRANCH_NAME_SIZE 50

#define NAME_USER_SIZE            40
#define EMAIL_USER_SIZE           50

#define EDIT_COMP_OPTION_SIZE     7

typedef enum {
    MICRO,
    PME,
    BIG,
    CATEGORY
} Category;

typedef struct{
    char street[COMPANY_STREET_SIZE];
    char locality[COMPANY_LOCALITY_SIZE];
    char postal_code[11];
} Address;

typedef struct {
    int code;
    char name[ACTIVITY_BRANCH_NAME_SIZE];
    int active;
} Act_Branch;

typedef struct {
    int nota;
    char nameUser[NAME_USER_SIZE];
    char emailUser[EMAIL_USER_SIZE];
} Classification;

typedef struct {
    char nameUser[NAME_USER_SIZE];
    char emailUser[EMAIL_USER_SIZE];
    char title[COMMENT_TITLE_SIZE];
    char text[COMMENT_TEXT_SIZE];
} Comment;

typedef struct {
    int act_code;

    int NIF;
    char name[COMPANY_NAME_SIZE];
    Address address;

    Category category;

    int nClassis;
    Classification classis[COMPANY_CLASSIS_SIZE];
    int nComments;
    Comment comments[COMPANY_COMMENTS_SIZE];

    int active;

} Company;

typedef struct {
    int n_comp;
    Company companies[COMPANY_SIZE];
} Companies;

char *print_category(int i);

int read_cat();

int search_comp(Companies companies, int NIF);

void insert_comp(Companies *companies);

void edit_comp(Companies *companies, int *main_op);


#endif /* COMPANY_H */

