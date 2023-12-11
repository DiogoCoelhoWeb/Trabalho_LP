/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   input.h
 * Author: Diogo Coelho
 *
 * Created on 7 de dezembro de 2023, 16:25
 */

#ifndef INPUT_H
#define INPUT_H

int getInt(int min_value, int max_value, char *msg);

float getFloat(float min_value, float max_value, char *msg);

double getDouble(double min_value, double max_value, char *msg);

char getChar(char *msg);

void getString(char *string, unsigned int size, char *msg);

#endif /* INPUT_H */

