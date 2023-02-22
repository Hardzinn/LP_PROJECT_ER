/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   input.h
 * Author: andre
 *
 * Created on 13 de fevereiro de 2023, 20:55
 */

#ifndef INPUT_H
#define INPUT_H

#define INVALID_OPTION "\nOpcão invalida!"


void cleanInputBuffer();

int obterInt(int minValor, int maxValor, char *msg);

float obterFloat(float minValor, float maxValor, char *msg);

char obterChar(char *msg);

void lerString(char *string, unsigned int tamanho, char *msg);

#endif /* INPUT_H */

